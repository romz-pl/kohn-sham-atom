#ifndef RATOM_EIGPROB_H
#define RATOM_EIGPROB_H

//
// 1. Class EigProb solves differential eigenvalue problem, with form
//
//     -\gamma u''(r) + (g(r) + L*(L + 1)/(2 r^2) ) u(r) = \lambda u(r)
//
// 2. The function g is given.
//    Constant: \gamma = 0.5
//    Parameter: L=0,1,2... is the angular quantum number
//
// 3. The domain of the problem is defined on the finite interval:
//        r \in [0, r_c]
//
// 3. The above equation is augmented by zero Dirichlet bounday conditions:
//        \lim_{r->0} u(r) = \lim_{r->\infty} u(r) = 0
//
// 4. EigProb seaches the smallest eigenvalues \lambda are releted eigenfunctions u(x).
//
// 5. The used mesh is the same for all searched eigenfunctions.
//
// 6. The problem can be solved on fixed mesh (non-adaptive).
//    The solution is searched based on the Finite Element Method with Lobatto
//    polynomials as basis functions.
//
// 7. The problem can be solved adaptively on changing mesh.
//
// 8. In adaptive algorithm, the element of mesh with the largest error is selected,
//    then it is splited into two parts, and new parts are added into the mesh.
//
// 9. Let us consider the mesh T. Based on this mesh T let us evaluate a few smallest
//    eigenvalues and corresponding eigenvectors applying the FEM.
//    Since the algorithm is based on the finite element method
//    the components of eigenvectors are the expansion coefficients in Lobatto basis
//    functions. For each eigenvector $i$ and for each element $e$ of mesh $T$, the smallest
//    expansion coefficient can be found. Let denote this coefficient as $c_{i,e}$. Out of these
//    components $c_{i,e}$, for given $i$, the largest coefficient
//
//              c^∗_i = max_{e \in T} {|c_{i,e}|}
//
//    is identified. Since the mesh $T$ is finite, then for each eigenvalue $i$ there exists
//    element $e^∗_i \in T$ corresponding to the coefficient $c^∗_i$ . In our algorithm all elements $e^∗_i$
//    for all $i$ are marked to split. Each marked element is split into two halves and new
//    mesh $T'$ is obtained. The calculations are repeated for new mesh $T'$. The adaptive
//    loop is repeated until coefficients $c^∗_i$ are less than prescribed value.
//
// 10. The implemented algorithm is described in my paper:
//     Z. Romanowski:
//     Application of h-adaptive, high order finite element method to solve radial Schrodinger equation,
//     Molecular Physics, vol. 107, pp. 1339-1348  (2009).
//
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include <cstddef>
#include <vector>
#include <string>
#include "eltinfo.h"
#include "fun1D.h"
#include "eltinfo.h"
#include "clpmtxband.h"
#include "clpmtx.h"
#include "mesh.h"


class EigProb
{
public:
    EigProb( size_t ell );
    ~EigProb() = default;

    void Solve( const Fun1D &g, size_t eigNo );
    void SolveAdapt( const Fun1D& g, size_t eigNo );

    double GetEigVal( size_t eig ) const;
    double GetEigFun( size_t eig, double x ) const;


    void WriteEigFun( const std::string &path, size_t eig, size_t pointNo ) const;

private:
    void Malloc();
    void Assemble( const Fun1D &g );
    void MaxMinCoef( std::vector< EltInfo >& eltInfo ) const;

    double CalcS( const Fun1D& g, const Element& e, size_t ni, size_t nj ) const;
    double CalcK( const Element& e, size_t ni, size_t nj ) const;

    double GetPot( const Fun1D &g, double r ) const;


private:
    // Stifness matrix
    ClpMtxBand m_s;

    // Vector with calculated eigenvalues
    std::vector< double > m_w;

    // Matrix with calculated eignvectors
    ClpMtx m_z;

    // Overlap matrix
    ClpMtxBand m_o;

    Mesh m_mesh;

    // Angular quantum number
    const size_t m_ell;

    // Constant \gamma
    static const double m_gamma;
};

#endif

