#include <algorithm>
#include <cmath>
#include "approxsolver.h"
#include "funtilde.h"
#include "lobatto.h"
#include "gauss.h"


// Constructor
//
//
ApproxSolver::ApproxSolver( size_t M, const Fun1D& f )
    : m_M( M - 1 )
    , m_f( f )
{
    assert( M >= 2 );

    Define( );
}


//
// Defines approximation problem
//
void ApproxSolver::Define( )
{
    // Since basis functions \phi_0, \phi_1 are not used in the approximation,
    // there are only 2 not 3 superdiagonals!
    const size_t superDiagNo = 2;

    m_b.assign( m_M, 0 );
    m_c.assign( m_M, 0 );
    m_K.Assign( m_M, superDiagNo, 0, 0 );


    for( size_t i = 0; i < m_M; i++ )
    {
        const size_t jMax = std::min( i + superDiagNo, m_M - 1 );
        for( size_t j = i; j <= jMax; j++ )
        {
            // Basis functions \phi_0, \phi_1 are skipped.
            // Only basis functions with indexes $2, 3, ... , M$ are considered.
            // Hence, in order to keep consistency, "2" must be added.
            m_K.Set( i, j ) = Lobatto::GetK( i + 2, j + 2 );
        }
    }
}



//
// Calculates the nodes a = r_0 < r_1 < .. r_N = b, such that approxiamtion error
// for each interval [r_i, r_{i+1}] is less than "delta"
//
Approx ApproxSolver::Run( double a, double b, double maxDelta )
{
    const size_t forcedIter = 10;
    m_heap.Clear();
    Solve( a, b );

    size_t ii = 0;
    while( true )
    {
        // This is my heuristic. Make always some adaptive iterations.
        if( ii > forcedIter )
        {
            if( m_heap.Top().Delta() < maxDelta )
                break;
        }

        ii++;
        const HeapElt e = m_heap.Pop();

        a = e.Left();
        b = e.Right();
        const double w = 0.5 * ( a + b );

        Solve( a, w );
        Solve( w, b );
    }

    Approx approx;
    approx.Set( m_heap );
    return approx;
}


//
// Returns approximation coefficients
//
std::vector< double > ApproxSolver::GetCoef( double a, double b ) const
{
    std::vector< double > coef( m_M + 2 );

    // Coefficients for $\psi_0$ and $\psi_1$
    coef[ 0 ] = m_f.Get( a );
    coef[ 1 ] = m_f.Get( b );

    for( size_t i = 0; i < m_M; i++) // Remaining coefficients
        coef[ i + 2 ] = m_c[ i ];

    return coef;
}


//
// Solves approximation problem on interval [a,b].
//
void ApproxSolver::Solve( double a, double b )
{
    assert( b > a );
    Element elt;

    // Define the element. Order "0" is not used!
    elt.Set( a, b, 0 );

    FunTilde funTilde( elt, m_f, a, b );

    for( size_t i = 0; i < m_M; i++ )
    {
        m_b[ i ] = funTilde.CalcB( i + 2 );
    }

    m_K.SolveSymPos( m_b, m_c );


    const double delta = CalcDelta( elt, funTilde );
    const std::vector< double > coef = GetCoef( a, b );
    m_heap.Push( HeapElt( a, b, delta, coef ) );
}

//
// Returns approximation error.
//
double ApproxSolver::CalcDelta( const Element& elt, const FunTilde& funTilde ) const
{

    double kij, sum = 0;
    for( size_t i = 0; i < m_M; i++)
    {
        for(size_t j = 0; j < m_M; j++)
        {
            // Upper triangular matrix is stored only
            if( j >= i )
                kij = m_K.Get( i, j );
            else
                kij = m_K.Get( j, i );
            sum += m_c[ i ] * m_c[ j ] * kij;
        }
    }
    sum *= elt.Jac();

    const double delta = sqrt( fabs( funTilde.IntegF2() - sum ) );
    return delta;



    /*
     * Zbigniew Romanowski: 1st Feb 2017
     * This would be better measure of the approximation!
     * This is
     *     sqrt{ \int_a^b [ \tilde{f}(x) - approx(x) ]^2 dx }
     *
    Approx approx;
    approx.Set( m_M, m_heap );

    double res = 0;
    for( size_t n = 0; n < m_gauss.Size(); n++ )
    {
        const double s = m_gauss.X( n );
        const double w = m_gauss.W( n );
        const double x = elt.X( s );
        const double v = funTilde.Get( s ) - approx.Get( x );
        res += w * v * v;
    }
    res *= elt.Jac();

    res = sqrt( res );

    return res;
    */
}
