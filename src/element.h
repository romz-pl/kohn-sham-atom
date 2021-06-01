#ifndef RATOM_ELEMENT_H
#define RATOM_ELEMENT_H


//
// One dimensional element in the mesh.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <cstddef>
#include <vector>


class Element
{
public:
    Element();
    ~Element() = default;

    double X( double s ) const;
    double Xinv( double x ) const;
    double Jac() const;

    size_t P() const;
    size_t DofNo() const;
    size_t PsiId( size_t i ) const;

    void Set( double x0, double x1, size_t p );

public:
    // DOF - DEGREE OF FREEDOM
    // The length of this vector is (p + 1), where "p" is the maximal degree of applied Lobatto functions
    std::vector< int > m_dof;

private:
    // (x[m+1] + x[m]) / 2
    double m_c1;

    // Jacobian: (x[m+1] - x[m]) / 2
    double m_c2;
};

//
//
//
inline
size_t Element::P() const
{
    return m_dof.size() - 1;
}

//
//
//
inline
double Element::X( double s ) const
{
    return m_c1 + s * m_c2;
}

//
// It returns s = X^{-1}
//
inline
double Element::Xinv( double x ) const
{
    const double s = ( x - m_c1 ) / m_c2;

    // To avoid the rounding errors
    if( s < -1 )
        return -1;

    // To avoid the rounding errors
    if( s > 1 )
        return 1;

    return s;
}

//
//
//
inline
size_t Element::DofNo() const
{
    return m_dof.size();
}

//
//
// Jacobian
//
inline
double Element::Jac() const
{
    return m_c2;
}

#endif

