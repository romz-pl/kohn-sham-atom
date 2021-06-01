#ifndef RATOM_APPROXSOLVER_H
#define RATOM_APPROXSOLVER_H



//
// 1. It solves approximation problem on interval [a, b]
//    for function $f$ by Lobatto polynomials.
//    This is adaptive algorithm.
//
// 2. See file lobatto.h for definition of Lobatto polynomials
//        \psi_i: [-1, 1] -> R.
//
// 3. The Lobatto polynomials are defined on interval [-1, 1].
//    Hence, the mapping h: [-1, 1] -> [a, b] is introduced:
//       h(s) = (a + b) / 2 + s (a - b) / 2
//
// 4. Using mapping h, new basis functions are introduced:
//       phi_i(x) = \psi_i( h^{-1}(x) )
//    where h^{-1} is the inverse function of h, such that h^{1}( h(x) ) = x
//
// 5. For details see the book:
//    P. Solın, K. Segeth and I. Dolezzel, High-Order Finite Element Method (CHAPMAN & HALL/CRC, London, 2004).
//
// 6. Having the new functions ]phi_i, the approximation is searched in the form:
//        f(x) = \sum_{i=0}^M c_i \phi_i(x)
//    where c_i are expansion coefficients and M is the order of expansion
//
// 7. Expansion coefficients $c$ are searched imposing the condition typical
//    for Finite Element Method. The following equation
//       \int_a^b \phi_j(x) f(x) dx = \sum_{i=0}^M c_i \int_a^b \phi_i(x) \phi_j(x) dx
//    must hold for j=0..M
//
// 8. The above equation can be written in matrix form:
//        K c = b
//    where
//        b_i = \int_a^b \phi_j(x) f(x) dx
//    and
//        K_{i,j} = \int_a^b \phi_i(x) \phi_j(x) dx
//
// 9. It can be shown that matrix K is symmetric and positive definite.
//
// 10. It is required that the searched approximation mst give exact values
//     on the border of the interval [a, b]. In order to fullfill this requirements,
//     new function is introduced:
//         \tilde{f}(x) = f(x) - f(a) * \phi_0(x) - f(b) * \phi_1(x)
//
// 11. Knowing that:
//        a) \phi_0, \phi_1 are linear functions
//        b) \phi_0(a) = 1, \phi_0(b) = 0
//        c) \phi_1(a) = 0, \phi_1(b) = 1
//     it holds
//        \tilde{f}(a) = \tilde{f}(b) = 0
//
// 12. The above listed algorithm describes non-adaptive approximation.
//
// 13. Below the adaptive algorithm is described.
//
// 14. First, the non-adaptive approximation is searched and interval [a, b]
//
// 15. Then the error of approximation is calculated.
//     If the error is less then the threshold, the approximation process is stoped.
//
// 16. If the approximation error is greater then required, then the interval [a, b]
//     is divided into two intervals [a, w] and [a, b], where is the middle of
//     interval [a, b], i.e. w =(a + b) / 2
//
// 17. The for bot intervals [a, w] and [w, b] non adaptive approximation is searched.
//     The calculated approximations are put on the priority heap,
//     where elements of the heap are ordered according to calculated approximation error.
//
// 18. For next iteration in adaptive approximation, the element with the largest
//     approximation error is taken.
//
// 19. The procedure runs untill the largest element error is less then the threshold.
//
// 20. As a result, the input interval [a, b] is divided into the sub-intervals.
//     On each sub-interval the approximation is calculated.
//
// 21. Since the non-adaptive approximation assure the values on the border of the interval
//     are equal to values of approximated function $f$, it is surre that the
//     approximation found by adaptive algorithm is continous!
//
// 22. There is a heuristic. The adaptive algorithm forces some divisions of of input interval.
//
// 23. In total there are (M+1) basis functions with indeces $0,1,2,3..M$.
//     However, Basis functions \phi_0, \phi_1 are not used in approximation.
//     Hence, there remained (M-1) basis functions!
//     The matrix K, vectors b, c have dimension: (M-1)
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <cassert>
#include <cstdio>
#include "heap.h"
#include "heapelt.h"
#include "fun1D.h"
#include "clpmtxband.h"
#include "approx.h"
#include "funtilde.h"


class ApproxSolver
{
public:
    ApproxSolver( size_t M, const Fun1D& f );
    ~ApproxSolver() = default;

    Approx Run( double a, double b, double delta );

private:
    void Define( );
    std::vector< double > GetCoef( double a, double b ) const;
    void Solve( double a, double b );
    double CalcDelta( const Element& elt, const FunTilde &funTilde ) const;

private:

    // Right hand size of system of equations
    std::vector< double > m_b;

    // Searched approximation coefficients for one element
    std::vector< double > m_c;

    // Matrix of system of equations
    ClpMtxBand m_K;

    // Approximation degree
    const size_t m_M;

    // Approximated function
    const Fun1D& m_f;

    // Heap
    Heap< HeapElt > m_heap;
};

#endif
