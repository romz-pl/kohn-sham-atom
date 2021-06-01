#include "kohnsham.h"
#include "paramdb.h"
#include "stateset.h"

//
// Constructor
//
KohnSham::KohnSham( )
{
    const size_t Lmax = StateSet::GetLmax();

    for( size_t ell = 0; ell < Lmax; ell++ )
    {
        m_eigProb.push_back( EigProb( ell ) );
    }
}

//
// Destructor
//
KohnSham::~KohnSham()
{
}

//
// Solves linear eqigenvalue problem
//
EigResult KohnSham::Solve( const Fun1D& pot )
{
    const bool adapt = ParamDb::GetBool( "Solver_EigAdapt" );

    EigResult eigResult;
    for(size_t ell = 0; ell < m_eigProb.size(); ell++)
    {
        const size_t eigNo = StateSet::GetNmax( ell );
        if( adapt )
        {
            m_eigProb[ ell ].SolveAdapt( pot, eigNo );
        }
        else
        {
            m_eigProb[ ell ].Solve( pot, eigNo );
        }

        // Sets eigenvalues of states
        for( size_t n = 0; n < eigNo; n++ )
        {
            const double eigVal = m_eigProb[ ell ].GetEigVal( n );
            eigResult.Add( ell, n, eigVal );
        }
    }

    return eigResult;
}

//
// Returns value of electron density for radius "r"
//
double KohnSham::Get( double r ) const
{
    const double rc	= ParamDb::GetDouble( "Atom_Rc" );
    const size_t Lmax = StateSet::GetLmax();

    if( r >= rc )
        return 0;

    double rho = 0;

    // For all quantum angular menetum numbers
    for( size_t ell = 0; ell < Lmax; ell++ )
    {
        double rhoL = 0;

        const size_t eigNo = StateSet::GetNmax( ell );

        // For all states for fixed "ell"
        for( size_t n = 0; n < eigNo; n++ )
        {
            const double occ = StateSet::Occ( ell, n );
            if( occ > 0 )
            {
                const double rnl = m_eigProb[ ell ].GetEigFun( n, r ); // R_{n, \ell}(r)
                rhoL += occ * rnl * rnl;
            }
        }

        // Sum up all constituents
        rho += rhoL;
    }

    return rho;
}



//
// Writes eigenfunctions into file.
//
void KohnSham::WriteEigen( ) const
{
    const size_t eigNode = ParamDb::GetSize_t( "Out_EigNode" );
    if( eigNode < 1 )
    {
        throw std::runtime_error( "Out_EigNode must be greater then zero." );
    }

    const size_t Lmax = StateSet::GetLmax();

    // For each angular quantum number
    for( size_t ell = 0; ell < Lmax; ell++ )
    {
        // For each state for fixed "L"
        const size_t eigNo = StateSet::GetNmax( ell );
        for( size_t n = 0; n < eigNo; n++ )
        {

            std::string path = ParamDb::GetString( "Out_EigPath" );
            path += ".";
            path += StateSet::Name( ell, n );

            m_eigProb[ ell ].WriteEigFun( path, n, eigNode );

        }
    }
}
