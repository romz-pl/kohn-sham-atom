#ifndef RATOM_XC_H
#define RATOM_XC_H


/** \brief Represents any echang-coreelation potential.
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/


class Xc
{
public:
    Xc(void);
    virtual ~Xc(void);

    virtual double V(double rho, double gRho) const = 0;
    virtual double E(double rho, double gRho) const = 0;

    virtual double EdiffV(double rho, double gRho) const;

    virtual const char* Name() const = 0;

protected:
    static double Rs(double rho);

};

#endif

