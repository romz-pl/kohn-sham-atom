#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include "poissonprob.h"
#include "bndr.h"
#include "paramdb.h"
#include "gauss.h"
#include "lobatto.h"


//
//
//
void PoissonProb::Solve( const Fun1D& rho )
{
    const bool adapt = ParamDb::GetBool( "Solver_PsnAdapt" );

    DefineMesh( );

    if( adapt )
    {
        SolveAdapt( rho );
    }
    else
    {
        SolveNonAdapt( rho );
    }
}

//
// Defines the ODE problem
//
void PoissonProb::DefineMesh( )
{
    const double rc      = ParamDb::GetDouble( "Atom_Rc" );
    const size_t psnNode = ParamDb::GetSize_t( "Solver_PsnNode" );
    const size_t psnDeg  = ParamDb::GetSize_t( "Solver_PsnDeg" );

    m_mesh.GenLin( 0, rc, psnNode, psnDeg );
    m_mesh.CreateCnnt( BndrType_Dir, BndrType_Dir );
}


//
// Solves the problem (WITHOUT adaptation)
//
void PoissonProb::SolveNonAdapt( const Fun1D& rho )
{
    Malloc();
    Assemble( rho );
    m_s.SolveSymPos( m_b, m_y );
}

//
// Adaptive solution of the problem
//
void PoissonProb::SolveAdapt( const Fun1D& rho )
{
    const double absMaxCoef = ParamDb::GetDouble( "Solver_PsnAbsMaxCoef" );

    std::vector< size_t > eltToSplit( 1 );

    while( true )
    {
        SolveNonAdapt( rho );
        const EltInfo eltInfo = MaxMinCoef( );

        if( eltInfo.GetMaxMinCoef() < absMaxCoef )
            break;

        eltToSplit[ 0 ] = eltInfo.GetEltId();

        m_mesh.AddToMesh( eltToSplit );
        m_mesh.CreateCnnt( BndrType_Dir, BndrType_Dir );
    }
}

//
// Finds the element with the largest coefficient contained in the minimal coefficients
// BUBBLE functins are considered only.
//
EltInfo PoissonProb::MaxMinCoef( ) const
{
    EltInfo eltInfo;

    for( size_t n = 0; n < m_mesh.EltNo(); n++ ) // For each element
    {
        const Element& e = m_mesh.Elt( n );
        double minCoef = DBL_MAX;

        for( size_t j = 1; j < e.DofNo() - 1; j++ ) // For each BUBBLE DOF in element
        {
            const int dof = e.m_dof[ j ];
            assert( dof >= 0 );

            // Find the smallest coefficient for element "e"
            const double coef = fabs( m_y[ dof ] );
            if( coef < minCoef )
                minCoef = coef;
        }

        // Set the largest coefficient with minimal coefficients
        if( minCoef > eltInfo.GetMaxMinCoef() )
        {
            eltInfo.Set( minCoef, n );
        }
    }

    return eltInfo;
}



//
// Allocates the required memory
//
void PoissonProb::Malloc()
{
    const size_t M = m_mesh.Dim( BndrType_Dir, BndrType_Dir );
    const size_t band = m_mesh.GetBand();

    m_s.Assign( M, band, 0, 0 );
    m_b.assign( M, 0 );
    m_y.assign( M, 0);
}


//
// Assembling algorithm for equation solving
//
void PoissonProb::Assemble( const Fun1D& rho )
{
    const size_t N = m_mesh.EltNo(); // Number of elements


    // Element loop
    for( size_t n = 0; n < N; n++ )
    {
        const Element& e = m_mesh.Elt( n );
        const size_t DofNo = e.DofNo();

        // Loop over basis functions
        for( size_t i = 0; i < DofNo; i++)
        {
            const int ni = e.m_dof[ i ];
            if(ni < 0)
                continue;

            const size_t psiI = e.PsiId( i );

            // Loop over basis functions
            for( size_t j = i; j < DofNo; j++ )
            {
                const size_t psiJ = e.PsiId( j );

                const int nj = e.m_dof[ j ];
                if(nj > -1)
                    m_s.Set( ni, nj ) += CalcS( e, psiI, psiJ );
                //else // Dirichlet boundary conditions are ZERO, hence it can be skiped
                //	m_b->Set(ni) -= bndr[-nj] * CalcS(e, psiI, psiJ);
            }

            // Contribution of the vertex basis function $v_{m_1}$ to the right hand side $b$
            m_b[ ni ] += CalcB( rho, e, psiI );
        }
    }
}

//
// Returns the element $b[i]$ of load matrix element.
// Gauss quadrature applied.
//
double PoissonProb::CalcB( const Fun1D& rho, const Element& e, size_t ni ) const
{
    double b = 0;

    for( size_t n = 0; n < Gauss::Size(); n++ )
    {
        const double s = Gauss::X( n );
        const double w = Gauss::W( n );
        const double r = e.X( s );
        b += w * Lobatto::Basis( ni, s ) * rho.Get( r ) / r;
    }
    return e.Jac() * b;
}

//
// Returns the element $e[i][j]$ stiffness matrix element.
// The elements are read from precomputed array.
//
double PoissonProb::CalcS( const Element& e, size_t ni, size_t nj ) const
{
    const double gamma = 1;
    const double v1 = gamma * Lobatto::GetS( ni, nj );

    const double jac = e.Jac();
    return v1 / jac;
}

//
// Returns the value of the solution at $x$
//
double PoissonProb::GetUh( double r ) const
{
    assert( m_mesh.IsInRange( r ) );
    const size_t n = m_mesh.FindElt( r );
    const Element& e = m_mesh.Elt( n );

    // s - Locat coordiante for element "e"
    const double s = e.Xinv( r );

    // Sum over all basis function with support on the element $e$
    double val = 0;


    // It works only with zero Dirichlet bpundary conditions
    for( size_t i = 0; i < e.m_dof.size(); i++ )
    {
        const int m = e.m_dof[ i ];
        if( m < 0 )
            continue;
        const size_t psiI = e.PsiId( i );

        val += m_y[ m ] * Lobatto::Basis( psiI, s );
    }


    return val;
}

double PoissonProb::GetVh( double r ) const
{
    assert( r > 0 );
    const double val = GetUh( r );

    const double z = ParamDb::GetDouble( "Atom_Proton" );
    const double rc = ParamDb::GetDouble( "Atom_Rc" );

    // Apply non-zero Dirichlet boundary conditions
    const double ua = 0, ub = z, a = 0, b = rc;
    const double alpha = ( ub - ua ) / ( b - a ), beta = ua - a * alpha;

    return ( val + alpha * r + beta ) / r;
}
