#ifndef RATOM_RHO_H
#define RATOM_RHO_H

//
// Electron density of atom.
// The electon density is represented as a piecewise polynomial function.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include <vector>
#include "fun1D.h"
#include "approx.h"


class Rho : public Fun1D
{
public:
    Rho( ) = default;
    virtual ~Rho() = default;

    virtual double Get( double r ) const;
    void Calc( const Fun1D& f );
    void Init();
    std::vector< double > GetNode() const;
    void Write() const;

private:
    double Integ() const;
    double GetRhoTilde( double r ) const;

private:
    // Function approximation
    Approx m_approx;
};

#endif

