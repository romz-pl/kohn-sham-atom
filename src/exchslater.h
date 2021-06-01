#ifndef RATOM_EXCHSLATER_H
#define RATOM_EXCHSLATER_H


/** \brief Slater approximation.
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/


#include "xc.h"





class ExchSlater : public Xc
{
public:
    ExchSlater(void);
    virtual ~ExchSlater(void);

    virtual double V(double rho, double gRho) const;
    virtual double E(double rho, double gRho) const;
    virtual double EdiifV(double rho, double gRho) const;

    virtual const char* Name() const
    {
        return "slater";
    }


private:
    double m_c;

};

#endif

