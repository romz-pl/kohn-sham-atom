#ifndef RATOM_NONLINKS_H
#define RATOM_NONLINKS_H


//
// 1. Class NonLinKs solves the non-linear radial Kohn-Sham equation of the form
//
//   (A)     -\frac{1}{2} R_{n,L}''(r) + (V(r) + L*(L + 1)/(2 r^2) ) R_{n,L}(r) = \lambda_{n,L} R_{n,L}(r)
//
// 2. The linear radial Kohn-Sham equation is solved by KohnSham equation.
//
// 3. The equation (A) is non-linear, since the interaction potential V(r) depends on
//    the electron density \rho, and \rho is calculated from the searched eigenfunctions R_{n,L}.
//    Hence, interaction potential V(r) depends on searched eigenfunctions R_{n,L}.
//
// 4. The equation (A) is solved iteratively. The iterative procedure is called
//    in quantum physics: Self Consisten Field (SCF).
//
// 5. As the measure of convergence, the sum of all calculated eigenfunctions is used.
//    For each iteration in SCF the sum of searched eigenfunctions is calculated S_j, and
//    compared to the value from the previous iteration S_{j-1}. If the difference
//        |S_j - S_{j-1}|
//    is less then the value specified by parameter Scf_Diff, then the SCF stops.
//
// 6. In order to increase the covergence, i.e. in order to decrease the number of iterations
//    required to obtain the covergence limit, mixing of density electron procedure is used.
//    For j-th SCF iteration, the lectron density \rho_j is calculated based on the input electron
//    density. Mixing means, then as the input electron density in (j+1) SCF iteration
//    the linear combination of electron densities in (j-1) and j steps are used
//
//       \rho = scfMix * \rho_{cur} + ( 1.0 - scfMix ) * \rho_{old}
//
// 7. The mixing coefficient scfMix is defined by input parameter Scf_Mix. See the class RhoMix.
//
// 8. SCF procedure needs the input electron density for the very first iteration.
//    This initial electron density is calculated by function Rho::Init()
//
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include "rho.h"
#include "pot.h"
#include "kohnsham.h"



class NonLinKs
{
public:
    NonLinKs( ) = default;
    ~NonLinKs( ) = default;

    void Scf();

private:

    bool IsFinished( const EigResult &eigResult ) const;

    void WriteResult( const KohnSham &ks, const EigResult &eigResult ) const;

private:
    // Interaction potential
    Pot m_pot;

    // Electron density
    Rho m_rho;
};

#endif

