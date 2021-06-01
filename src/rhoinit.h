#ifndef RATOM_RHOINIT_H
#define RATOM_RHOINIT_H


//
// Initialization of electron density
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <cmath>


class RhoInit : public Fun1D
{
public:
    RhoInit(double c, double alpha) : m_c(c), m_alpha(alpha) { }
    virtual ~RhoInit() { }
    virtual double Get(double r) const
    {
        return r * r * m_c * exp(-m_alpha * r);
    }
public:
    double m_c, m_alpha;
};


#endif
