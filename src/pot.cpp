#include <cassert>
#include "pot.h"
#include "exchslater.h"
#include "corrvwn.h"
#include "constants.h"
#include "paramdb.h"
#include <stdexcept>

//
// Constructor
//
Pot::Pot( )
    : m_z( ParamDb::GetDouble( "Atom_Proton" ) )
{
    SetXc( );
}



//
// Returns value of electron density  for radius "r"
//
double Pot::GetRho( double r ) const
{
    return m_rho.Get( r );
}

//
// Returns effective potential for radial Kohn-Sham equation for radius "r"
//
double Pot::Get( double r ) const
{
    assert( r > 0 );

    const double rhoVal = m_rho.Get( r ) / ( RATOM_4PI * r * r );
    assert( rhoVal >= 0 );

    const double vn = Vn( r );
    const double vx = Vx( rhoVal, 0 );
    const double vc = Vc( rhoVal, 0 );
    const double vh = Vh( r );

    return vx + vc + vn + vh;
}

//
// Sets the new electron density
//
void Pot::SetRho( const Rho &rho )
{
    m_rho = rho;

    // When electron density was changed, the Poisson equation must be solved.
    m_poisson.Solve( m_rho );
}


//
// Electrostatic potential of atomic core
//
double Pot::Vn( double r ) const
{
    return - m_z / r;
}


//
// Exchange potential
//
double Pot::Vx( double rho, double rhoDer ) const
{
    assert( m_exch );
    return m_exch->V( rho, rhoDer );
}

//
// Correlation potential
//
double Pot::Vc( double rho, double rhoDer ) const
{
    assert( m_corr );
    return m_corr->V( rho, rhoDer );
}

//
// Hartree potential
//
double Pot::Vh( double r ) const
{
    return m_poisson.GetVh( r );
}

//
// Density of exchnage energy
//
double Pot::Ex( double rho, double rhoDer ) const
{
    assert( m_exch );
    return m_exch->E( rho, rhoDer );
}

//
// Density of correlation density
//
double Pot::Ec( double rho, double rhoDer ) const
{
    assert( m_corr );
    return m_corr->E( rho, rhoDer );
}



//
// Returns difference between density of energy and potential
//
double Pot::XcEdiffV( double r ) const
{
    const double rho = m_rho.Get( r );

    return m_exch->EdiffV( rho, 0 ) + m_corr->EdiffV( rho, 0 );
}


//
// Defines exchange and correlation approximation
//
void Pot::SetXc( )
{
    const std::string exch = ParamDb::GetString( "XC_Exch" );
    const std::string corr = ParamDb::GetString( "XC_Corr" );

    if( exch == "slater" )
    {
        m_exch.reset( new ExchSlater );
    }
    else
    {
        throw std::invalid_argument( "Unknown exchange type. Only 'slater' supported!" );
    }

    if( corr == "vwn" )
    {
        m_corr.reset( new CorrVwn );
    }
    else
    {
        throw std::invalid_argument( "Unknown correlation type. Only 'vwn' supported!" );
    }
}
