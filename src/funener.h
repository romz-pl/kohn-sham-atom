#ifndef RATOM_FUNENER_H
#define RATOM_FUNENER_H

//
// Helper classes used to evaluated terms of total energy
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include "pot.h"


//
//
//
class FunEner : public Fun1D
{
public:
    FunEner( const Pot& pot ) : m_pot( pot ) { }

protected:
    double RhoTilde( double r, double rho ) const;

protected:
    // Interaction potencial
    const Pot& m_pot;
};


//
//
//
class EnerTotal : public FunEner
{
public:
    EnerTotal( const Pot& pot ) : FunEner( pot ) { }
    virtual double Get( double r ) const;
};

//
//
//
class EnerNucleus : public FunEner
{
public:
    EnerNucleus( const Pot& pot ) : FunEner( pot ) { }
    virtual double Get( double r ) const;
};

//
//
//
class EnerHartree : public FunEner
{
public:
    EnerHartree( const Pot& pot ) : FunEner( pot ) { }
    virtual double Get( double r ) const;
};


//
//
//
class EnerExch : public FunEner
{
public:
    EnerExch( const Pot& pot ) : FunEner( pot ) { }
    virtual double Get( double r ) const;
};


//
//
//
class EnerCorr : public FunEner
{
public:
    EnerCorr( const Pot& pot ) : FunEner( pot ) { }
    virtual double Get( double r ) const;
};


//
//
//
class EnerKinetic : public FunEner
{
public:
    EnerKinetic( const Pot& pot ) : FunEner( pot ) { }
    virtual double Get( double r ) const;
};

#endif

