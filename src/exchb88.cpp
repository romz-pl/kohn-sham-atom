#include "exchb88.h"
#include "constants.h"
#include <cmath>

const double ExchB88::m_rhoMin = 1e-20;

//
// Constructor
//
ExchB88::ExchB88(void)
{
}

//
// Destructor
//
ExchB88::~ExchB88(void)
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
double ExchB88::E(double rhoa, double rhob, double gaa, double /*gab*/, double gbb) const
{
    // return (Ehelp(rhoa, gaa) + Ehelp(rhob, gbb)) / (rhoa + rhob);
    return Ehelp(rhoa, gaa) + Ehelp(rhob, gbb);
}

//
// Returns part of exchange enegrgy for density $rho$ and derivative $g$
//
double ExchB88::Ehelp(double rho, double g) const
{
    if(rho < m_rhoMin)
        return 0.;

const double rho43 = pow(rho, 4. / 3.);
const double x = sqrt(g) / rho43;

    return rho43 * G(x);
}

//
// Returns value of helper function $G(x)$
//
double ExchB88::G(double x) const
{
const double q = 3. / 2. * pow(3. / (4 * M_PI), 1. / 3.);
const double b = 0.0042; // Constant from article B88

    return -q - b * x * x / (1 + 6 * b * x * asinh(x));
}

//
// Returns value of helper function $G'(x)$
//
double ExchB88::Gprim(double x) const
{
const double b = 0.0042; // Constant from article B88
const double q = asinh(x);
double v1, v2;

    v1 = x / sqrt(x * x + 1) - q;
    v2 = 1 + 6 * b * x * q;

    return (6 * b * b * x * x * v1 - 2 * b * x) / (v2 * v2);
}



//
// Returns derivative of functional $\rho_{\alpha}$.
// rhoa - electron density alpha
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha};
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchB88::Vrhoa(double rhoa, double /*rhob*/, double gaa, double /*gab*/, double /*gbb*/) const
{
    return Vhelp(rhoa, gaa);
}

//
// Returns derivative of functional $\rho_{\beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used.
// gbb  - gamma_{\beta \beta};
//
double ExchB88::Vrhob(double /*rhoa*/, double rhob, double /*gaa*/, double /*gab*/, double gbb) const
{
    return Vhelp(rhob, gbb);
}

//
// Helper function
//
double ExchB88::Vhelp(double rho, double g) const
{
    if(rho < m_rhoMin)
        return 0.;

const double rho13 = pow(rho, 1. / 3.);
const double x = sqrt(g) / (rho * rho13);

    return (4. / 3.) * rho13 * (G(x) - x * Gprim(x));
}


//
// Returns derivative of functional $\gamma_{\alpha \alpha}$.
// rhoa - electron density alpha
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha};
// gab  - gamma_{\alpha \beta}; not used.
// gbb  - gamma_{\beta \beta}; not used
//
double ExchB88::Vgaa(double rhoa, double /*rhob*/, double gaa, double /*gab*/, double /*gbb*/) const
{
    if(rhoa < m_rhoMin || gaa < m_rhoMin)
        return 0.;

const double q = sqrt(gaa);
const double xa = q / pow(rhoa, 4. / 3.);

    return Gprim(xa) / (2 * q);
}

//
// Returns derivative of functional $\gamma_{\beta \beta}$.
// rhoa - electron density alpha not used
// rhob - electron density beta
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta};
//
double ExchB88::Vgbb(double /*rhoa*/, double rhob, double /*gaa*/, double /*gab*/, double gbb) const
{
    if(rhob < m_rhoMin || gbb < m_rhoMin)
        return 0.;

const double q = sqrt(gbb);
const double xb = q / pow(rhob, 4. / 3.);

    return Gprim(xb) / (2 * q);
}

//
// Returns derivative of functional $\gamma_{\alpha \beta}$.
// It is always equat to zero.
// rhoa - electron density alpha not used
// rhob - electron density beta not used
// gaa  - gamma_{\alpha \alpha}; not used
// gab  - gamma_{\alpha \beta}; not used
// gbb  - gamma_{\beta \beta}; not used
//
double ExchB88::Vgab(double /*rhoa*/, double /*rhob*/, double /*gaa*/, double /*gab*/, double /*gbb*/) const
{
    return 0;
}



