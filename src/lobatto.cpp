#include <cassert>
#include <cmath>
#include "lobatto.h"
#include "gauss.h"

const size_t Lobatto::MAXP = 11;
ClpMtx Lobatto::m_mtxS;
ClpMtx Lobatto::m_mtxK;

//
// Constructor
//
Lobatto::Lobatto()
{
    CalcS();
    CalcK();
}


//
// Evaluates integral S_{i,j} = $\int_{-1}^1 \psi_i'(x) \psi_j'(x) dx$.
// Integrals evaluated analiticaly.
//
void Lobatto::CalcS()
{
    m_mtxS.Assign( MAXP, MAXP, 0. );

    m_mtxS.Set( 0, 0 ) = 0.5;
    m_mtxS.Set( 1, 1 ) = 0.5;
    m_mtxS.Set( 0, 1 ) = m_mtxS.Set( 1, 0 ) = -0.5;

    for( size_t i = 2; i < m_mtxS.ColNo(); i++ )
        m_mtxS.Set( i, i ) = 1.;
}

//
// Evaluates integral K_{i,j} = $\int_{-1}^1 \psi_i(x) \psi_j(x) dx$.
// Integrals evaluated analiticaly.
//
void Lobatto::CalcK()
{
    m_mtxK.Assign( MAXP, MAXP, 0. );

    m_mtxK.Set( 0, 0 ) = 2. / 3.;
    m_mtxK.Set( 0, 1 ) = 1. / 3.;
    m_mtxK.Set( 0, 2 ) = -1. / sqrt( 6. );
    m_mtxK.Set( 0, 3 ) = 1. / ( 3. * sqrt( 10. ) );


    m_mtxK.Set( 1, 1 ) = 2. / 3.;
    m_mtxK.Set( 1, 2 ) = -1. / sqrt( 6. );
    m_mtxK.Set( 1, 3 ) = -1. / ( 3. * sqrt( 10. ) );

    m_mtxK.Set( 2, 2 ) = 2. / 5.;
    m_mtxK.Set( 2, 4 ) = -1. / ( 5. * sqrt( 21. ) );

    m_mtxK.Set( 3, 3 ) = 2. / 21.;
    m_mtxK.Set( 3, 5 ) = -1. / ( 21. * sqrt( 5. ) );

    m_mtxK.Set( 4, 4 ) =  2. / 45.;
    m_mtxK.Set( 4, 6 ) = -1. / ( 9. * sqrt( 77. ) );

    m_mtxK.Set( 5, 5 ) =  2. / 77.;
    m_mtxK.Set( 5, 7 ) = -1. / ( 33. * sqrt( 13. ) );

    m_mtxK.Set( 6, 6 ) =  2. / 117.;
    m_mtxK.Set( 6, 8 ) = -1. / ( 13. * sqrt( 165. ) );

    m_mtxK.Set( 7, 7 ) =  2. / 165.;
    m_mtxK.Set( 7, 9 ) = -1. / ( 15. * sqrt( 221. ) );

    m_mtxK.Set( 8, 8 ) =  2. / 221.;
    m_mtxK.Set( 8, 10 ) = -1. / ( 17. * sqrt( 285. ) );

    m_mtxK.Set( 9, 9 ) =  2. / 285.;

    m_mtxK.Set( 10, 10 ) =  2. / 357.;

    //
    // Copying into the lower triangle part
    for( size_t i = 0; i < m_mtxK.ColNo(); i++ )
    {
        for( size_t j = 0; j < i; j++ )
        {
            m_mtxK.Set( i, j ) = m_mtxK.Get( j, i );
        }
    }

    // assert( CheckMtxK() );

}

/*
//
// Returns integral $\int_{-1}^1 \psi_i(x) \psi_j(x) dx$.
// Integral is evaluated based on the Gaussian quadratures
//
double Lobatto::CalcNumericK( size_t i, size_t j )
{
    double v = 0;

    for( size_t n = 0; n < Gauss::Size(); n++ )
    {
        const double x = Gauss::X( n );
        const double w = Gauss::W( n );
        v += w * Basis( i, x ) * Basis( j, x );
    }
    return v;
}

//
// This checks the function CalcK.
// Returns true, if numericaly and analitically values of matric K are equal.
//
//
bool Lobatto::CheckMtxK( )
{
    const double eps = 1E-4;

    for( size_t i = 0; i < m_mtxK.RowNo(); i++ )
    {
        for( size_t j = 0; j < m_mtxK.ColNo(); j++ )
        {
            const double a = m_mtxK.Get( i, j );
            const double b = CalcNumericK( i, j );
            if( fabs( a - b ) > eps )
                return false;
        }
    }
    return true;
}
*/

//
// Returns the value of basis function $\psi_i(s)$
// First eleven (for i = 0, 1, ..., 10) Lobatto hierarchic shape functions.
//
double Lobatto::Basis( size_t i, double s )
{
    using Polynomial = double (*) (double);

    static const std::vector< Polynomial > poly =
    {
        Poly0,
        Poly1,
        Poly2,
        Poly3,
        Poly4,
        Poly5,
        Poly6,
        Poly7,
        Poly8,
        Poly9,
        Poly10
    };

    assert( i < poly.size() );
    const double v = poly[ i ]( s );
    return v;
}

//
//
//
double Lobatto::Poly0( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = 0.5;
    const double v = 1 - s;
    return c * v;
}

//
//
//
double Lobatto::Poly1( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = 0.5;
    const double v = 1 + s;
    return c * v;
}

//
//
//
double Lobatto::Poly2( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 3. / 2.) / 2.;
    const double s2 = s * s;
    const double v = s2 - 1;
    return c * v;
}

//
//
//
double Lobatto::Poly3( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 5. / 2.) / 2.;
    const double s2 = s * s;
    const double v = ( s2 - 1 ) * s;
    return c * v;
}

//
//
//
double Lobatto::Poly4( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 7. / 2.) / 8.;
    const double s2 = s * s;
    const double v = ( s2 - 1 ) * ( 5 * s2 - 1 );
    return c * v;
}

//
//
//
double Lobatto::Poly5( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 9. / 2.) / 8.;
    const double s2 = s * s;
    const double v = ( s2 - 1 ) * ( 7 * s2 - 3 ) * s;
    return c * v;
}

//
//
//
double Lobatto::Poly6( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 11. / 2. ) / 16.;
    const double s2 = s * s;
    // const double s4 = s2 * s2;
    // const double v = ( s2 - 1 ) * ( 21 * s4 - 14 * s2 + 1 );
    const double v = ( s2 - 1 ) * ( 21 * s2 * s2 - 14 * s2 + 1 );
    return c * v;
}

//
//
//
double Lobatto::Poly7( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 13. / 2. ) / 16.;
    const double s2 = s * s;
    //const double s4 = s2 * s2;
    //const double v = ( s2 - 1 ) * ( 33 * s4 - 30 * s2 + 5 ) * s;
    const double v = ( s2 - 1 ) * ( 33 * s2 * s2 - 30 * s2 + 5 ) * s;
    return c * v;
}

//
//
//
double Lobatto::Poly8( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 15. / 2. ) / 128.;
    const double s2 = s * s;
    //const double s4 = s2 * s2;
    //const double s6 = s4 * s2;
    //const double v = ( s2 - 1 ) * ( 429 * s6 - 495 * s4 + 135 * s2 - 5 );
    const double v = ( s2 - 1 ) * ( 429 * s2 * s2 * s2 - 495 * s2 * s2 + 135 * s2 - 5 );
    return c * v;
}

//
//
//
double Lobatto::Poly9( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 17. / 2. ) / 128.;
    const double s2 = s * s;
    //const double s4 = s2 * s2;
    //const double s6 = s4 * s2;
    //const double v = ( s2 - 1 ) * ( 715 * s6 - 1001 * s4 + 385 * s2 - 35 ) * s;
    const double v = ( s2 - 1 ) * ( 715 * s2 * s2 * s2 - 1001 * s2 * s2 + 385 * s2 - 35 ) * s;
    return c * v;
}

//
//
//
double Lobatto::Poly10( double s )
{
    assert( s >= -1 && s <= 1 );
    constexpr double c = sqrt( 19. / 2. ) / 256;
    const double s2 = s * s;
    const double s4 = s2 * s2;
    const double s6 = s4 * s2;
    const double s8 = s6 * s2;
    const double v = ( s2 - 1 ) * ( 2431 * s8 - 4004 * s6 + 2002 * s4 - 308 * s2 + 7 );
    return c * v;
}

