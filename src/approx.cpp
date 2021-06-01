#include <algorithm>
#include <cmath>
#include "approx.h"
#include "lobatto.h"
#include "gauss.h"



//
// Constructor
//
Approx::Approx()
{

}



//
// Returns approximated value for "a <= x <= b".
//
double Approx::Get( double x ) const
{
    for(size_t i = 0; i < m_heap.Size(); i++)
    {
        const HeapElt& e = m_heap[i];
        if( e.Left() <= x && x <= e.Right() )
        {
            double val = 0;

            // s - local variable for element "e"
            const double s = e.Xinv(x);

            for(size_t j = 0; j < e.CoefSize(); j++)
                val += e.Coef( j ) * Lobatto::Basis(j, s);

            return val;
        }
    }

    assert(0);
    return 0;

}



std::vector< double > Approx::GetNode() const
{
    std::vector< double > node;

    for(size_t i = 0; i < m_heap.Size(); i++)
    {
        const HeapElt& e = m_heap[i];
        node.push_back( e.Left() );
        node.push_back( e.Right() );
    }

    std::sort(node.begin(), node.end());
    std::vector<double>::iterator newEnd;
    newEnd = std::unique(node.begin(), node.end());
    node.erase(newEnd, node.end());

    return node;

}


//
// Writes coefficients into the file
//
void Approx::WriteCoef( FILE* out ) const
{
size_t k, i;

    fprintf(out, "%4s \t %16s \t %16s", "i", "r_i", "r_{i+1}");
//    for(k = 0; k <= m_M; ++k)
//        fprintf(out, " \t              c_%lu", static_cast<unsigned long>(k));
    fprintf(out, "\n");

    for(i = 0; i < m_heap.Size(); ++i)
    {
        const HeapElt& e = m_heap[i];

        fprintf(out, "%4lu \t %16.6E \t %16.6E", static_cast<unsigned long>(i), e.Left(), e.Right() );
        for(k = 0; k < e.CoefSize(); ++k)
            fprintf(out, " \t %16.6E", e.Coef( k ) );
        fprintf(out, "\n");
    }

}

