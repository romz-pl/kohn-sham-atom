#ifndef RATOM_POISSONPROB_H
#define RATOM_POISSONPROB_H

//
// 1. This class solves one-dimennsional Poisson equation, which is
//    ordinary differential equation of second order.
//
// 2. The Poisson equation has the form:
//
//    (A)    \frac{1}{r} \frac{d^2}{d r^2} [r V_h(r)] = -4 \pi \tilde{\rho}(r)
//
// 3. The Poisson equation is defined on the finite interval r \in [0, r_c],
//    where $r_c$ defines the "atom's radius".
//
// 4. In equation (A) function \tilde{\rho}:[0, r_c] -> R is electron density.
//
// 5. The searched function in equation (A) is function V_h:[0, r_c] -> R,
//    which is called Hartree potential.
//
// 6. The equation (A) is augmented with Dirichlet boundary conditions.
//
// 7. It can be shown that the soloution V_h is given as an integral:
//
//    (H)     V_h(r) = 4 \pi [ \frac{1}{r} \int_0^r t^2 \tilde{\rho}(t) dt  +
//                                + \int_r^{infty} t \tilde{\rho}(t) dt ]
//
// 8. The class PoissonProp does NOT solve equation (A). Instead, it solves equation
//
//    (B)     -\frac{d^2}{d r^2} [U_h(r)] = \rho(r) / r
//
//    where the function U_h is defined as follows
//
//    (C)     U_h(r) = r V_h(r),
//
//    and the function \rho is given by equation:
//
//    (D)    \rho(r) = 4 \pi r^2 \tilde{\rho}(r)
//
//    One can obtain equation (B) from equation (A) substituting from equation (C)
//
//            V_h(r) = U_h(r) / r
//
//    and simplyfying the differential equation (A).
//
// 9. Equation (B) is augmented with two Dirchlet boundary conditions:
//
//       U_h(0) = 0 * V_h(0) = 0
//       U_h(r_c) = r_c * V_h(r_c)
//
// 10. From the assumption, it is known that electron density \rho is non-zero
//     on the interval [0, r_c] only. Hence, based on the equation (H), we have
//
//     V_h(r_c) = 4 \pi \frac{1}{r_c} \int_0^{r_c} t^2 \tilde{\rho}(t) dt = N
//
//     where N is the number of electrons in the atom.
//
// 11. Hence, the class PoissonProb solves the following ordinary differential equation
//
//     (E-1)       -\frac{d^2}{d r^2} [U_h(r)] = \rho(r) / r
//
//     with Dirichlet boundary conditions
//
//     (E-2)       U_h(0) = 0
//     (E-3)       U_h(r_c) = N
//
// 12. The equation (E-1) with Dirichlet boundary conditions (E-2), (E-3) is solved
//     by Finite Element Method with Lobatto polynomials as basis functions.
//
// 13. There are two algorithm implemented:
//        a) adaptive
//        b) non-adaptive
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include "fun1D.h"
#include "mesh.h"
#include "eltinfo.h"
#include "clpmtxband.h"


class PoissonProb
{
public:
    PoissonProb() = default;

    void Solve( const Fun1D& rho );
    double GetUh( double r ) const;
    double GetVh( double r ) const;

private:
    void DefineMesh();
    void SolveNonAdapt( const Fun1D& rho );
    void SolveAdapt( const Fun1D& rho );

    EltInfo MaxMinCoef() const;
    void Malloc();
    void Assemble( const Fun1D& rho );

    double CalcB( const Fun1D& rho, const Element& e, size_t ni ) const;
    double CalcS( const Element& e, size_t ni, size_t nj ) const;


private:
    // Mesh for Finite Element Method
    Mesh m_mesh;

    // Stifness matrix
    ClpMtxBand m_s;

    // Right hand side vektor for equation Sy = b
    std::vector< double > m_b;

    // Coefficient vector y.
    std::vector< double > m_y;
};


#endif
