#include <cmath>
#include "nonlinks.h"
#include "rhomix.h"
#include "energy.h"




//
// Iterative solution of nonlinear Kohn-Sham equation, SCF loop
//
void NonLinKs::Scf( )
{
    const size_t scfMaxIter = ParamDb::GetSize_t( "Scf_MaxIter" );
    size_t iter = 1;

    m_rho.Init();

    printf( "********************   S C F   L O O P   ********************\n" );

    KohnSham ks;
    while( true )
    {
        printf( "*  SCF=%3lu   ", static_cast< unsigned long >( iter ) );

        m_pot.SetRho( m_rho );
        const EigResult eigResult = ks.Solve( m_pot );

        if( IsFinished( eigResult ) || iter == scfMaxIter )
        {
            printf( "*  SCF-ITERATIONS = %lu\n", static_cast< unsigned long >( iter ) );
            printf( "***********   S C F   L O O P   F I N I S H E D   ***********\n" );

            WriteResult( ks, eigResult );

            break;
        }


        const Rho rhoOld = m_rho;

        const RhoMix mix( ks, rhoOld );
        m_rho.Calc( mix );

        iter++;
    }

}



//
// Returns "true", if required accuarcy reached.
//
bool NonLinKs::IsFinished( const EigResult& eigResult ) const
{
    const double scfEnerDiff = ParamDb::GetDouble( "Scf_Diff" );
    static double sumOld = 0; // This variable MUST BE "static"

    const double sumNew = eigResult.EigenSum();
    const double diff = fabs( sumNew - sumOld );
    sumOld = sumNew;

    printf( "EigenSum = %18.10lf    Diff = %18.10E\n", sumNew, diff );
    fflush( stdout );

    return ( diff < scfEnerDiff );
}

//
// Write results into files
//
void NonLinKs::WriteResult( const KohnSham& ks, const EigResult& eigResult ) const
{
    StateSet::WriteSates( stdout, eigResult );

    // Calculates required energy of atom
    Energy energy( m_pot, eigResult, m_rho.GetNode( ) );
    energy.WriteEnergy( stdout );

    m_rho.Write();
    ks.WriteEigen();
}


