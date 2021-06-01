#ifndef RATOM_ELTINFO_H
#define RATOM_ELTINFO_H

//
// Information about the element in the mesh.
// It is used by the adaptive algorithm.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include <cstddef>

class EltInfo
{
public:
    EltInfo() : m_maxMinCoef( 0 ), m_eltId( -1 ) {}
    ~EltInfo() = default;


    // Needed for sorting
    bool operator< ( const EltInfo& e ) const
    {
        return ( m_eltId < e.m_eltId );
    }


    // Needed for duplicate elimination
    bool operator== ( const EltInfo& e ) const
    {
        return ( e.m_eltId == m_eltId );
    }

    void Set( double maxMinCoef, size_t eltId )
    {
        m_maxMinCoef = maxMinCoef;
        m_eltId = eltId;
    }

    double GetMaxMinCoef() const
    {
        return m_maxMinCoef;
    }

    size_t GetEltId() const
    {
        return m_eltId;
    }


private:
    // The largest from the smallest coefficients
    double m_maxMinCoef;

    // Element ID
    size_t m_eltId;
};

#endif

