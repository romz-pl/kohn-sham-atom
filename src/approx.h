#ifndef RATOM_APPROX_H
#define RATOM_APPROX_H

//
// Solution of the approximation
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include <cassert>
#include <cstdio>
#include "mesh.h"
#include "heap.h"
#include "heapelt.h"
#include "fun1D.h"
#include "element.h"
#include "clpmtxband.h"



class Approx : public Fun1D
{
public:
    Approx();
    virtual ~Approx() = default;

    virtual double Get( double x ) const;



    std::vector< double > GetNode() const;

    void WriteCoef( FILE* out ) const;

    void Set( const Heap< HeapElt >& heap )
    {
        m_heap = heap;
    }

private:

    Heap< HeapElt > m_heap;
};


#endif

