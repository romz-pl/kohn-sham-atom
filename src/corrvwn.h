#ifndef RATOM_CORRVWN_H
#define RATOM_CORRVWN_H


/** \brief VWN approximation.
*
*	\note 1) S. J. Vosko, L. Wilk, M. Nusair "Accurate spin dependent electron liquid correlation
*		energies for local spin dnsity calculations: A critical analysis",
*		Can. J. Phys. vol. 58, 1200-1211 (1980)
*		2) Vosko, Wilk, Phys. Rev. B, vol. 22, 3812 (1980)
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/

#include "xc.h"



class CorrVwn : public Xc
{
public:
    CorrVwn(void);
    virtual ~CorrVwn(void);

    virtual double V(double rho, double gRho) const;
    virtual double E(double rho, double gRho) const;
    virtual double EdiffV(double rho, double gRho) const;

    virtual const char* Name() const
    {
        return "vwn";
    }

private:
    virtual void Help(double rho, double* ec, double* vc) const;
};


#endif

