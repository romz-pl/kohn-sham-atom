#ifndef RATOM_HEAPELT_H
#define RATOM_HEAPELT_H

//
// Element of heap. Used for adaptive algorithm.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include <vector>
#include <cstddef>

class HeapElt
{
public:
    HeapElt( double left, double right, double delta, const std::vector<double>& c );
    ~HeapElt() = default;

    double Xinv( double x ) const;
    bool operator< ( const HeapElt& e ) const;

    double Left() const { return m_left; }
    double Right() const { return m_right; }
    double Delta() const { return m_delta; }

    double Coef( size_t i ) const { return m_coef[ i ]; }
    size_t CoefSize( ) const { return m_coef.size(); }

private:
    // Left end of interval
    double m_left;

    // Right end of inteval
    double m_right;

    // Approximation error for interval
    double m_delta;

    // Coefficientt of linear transformation (mapping) X
    double m_c1, m_c2;


    // Vector of interpolation coefficients
    std::vector< double > m_coef;
};

#endif

