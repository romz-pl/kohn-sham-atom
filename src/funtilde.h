#ifndef RATOM_FUNTILDE_H
#define RATOM_FUNTILDE_H

#include "element.h"
#include "fun1D.h"


class FunTilde
{
public:
    FunTilde( const Element& elt, const Fun1D& f, double a, double b );

    double Get( double s ) const;

    double CalcB( size_t i ) const;
    double IntegF2( ) const;


private:
    const Element& m_elt;
    const Fun1D& m_f;
    const double m_fa;
    const double m_fb;

};

#endif
