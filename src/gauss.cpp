#include <cassert>
#include <cmath>
#include "gauss.h"
#include "gauleg.h"
#include "lobatto.h"

const size_t Gauss::m_deg = 3 * ( Lobatto::MAXP - 1 );
std::vector< double > Gauss::m_w;
std::vector< double > Gauss::m_x;

//
// Constructor
// deg - degree of 1D Gaussiona quadrature
//
Gauss::Gauss()
{
    m_w.resize( m_deg );
    m_x.resize( m_deg );

    ::gauleg( -1, 1, m_x, m_w, m_deg );
}



//
// Returns integral of function "f" for interval [a, b]
//
double Gauss::Calc( const Fun1D& f, double a, double b )
{
    // Scaling from interval [a, b] to interval [-1, 1].
    const double q = 0.5 * ( a + b );
    const double p = 0.5 * ( b - a );

    double sum = 0;

    for( size_t i = 0; i < m_deg; i++ )
    {
        sum += m_w[ i ] * f.Get( p * m_x[ i ] + q );
    }

    return p * sum;
}
