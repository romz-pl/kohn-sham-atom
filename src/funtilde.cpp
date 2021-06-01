#include "funtilde.h"
#include "lobatto.h"
#include "gauss.h"



FunTilde::FunTilde( const Element& elt, const Fun1D& f, double a, double b )
    : m_elt( elt )
    , m_f( f )
    , m_fa( f.Get( a ) )
    , m_fb( f.Get( b ) )
{

}

double FunTilde::Get( double s ) const
{
    const double x = m_elt.X( s );
    return m_f.Get( x ) - m_fa * Lobatto::Basis( 0, s ) - m_fb * Lobatto::Basis( 1, s );
}

double FunTilde::CalcB( size_t i ) const
{
    double b = 0;
    for( size_t n = 0; n < Gauss::Size(); n++ )
    {
        const double s = Gauss::X( n );
        const double w = Gauss::W( n );
        b += w * Lobatto::Basis( i, s ) * Get( s );
    }
    return b;
}

//
// Returns value of integral for function f^2.
// Gauss quadratures applied.
//
double FunTilde::IntegF2( ) const
{
    double v, w, s, res = 0;

    for(size_t n = 0; n < Gauss::Size(); n++)
    {
        s = Gauss::X( n );
        w = Gauss::W( n );
        v = Get( s );
        res += w * v * v;
    }
    return m_elt.Jac() * res;
}
