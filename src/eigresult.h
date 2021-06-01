#ifndef RATOM_EIGRESULT_H
#define RATOM_EIGRESULT_H

#include <cstddef>
#include <vector>

class EigResult
{
private:
    struct Trio
    {
        Trio( size_t L, size_t n, double eig ) : m_L( L ), m_n( n ), m_eig( eig ) {}
        const size_t m_L;
        const size_t m_n;
        const double m_eig;
    };

public:
    EigResult( ) = default;

    void Add( size_t L, size_t n, double eig )
    {
        m_trio.push_back( Trio( L, n, eig) );
    }

    double EigenEnerg() const;
    double EigenSum() const;
    double GetEigVal( size_t L, size_t n ) const;

private:

    std::vector< Trio > m_trio;
};

#endif
