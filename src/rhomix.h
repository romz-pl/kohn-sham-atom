#ifndef RATOM_RHOMIX_H
#define RATOM_RHOMIX_H


//
// Linear mixing of states neaded to aobtain SCF convergence
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include "fun1D.h"
#include "paramdb.h"


class RhoMix : public Fun1D
{
public:
    RhoMix( const Fun1D& rhoCur, const Fun1D& rhoOld)
        : m_rhoCur( rhoCur ), m_rhoOld( rhoOld )
    {
        m_scfMix = ParamDb::GetDouble( "Scf_Mix" );
    }

    virtual ~RhoMix() = default;



    virtual double Get( double r ) const
    {
        const double cur = m_rhoCur.Get( r );
        const double old = m_rhoOld.Get( r );

        return m_scfMix * cur + ( 1.0 - m_scfMix ) * old;
    }

private:
    // Current elevron density
    const Fun1D& m_rhoCur;

    // Old electron density
    const Fun1D& m_rhoOld;

    // Mixing coefficient from SCF algorithm
    double m_scfMix;
};



#endif
