#ifndef RATOM_RATOM_H
#define RATOM_RATOM_H


//
// 1. RAtom is the solver for non-linear Kohn-Sham equation, which is
//    non-linear differential, second order, eigenvalue problem.
//
// 2. This class is the wrapper for all required resources.
//
// 3. RAtom solves linear Kohn-Sham equation by Finite Element Method (FEM)
//    with Lobatto polynomials as basis functions.
//
// 4. RAtom solves the non-linear Kohn-Sham equation iteratively
//    by so called Self Consistent Field (SCF) procedure.
//
// 5. In order to calculate interaction potential in linear Kohn-Sham equation,
//    Poisson equation is solved.
//
// 6. The Poisson equation is the differential, second order, equation.
//    RAtom solves Poisson equation by Finite Element Method (FEM) with
//    Lobatto polynomials as the basis functions.
//
// 7. For Poisson equation and Kohn-Sham equation, the electron density is needed.
//    The electron density is represented (approximated), as the linear
//    combination of Lobatto polynomials.
//
// 8. The distinguished feature of RAtom is the implemented h-adaptive procedure.
//    The following problems are solved adaptively:
//       a) Linear Kohn-Sham equation
//       b) Poisson equation
//       c) Approximation of electron density
//
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include "paramdb.h"
#include "nonlinks.h"
#include "lobatto.h"
#include "gauss.h"
#include "stateset.h"

class RAtom
{
public:
    RAtom( const std::string& path );
    ~RAtom( ) = default;

    void Run( );

private:
    // These three objects must be created
    ParamDb m_db;
    Lobatto m_lobatto;
    Gauss m_gauss;
    StateSet m_stateSet;

    // Non Linear Kohn-Sham solver
    NonLinKs m_solver;


};


#endif
