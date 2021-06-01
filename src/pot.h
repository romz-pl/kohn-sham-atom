#ifndef RATOM_POT_H
#define RATOM_POT_H

//
// Interaction potential (without part ddependent on angular quantum number)
// in non-linear Kohn-Sham equation
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include <memory>
#include <string>
#include <cstddef>
#include "fun1D.h"
#include "xc.h"
#include "poissonprob.h"
#include "rho.h"

class Pot : public Fun1D
{
    friend class EnerTotal;

public:
    Pot( );
    virtual ~Pot() = default;

    void SetRho( const Rho& rho );

    virtual double Get( double r ) const;
    double GetRho( double r ) const;


    double Vn( double r ) const;
    double Vx( double rho, double rhoDer ) const;
    double Vc( double rho, double rhoDer ) const;
    double Vh( double r ) const;

    double Ex( double rho, double rhoDer ) const;
    double Ec( double rho, double rhoDer ) const;

    double XcEdiffV( double r ) const;

private:
    void SetXc( );


private:
    // Number of protons in atom
    const double m_z;

    // Electron density
    Rho m_rho;

    // Exchenge potential
    std::unique_ptr< Xc > m_exch;

    // Correlation potential
    std::unique_ptr< Xc > m_corr;

    // Solver for Poisson equation
    PoissonProb m_poisson;
};

#endif

