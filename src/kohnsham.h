#ifndef RATOM_KOHNSHAM_H
#define RATOM_KOHNSHAM_H

//
// 1. Class KohnSham solves the linear radial Kohn-Sham equation of the form
//
//   (A)     -\frac{1}{2} R_{n,L}''(r) + (V(r) + L*(L + 1)/(2 r^2) ) R_{n,L}(r) = \lambda_{n,L} R_{n,L}(r)
//
//   where:
//      a) the domain of the equation is the finite interval [0, r_c], and r_c is the atom radius
//      b) function V(r) is the interaction potential
//      c) parameter L is the angular quantum number
//      d) function R(r) is searched eigenfunction
//      e) \lambda is searched eigenvalue.
//
// 2. For each parameter L the equation (A) is solved, i.e. the smallest eigenvalues and
//    corresponding eigenfunctions are calculated.
//
// 3. The eigenvalues are indexed by index $n$, where $n=0$ corresponds to the smallest eigenvalue.
//
// 4. Hence, eigenvalues, and eigenfunctions are indexed by $L$ and $n$.
//
// 5. Equation (A) is solved by class EigProb.
//
// 6. Function KohnSham::Get returns the electron density:
//
//        \rho(r) = \sum_{L=0}^{Lmax} \sum_{n=0}^{N_L} f_{n,L} R_{n,L}^2(r)
//
//   where f_{n,l} is the occupation factor of state (n,l) defined in class StateSet and StateDb.
//
// 7. In the source code, for angular quantum number L, the "ell" name is used.
//
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include <cstddef>
#include <vector>
#include <cassert>
#include "fun1D.h"
#include "eigprob.h"
#include "eigresult.h"


class KohnSham : public Fun1D
{
public:
    KohnSham( );
    ~KohnSham( );

    EigResult Solve( const Fun1D& pot );
    double Get( double r ) const;
    void WriteEigen( ) const;


private:
    void CalcOcc();

private:
    // One solver for each angular quantum number ell
    std::vector< EigProb > m_eigProb;

    // Number of calculated eigenvalues for each angular quantum number ell
    std::vector< size_t > m_eigNo;
};

#endif

