#ifndef RATOM_ENERGY_H
#define RATOM_ENERGY_H

//
// Evaluates the terms of the total energy
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include <vector>
#include <cstdio>
#include "pot.h"
#include "stateset.h"
#include "funener.h"
#include "eigresult.h"


class Energy
{
public:
    Energy( const Pot& pot, const EigResult& eigResult, const std::vector< double > &node ) ;
    virtual ~Energy() = default;

    void WriteEnergy( FILE* out ) const;

private:
    double Total() const;
    double Nucleus() const;
    double Hartree() const;
    double Exch() const;
    double Corr() const;
    double Kinetic() const;

    double Integ( const Fun1D& fun ) const;

private:
    // DFT potencial
    const Pot& m_pot;

    // Atomic eigenstates
    const EigResult& m_eigResult;

    // Coordinates of the meshes nodes for numerical integration
    std::vector< double >  m_node;
};

#endif

