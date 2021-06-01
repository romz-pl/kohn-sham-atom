#include <fstream>
#include <sstream>
#include "rho.h"
#include "rhoinit.h"
#include "constants.h"
#include "approxsolver.h"
#include "gauss.h"
#include "paramdb.h"


//
// Initialization of electron density.
// Proper initialization of electron density could have large impact on the
// convergence of Self Consisten Field (SCF) procedure implemented in class NonLinKs.
//
// The algorithm implemented in this function is based on heuristic!
// I have never tried other incitialization functions, since I was satisfied with
// the current speed of convergence.
//
// 1. For default initialization the following function is used
//
//        \rho_0(r) = M^4 / 16 * r^2 * \exp( -M * r / 2 )
//
//    where M is the number of electrons (equal to the number of protons for the nutral atom).
//
// 2. For user defined initialization the following function is used
//
//        \rho_0(r) = c * r^2 * \exp( -\alpha * r );
//
//    See the class RhoInit.
//
//
void Rho::Init()
{
    const bool def = ParamDb::GetBool( "Rho0_Default" );
    const double M = ParamDb::GetDouble( "Atom_Proton" );
    const double midM = 50; // This is heuristic!
    double c, alpha;

    if( def ) // Default initialization
    {
        double w;
        if( M < midM )
            w = M;
        else
            w = midM;
        // Default inicjalization
        c = w * w * w * w / 16.;
        c *= ( M / w );
        alpha = 0.5 * w;
    }
    else // User defined initialization
    {

        c = ParamDb::GetDouble( "Rho0_c" );
        alpha = ParamDb::GetDouble( "Rho0_Alpha" );
    }

    RhoInit f( c, alpha );
    Calc( f );
    const double elecNo = Integ();

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+  Number of protons (electrons) = %.2lf\n", M );
    printf("+  Applied 'Rho0' gives %.6lf electrons\n", elecNo );
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");


    // After initialization integral of electron densities shuld be equal to number of protons
    const double eps = 1E-4;
    if( fabs( M - elecNo ) > eps )
    {
        if( def )
        {
            throw std::runtime_error( "Something strange in function Rho::Init" );
        }
        else
        {
            std::stringstream ss;
            ss << "Invalid arguments for user defined initialization of electron density." << std::endl;
            ss << "Applied parameter Rho0_c = " << ParamDb::GetDouble( "Rho0_c" ) << std::endl;
            ss << "and parameter Rho0_Alpha = " << ParamDb::GetDouble( "Rho0_Alpha" ) << std::endl;
            ss << "give wrong number of electrons! It must be: " << M << std::endl;
            ss << "Applied parameters gave: " << elecNo << std::endl;
            ss << "Adjust parameters Rho0_c, Rho0_Alpha and try again." << std::endl;
            throw std::runtime_error( ss.str() );
        }
    }
}

//
// returns integral
//
// \int \rho(r) d \vec{r} = \int_0^{\infty} \rho(r) dr
//
double Rho::Integ() const
{
    const std::vector< double > node = GetNode();
    assert( node.size() > 1 );

    double val = 0;
    for( size_t i = 0; i < node.size() - 1; ++i )
        val += Gauss::Calc( *this, node[ i ], node[ i + 1 ] );

    return val;
}

//
// Calculates approximation of electron density based on function "f"
//
void Rho::Calc( const Fun1D& f )
{
    const double rc			= ParamDb::GetDouble( "Atom_Rc" );
    const size_t rhoDeg		= ParamDb::GetSize_t( "Rho_Deg" );
    const double rhoDelta	= ParamDb::GetDouble( "Rho_Delta" );

    ApproxSolver approxSolver( rhoDeg, f );
    m_approx = approxSolver.Run( 0, rc, rhoDelta );
}

//
// Returns electron density for radius "r"
//
double Rho::Get( double r ) const
{
    assert( r <= ParamDb::GetDouble( "Atom_Rc" ) );

    const double v = m_approx.Get( r );

    // Sometimes, because of approximation, the approximated value is less than zero,
    // what has no phisical meaning. Then zero is returned.
    if( v < 0. )
        return 0;

    return v;
}

//
// Returns value of helper function $\tilde{\rho}(r)$
//
double Rho::GetRhoTilde( double r ) const
{
    const double rho = Get( r );

    if( r > 0 )
        return rho / ( RATOM_4PI * r * r );

    // Linear extrapolation for (r == 0)
    const double eps = 1E-6;
    const double v1 = GetRhoTilde( eps );
    const double v2 = GetRhoTilde( 2 * eps );
    return 2 * v1 - v2;
}

//
// Returns nodes used for perfoming the approximation
//
std::vector< double > Rho::GetNode() const
{
    return m_approx.GetNode();
}


//
// Writes calculated total radial electron density.
//
void Rho::Write() const
{
    const std::string outRhoPath = ParamDb::GetString( "Out_RhoPath" );
    std::ofstream out( outRhoPath, std::ios::out );
    if( !out )
    {
        throw std::invalid_argument( "Cannot open file. Path = " + outRhoPath );
    }
    out << std::scientific;

    const size_t outRhoNode = ParamDb::GetSize_t( "Out_RhoNode" );
    if( outRhoNode < 1 )
    {
        throw std::runtime_error( "Out_RhoNode must be greater then zero." );
    }

    out << "# \n";
    out << "# Output from RAtom program.\n";
    out << "# \n";
    out << "# Total radial electron density.\n";
    out << "# The first column contains radius $r$ in bohr units.\n";
    out << "# The second column holds $\\rho(r)$.\n";
    out << "# The third column holds $\\tilde{\\rho}(r) = \\rho(r) / (\\pi * r * r)$\n";
    out << "# \n";
    out << "# Use this file with gnuplot to create the plot.\n";
    out << "# \n";
    out << "# R     Rho     RhoTilde\n";
    out << "#\n";

    const std::vector< double > node = GetNode( );
    if( node.empty() )
    {
        throw std::runtime_error( "No data in Rho::Write function." );
    }


    double r;
    for( size_t i = 0; i < node.size() - 1; ++i )
    {
        const double dr = ( node[ i + 1 ] - node[ i ]) / outRhoNode;
        r = node[ i ];
        for( size_t k = 0; k < outRhoNode; ++k )
        {
            out  << r << " " << Get( r ) << " " << GetRhoTilde( r ) << std::endl;
            r += dr;
        }
    }

    // The last node
    r = node.back();
    out  << r << " " << Get( r ) << " " << GetRhoTilde( r ) << std::endl;

}

