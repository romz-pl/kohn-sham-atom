#ifndef RATOM_LOBATTO_H
#define RATOM_LOBATTO_H

//
// Lobatto functions and integral evaluation
//
// 1. Lobatto polynomials are described in following book:
//    P. Solın, K. Segeth and I. Dolezzel, High-Order Finite Element Method (CHAPMAN & HALL/CRC, London, 2004).
//
// 2. Lobato polynomials are defined on reference interval [-1, 1] by
//    normalized Legendre polynomial.
//
// 3. Fortunately, there are explicite expresions for Lobato polynomials \psi(s):
//         \psi_0(s) = (1 − s)/2
//         \psi_1(s) = (1 + s)/2
//         \psi_2(s) = \frac{1/2} \sqrt{ \frac{3/2} } (s^2 − 1)
//         \psi_3(s) = \frac{1/2} \sqrt{ \frac{5/2} } (s^2 − 1) s
//         \psi_4(s) = \frac{1/8} \sqrt{ \frac{7/2} } (s^2 − 1) (5 s^2 − 1)
//         \psi_5(s) = \frac{1/8} \sqrt{ \frac{9/2} } (s^2 − 1) (7 s^2 − 3)s
//         \psi_6(s) = \frac{1/16} \sqrt{ \frac{11/2} } (s^2 − 1) (21 s^4 − 14 s^2 + 1)
//         \psi_7(s) = \frac{1/16} \sqrt{ \frac{13/2} } (s^2 − 1) (33 s^4 − 30 s^2 + 5) s
//         \psi_8(s) = \frac{1/128} \sqrt{ \frac{15/2} } (s^2 − 1) (429 s^6 − 495 s^4 + 135 s^2 − 5)
//         \psi_9(s) = \frac{1/128} \sqrt{ \frac{17/2} } (s^2 − 1) (715 s^6 − 1001 s^4 + 385 s^2 − 35) s
//         \psi_{10}(s) = \frac{1/256} \sqrt{ \frac{7/2} } (s^2 − 1) (2431 s^8 − 4004 s^6 + 2002 s^4 − 308 s^2 + 7)
//  These values are evaluated by function Lobatto::Basis
//
// 4. Moreover, we have:
//                 | 1   for k = 0
//    \psi_k(-1) = | 0   for k = 1
//                 | 0   for k > 1
//
//                 | 0   for k = 0
//    \psi_k(+1) = | 1   for k = 1
//                 | 0   for k > 1
//
// 5. Given explicite formula for Lobatto polynomials, one can evalulate integral
//         K_{i,j} = \int_{-1}^{1} \psi_i(s) \psi_j(s) ds
//    Elements of matrix K are returned by function Lobatto::GetK
//    and they are evaluated by function Lobatto::CalcK
//
//  6. Furthermore, one can evalulate integral between derivatives of Lobatto integrals
//         S_{i,j} = \int_{-1}^{1} \psi_i'(s) \psi_j'(s) ds
//    Elements of matrix K are returned by function Lobatto::GetS
//    and they are evaluated by function Lobatto::CalcS
//
// 7. Values of matrix K and S are listed in my paper
//    Z. Romanowski "Application of h-adaptive, high order finite element method to
//    solve radial Schrodinger equation", Molecular Physics, vol. 107, pp. 1339-1348 (2009).
//
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include <cassert>
#include <vector>
#include <cstddef>
#include "clpmtx.h"

class Lobatto
{
public:
    Lobatto();
    ~Lobatto() = default;

    static double Basis( size_t i, double s );

    static double GetK( size_t i, size_t j );
    static double GetS( size_t i, size_t j );

private:
    static void CalcS();
    static void CalcK();
    // static bool CheckMtxK( );
    // static double CalcNumericK( size_t i, size_t j );

    static double Poly0( double s );
    static double Poly1( double s );
    static double Poly2( double s );
    static double Poly3( double s );
    static double Poly4( double s );
    static double Poly5( double s );
    static double Poly6( double s );
    static double Poly7( double s );
    static double Poly8( double s );
    static double Poly9( double s );
    static double Poly10( double s );

public:
    // Maximal element degree
    static const size_t MAXP;

private:
    // Matrix S
    // S_{i,j} = \int_{-1}^{1} \psi_i'(s) \psi_j'(s) ds
    static ClpMtx m_mtxS;

    // Matrix K
    // K_{i,j} = \int_{-1}^{1} \psi_i(s) \psi_j(s) ds
    static ClpMtx m_mtxK;

};


//
// Returns element of matrix K
//
inline
double Lobatto::GetK( size_t i, size_t j )
{
    assert( i < MAXP );
    assert( j < MAXP );

    return m_mtxK.Get( i, j );
}

//
// Returns element of matrix S
//
inline
double Lobatto::GetS( size_t i, size_t j )
{
    assert( i < MAXP );
    assert( j < MAXP );

    return m_mtxS.Get( i, j );
}


#endif

