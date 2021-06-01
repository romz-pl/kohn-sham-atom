#include "eigresult.h"
#include "stateset.h"

#include <cassert>

//
// Returns energy of eigenstates including occupation factor and degenercy.
//
double EigResult::EigenEnerg() const
{
    double ret = 0;

    for( const Trio& t : m_trio )
    {
        const double occ = StateSet::Occ( t.m_L, t.m_n );
        ret += t.m_eig * occ;
    }

    return ret;
}

//
// Returns sum of eigenvalues of states.
// Non occupied einegstates are counted as well.
//
double EigResult::EigenSum( ) const
{
    double ret = 0;

    for( const Trio& t : m_trio )
    {
        ret += t.m_eig;
    }

    return ret;
}

double EigResult::GetEigVal( size_t L, size_t n ) const
{
    for( const Trio& t : m_trio )
    {
        if( t.m_L == L && t.m_n == n )
            return t.m_eig;
    }
    assert( 0 );
    return 0;
}

