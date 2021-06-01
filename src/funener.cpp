#include "funener.h"
#include "constants.h"

//
// Returns value of function \tilde{\rho}(r)
//
double FunEner::RhoTilde( double r, double rho ) const
{
    return rho / ( RATOM_4PI * r * r );
}


//
// Integrand for energy "Total"
//
double EnerTotal::Get( double r ) const
{
    const double rho = m_pot.GetRho( r );
    const double rhoT = RhoTilde( r, rho );
    double ex, co, vh;

    ex = m_pot.m_exch->EdiffV( rhoT, 0 );
    co = m_pot.m_corr->EdiffV( rhoT, 0 );
    vh = m_pot.Vh( r );

    return ( ex + co - 0.5 * vh ) * rho;
}

//
// Integrand for energy "Nucleus"
//
double EnerNucleus::Get( double r ) const
{
    const double rho = m_pot.GetRho( r );

    return m_pot.Vn( r ) * rho;
}

//
// Integrand for energy "Hartree"
//
double EnerHartree::Get( double r ) const
{
    const double rho = m_pot.GetRho( r );

    return 0.5 * m_pot.Vh( r ) * rho;
}

//
// Integrand for energy "Exchenge"
//
double EnerExch::Get( double r ) const
{
    const double rho = m_pot.GetRho( r );
    const double rhoT = RhoTilde( r, rho );

    return m_pot.Ex( rhoT, 0 ) * rho;
}

//
// Integrand for energy "Correlation"
//
double EnerCorr::Get( double r ) const
{
    const double rho = m_pot.GetRho( r );
    const double rhoT = RhoTilde( r, rho );

    return m_pot.Ec( rhoT, 0 ) * rho;
}

//
// Integrand for energy "Kinetic"
//
double EnerKinetic::Get( double r ) const
{
    const double rho = m_pot.GetRho( r );
    const double rhoT = RhoTilde( r, rho );

    const double vx = m_pot.Vx( rhoT, 0 );
    const double vc = m_pot.Vc( rhoT, 0 );
    const double vn = m_pot.Vn( r );
    const double vh = m_pot.Vh( r );

    return ( vx + vc + vn + vh ) * rho;
}



