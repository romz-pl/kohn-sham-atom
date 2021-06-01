#include <fstream>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <cfloat>
#include <cmath>
#include "eigprob.h"
#include "lobatto.h"
#include "gauss.h"
#include "paramdb.h"

const double EigProb::m_gamma = 0.5;

//
// Constructor
//
EigProb::EigProb( size_t ell )
    : m_ell( ell )
{

    const double rc      = ParamDb::GetDouble( "Atom_Rc" );
    const size_t eigNode = ParamDb::GetSize_t( "Solver_EigNode" );
    const size_t eigDeg  = ParamDb::GetSize_t( "Solver_EigDeg" );

    m_mesh.GenLin( 0, rc, eigNode, eigDeg );
    m_mesh.CreateCnnt( BndrType_Dir, BndrType_Dir );
}

//
// Solves the eigenproblem, WITHOUT adaptive procedure
//
void EigProb::Solve( const Fun1D& g, size_t eigNo )
{
    const double abstol = ParamDb::GetDouble( "Solver_EigAbsTol" );

    Malloc();
    Assemble( g );
    m_s.EigenGen(eigNo, abstol, m_w, m_z, m_o);
}

//
// Solve the eigenproblem adatively
//
void EigProb::SolveAdapt( const Fun1D& g, size_t eigNo )
{
    const double absMaxCoef = ParamDb::GetDouble( "Solver_EigAbsMaxCoef" );

    std::vector< EltInfo > eltInfo( eigNo );
    std::vector< size_t > eltToSplit;


    while( true )
    {
        Solve( g, eigNo );
        MaxMinCoef( eltInfo );
        std::sort( eltInfo.begin(), eltInfo.end() );
        const auto newEnd = std::unique( eltInfo.begin(), eltInfo.end() );

        double maxCoef = 0;
        for( size_t i = 0; i < eltInfo.size(); ++i )
        {
            if( eltInfo[i].GetMaxMinCoef() > maxCoef )
                maxCoef = eltInfo[i].GetMaxMinCoef();
        }
        if( maxCoef < absMaxCoef )
            break;

        // The Elt was splitted

        eltToSplit.clear();
        for( auto ii = eltInfo.begin(); ii != newEnd; ++ii )
        {
            eltToSplit.push_back( ii->GetEltId() );
        }

        m_mesh.AddToMesh( eltToSplit );
        m_mesh.CreateCnnt( BndrType_Dir, BndrType_Dir );
    }
}


//
// Allocates the required memory
//
void EigProb::Malloc()
{
    const size_t M = m_mesh.Dim( BndrType_Dir, BndrType_Dir );
    const size_t band = m_mesh.GetBand();

    m_s.Assign( M, band, 0, 0 );
    m_w.assign( M, 0 );
    m_z.Assign( M, M, 0 );
    m_o.Assign( M, band, 0, 0 );
}

//
// Assembling algorithm for eigenvalue problem
//
void EigProb::Assemble( const Fun1D& g )
{
    const size_t N = m_mesh.EltNo(); // Number of elements

    // Element loop
    for( size_t n = 0; n < N; n++ )
    {
        const Element& e = m_mesh.Elt( n );
        const size_t DofNo = e.DofNo();

        // Loop over basis functions
        for( size_t i = 0; i < DofNo; i++ )
        {
            const int ni = e.m_dof[ i ];
            if( ni < 0 )
                continue;

            const size_t psiI = e.PsiId( i );

            // Loop over basis functions
            for( size_t j = i; j < DofNo; j++ )
            {
                const size_t psiJ = e.PsiId( j );

                const int nj = e.m_dof[ j ];
                if( nj > -1 )
                {
                    m_s.Set( ni, nj ) += CalcS( g, e, psiI, psiJ );
                    m_o.Set( ni, nj ) += CalcK( e, psiI, psiJ );
                }
            }
        }
    }
}

//
// Returns the element (ni, nj) of the stiffness matrix element.
// The elements are read from precomputed array.
//
double EigProb::CalcS( const Fun1D& g, const Element& e, size_t ni, size_t nj ) const
{
    const double v1 = m_gamma * Lobatto::GetS( ni, nj );
    double v0 = 0;

    for( size_t n = 0; n < Gauss::Size(); n++ )
    {
        const double s = Gauss::X( n );
        const double w = Gauss::W( n );
        const double r = e.X( s );
        v0 += w * Lobatto::Basis( ni, s ) * Lobatto::Basis( nj, s ) * GetPot( g, r );
    }

    const double jac = e.Jac();
    return v1 / jac + v0 * jac;
}

//
// For given $r$ it returns the value
//    g(r) + L*(L + 1)/(2 r^2)
//
double EigProb::GetPot( const Fun1D& g, double r ) const
{
    assert( r > 0 );
    const double a = g.Get( r );
    const double b = m_ell * ( m_ell + 1 ) / ( 2 * r * r );
    return a + b;
}

//
// Returns the element $o[i][j]$ overlap matrix element
// The elements are read from precomputed array.
//
double EigProb::CalcK( const Element& e, size_t ni, size_t nj ) const
{
    return e.Jac() * Lobatto::GetK( ni, nj );
}


//
// Returns the value of $eig$ eigenfunction at point $r$
//
double EigProb::GetEigFun( size_t eig, double r ) const
{
    assert( eig < m_w.size() );
    assert( m_mesh.IsInRange( r ) );

    const size_t n = m_mesh.FindElt( r );
    const Element& e = m_mesh.Elt( n );

    // s - local variable for element "e"
    const double s = e.Xinv( r );

    // Sum over all basis function with support on the element $e$
    double val = 0;

    for( size_t i = 0; i < e.m_dof.size(); i++ )
    {
        const int mi = e.m_dof[ i ];
        if( mi < 0 )
            continue;

        const size_t psiI = e.PsiId( i );

        val += m_z.Get( mi, eig ) * Lobatto::Basis( psiI, s );
    }
    return val;
}




//
// Returns the value of the $eig$ eigenvalue
//
double EigProb::GetEigVal( size_t eig ) const
{
    assert( eig < m_w.size() );

    return m_w[ eig ];
}



//
// Writes eigen-function $eig$ to file
// If "pointNo == 0", then eigenfunction is stored in mesh nodes only.
// Argument "pointNo" determines number of addtional points netween mesh nodes
// where the eigenfunction is stored.
//
void EigProb::WriteEigFun( const std::string& path, size_t eig, size_t pointNo ) const
{
    std::ofstream out( path.c_str(), std::ios::out );
    if( !out )
    {
        throw std::invalid_argument( "Cannot open file for write. Path = " + path );
    }
    out << std::scientific;

    out << "# \n";
    out << "# Output from RAtom program.\n";
    out << "# \n";
    out << "# Eigenfunction for specific electronic state.\n";
    out << "# The first column contains radius $r$ in bohr units.\n";
    out << "# The second column holds value of eginefunction.\n";
    out << "# \n";
    out << "# Use this file with gnuplot to create the plot.\n";
    out << "#\n";

    if( m_mesh.XNo() == 0 )
    {
        throw std::runtime_error( "Eigenfunction not calculated in function EigProb::WriteEigFun" );
    }
    assert( pointNo > 0 );


    double x;
    for( size_t n = 0; n < m_mesh.XNo() - 1; n++ )
    {
        x = m_mesh.X( n );
        const double dx = ( m_mesh.X( n + 1 ) - m_mesh.X( n ) ) / pointNo;
        for( size_t i = 0; i < pointNo; i++ )
        {
            out  << x << " " << GetEigFun( eig, x ) << std::endl;
            x += dx;
        }
    }

    // The last point must be written (to avoid the rounding errors)
    x = m_mesh.XBack();
    out  << x << " " << GetEigFun( eig, x ) << std::endl;
}



//
// Finds the element with the largest coefficient contained in the minimal coefficients
// BUBBLE functins are considered only.
//
void EigProb::MaxMinCoef( std::vector< EltInfo >& eltInfo ) const
{
    const size_t eigNo = eltInfo.size();
    double minCoef;


    for( size_t i = 0; i < eigNo; i++ ) // For each eigenfunction
    {
        eltInfo[ i ].Set( 0, -1 ); // Inicjalizacja
        for( size_t n = 0; n < m_mesh.EltNo(); n++ ) // For each element
        {
            const Element& e = m_mesh.Elt( n );
            minCoef = DBL_MAX;

            for( size_t j = 1; j < e.DofNo() - 1; j++ ) // For each BUBBLE DOF at element
            {
                const int dof = e.m_dof[ j ];
                if( dof < 0 ) // Skip Dirichlet boundary conditions
                    continue;

                // Find the minimal coefficient for element "e"
                const double coef = fabs( m_z.Get( dof, i ) );
                if( coef < minCoef )
                    minCoef = coef;
            }

            // Set the largest coefficient for the smallest coefficients
            if( minCoef > eltInfo[ i ].GetMaxMinCoef() )
            {
                eltInfo[ i ].Set( minCoef, n );
            }
        }
    }
}
