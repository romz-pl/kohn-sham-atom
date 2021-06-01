#include "exchs.h"
#include <cmath>


const double ExchS::m_alpha = 2./3;
const double ExchS::m_c = pow(3. / (4. * M_PI), 1./3.);

//
// Construktor
//
ExchS::ExchS(void)
{
}

//
// Destructor
//
ExchS::~ExchS(void)
{
}

///
// Returns density of exchange energy per one electron
// rhoa - electron density alpha
// rhob - electron density beta
// gaa  - gamma_{\alpha \alpha} not used
// gab  - gamma_{\alpha \beta} not used
// gbb  - gamma_{\beta \beta} not used
//
double ExchS::E(double rhoa, double rhob, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
const double f = -(9./4.) * m_alpha * m_c;

    // return f * (pow(rhoa, 4./3.) + pow(rhob, 4./3.)) / (rhoa + rhob);
    return f * (pow(rhoa, 4./3.) + pow(rhob, 4./3.));
}



//
// Returns derivative of functional $\rho_{\alpha}$.
// rhoa - electron density alpha
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchS::Vrhoa(double rhoa, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
const double f = -3. * m_alpha * m_c;

    return f * pow(rhoa, 1./3.);
}

//
// Returns derivative of functional $\rho_{\beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchS::Vrhob(double /*rhoa*/, double rhob, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
const double f = -3. * m_alpha * m_c;

    return f * pow(rhob, 1./3.);
}


//
// Returns derivative of functional $\gamma_{\alpha \alpha}$.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchS::Vgaa(double /*rhoa*/, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return 0.;
}


//
// Returns derivative of functional $\gamma_{\beta \beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchS::Vgbb(double /*rhoa*/, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return 0.;
}

//
// Returns derivative of functional $\gamma_{\alpha \beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchS::Vgab(double /*rhoa*/, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return 0;
}



