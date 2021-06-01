#include "exchpbe.h"
#include "constants.h"
#include <cmath>



const double ExchPbe::m_kpTable[2] = {0.804, 1.245};
// const double ExchPbe::m_beta = 0.066725;
// const double ExchPbe::m_mu = m_beta * M_PI * M_PI / 3.;
const double ExchPbe::m_mu = 0.2195149727645171;
const ExchS ExchPbe::m_slater;
const double ExchPbe::m_coef = 1. / (2 * pow(3. * M_PI * M_PI, 1./3.));


//
// Constructor
// if rev equal to "true", then "revived PBE"
//
ExchPbe::ExchPbe(bool rev)
{
    m_kp = m_kpTable[rev ? 1 : 0];
}

//
// Destructor
//
ExchPbe::~ExchPbe(void)
{
}

///
// Returns density of exchange energy per one electron
// rhoa - electron density alpha
// rhob - electron density beta
// gaa  - gamma_{\alpha \alpha}
// gab  - gamma_{\alpha \beta} not used
// gbb  - gamma_{\beta \beta}
//
double ExchPbe::E(double rhoa, double rhob, double gaa, double /*gab*/, double gbb) const
{
    return 0.5 * (Ehelp(rhoa, gaa) + Ehelp(rhob, gbb));
}

double ExchPbe::Ehelp(double rho, double g) const
{
    return m_slater.E(rho, rho, 0., 0., 0.) * Fx(S(2. * rho, 4. * g));
}

double ExchPbe::Fx(double s) const
{
    return 1. + m_kp - m_kp / (1. + m_mu * s * s / m_kp);
}

//!
//! \frac{ \partial F_x(s) } { \partial s}
//!
double ExchPbe::FxDer(double s) const
{
const double v1 = 2. * m_kp * m_kp * m_mu * s;
const double v2 = m_kp + m_mu * s * s;

    return v1 / (v2 * v2);
}

//!
//! grho = $|\nabla \rho|^2$
//!
double ExchPbe::S(double rho, double grho) const
{
    return sqrt(grho) * m_coef * pow(rho, -4./3.);
}

//!
//! \frac{ \partial s }{ \partial \rho }
//!
double ExchPbe::SRho(double rho, double grho) const
{
    return -(4./3.) * sqrt(grho) * m_coef * pow(rho, -7./3.);
}


//!
//! \frac{ \partial s }{ \partial |\rho| }
//!
double ExchPbe::SGradRho(double rho, double /*grho*/) const
{
    return m_coef * pow(rho, -4./3.);
}

double ExchPbe::Kf(double rho) const
{
    return pow(3 * M_PI * M_PI * rho, 1./3.);
}


//
// Returns derivative of functional $\rho_{\alpha}$.
// rhoa - electron density alpha
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchPbe::Vrhoa(double rhoa, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return  pow(rhoa, 1./3.);
}

//
// Returns derivative of functional $\rho_{\beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchPbe::Vrhob(double /*rhoa*/, double rhob, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{

    return pow(rhob, 1./3.);
}


//
// Returns derivative of functional $\gamma_{\alpha \alpha}$.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchPbe::Vgaa(double rhoa, double /*rhob*/, double gaa, double /*gab*/, double /*gbb*/) const
{
const double v1 = m_slater.E(rhoa, rhoa, 0., 0., 0.);
const double s = S(2. * rhoa, 4. * gaa);
const double v2 = FxDer(s);
const double v3 = SGradRho(2. * rhoa, 4. * gaa);

    return 0.5 * v1 * v2 * v3;
}


//
// Returns derivative of functional $\gamma_{\beta \beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchPbe::Vgbb(double /*rhoa*/, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return 0.;
}

//
// Returns derivative of functional $\gamma_{\alpha \beta}$.
// It is always equal to zero.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchPbe::Vgab(double /*rhoa*/, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return 0;
}



