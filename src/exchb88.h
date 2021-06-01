#ifndef RATOM_EXCHB88_H
#define RATOM_EXCHB88_H


/** \brief Becke 1988 approximation.
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/


#include "xc.h"
#include <cmath>

class ExchB88 //: public Xc
{
public:
    ExchB88(void);
    virtual ~ExchB88(void);

    virtual double E(double rhoa, double rhob, double gaa, double gab, double gbb) const;

    virtual double Vrhoa(double rhoa, double rhob, double gaa, double gab, double gbb) const;
    virtual double Vrhob(double rhoa, double rhob, double gaa, double gab, double gbb) const;

    virtual double Vgaa(double rhoa, double rhob, double gaa, double gab, double gbb) const;
    virtual double Vgbb(double rhoa, double rhob, double gaa, double gab, double gbb) const;
    virtual double Vgab(double rhoa, double rhob, double gaa, double gab, double gbb) const;

private:
    double Ehelp(double rho, double g) const;
    double Vhelp(double rho, double g) const;

    double G(double x) const;
    double Gprim(double x) const;

    static double asinh(double x)
    {
        return log(x + sqrt(x * x + 1.));
    }


protected:
    static const double m_rhoMin;
};


#endif

