#include <cassert>
#include "heapelt.h"


//
// Constructor
//
HeapElt::HeapElt( double left, double right, double delta, const std::vector< double >& c )
    : m_left( left )
    , m_right( right )
    , m_delta( delta )
    , m_coef( c )
{
    assert( right > left) ;

    m_c1 = 0.5 * ( m_right + m_left );
    m_c2 = 0.5 * ( m_right - m_left );
}


//
// Comparison operator required for heap operations
//
bool HeapElt::operator< ( const HeapElt& e ) const
{
    return ( m_delta < e.m_delta );
}

//
// Returns local variable "s" corresponding to global variable "x"
//
double HeapElt::Xinv( double x ) const
{
    const double s = ( x - m_c1 ) / m_c2;

    // In principle, it should be -1 <= s <= 1
    // However, due to finite prcision some rounding errors apears.
    // Hence, there must be two checks below.

    if( s < -1.0 )
        return -1.0;

    if( s > 1.0 )
        return 1.0;

    return s;
}

