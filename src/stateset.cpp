#include "stateset.h"
#include "constants.h"
#include "paramdb.h"
#include <stdexcept>

// Initialization of static variable
const StateDb StateSet::m_stateDb;
std::vector< State > StateSet::m_state;

//
// Constructor
//
StateSet::StateSet( )
{
    const size_t proton = ParamDb::GetSize_t( "Atom_Proton" );

    const std::vector< std::string > config = m_stateDb.GetConfig( proton );

    for( const std::string& v : config )
        m_state.push_back( State( v ) );
}


//
// Returns referenc for eigenstated defined by pair of quantum numbers(l, n)
//
const State& StateSet::Find( size_t l, size_t n )
{
    for( const State& s : m_state )
    {
        if( ( s.L() == l ) && ( s.N() == n ) )
            return s;
    }

    throw std::runtime_error( "Funtion 'StateSet::Find': There is no state (n, l)" );
    return m_state.front();
}

//
// Returns occupation factor for state (l, n)
//
double StateSet::Occ( size_t l, size_t n )
{
    return Find( l, n ).Occ();
}

//
// Returns name of state (l, n)
//
std::string StateSet::Name( size_t l, size_t n )
{
    return Find( l, n ).Name();
}


//
// Returns maximal angular quantum number
//
size_t StateSet::GetLmax()
{
size_t lMax = 0;

    for( const State& s : m_state )
    {
        if( s.L() > lMax )
            lMax = s.L();
    }
    return lMax + 1;
}


//
// Returns maximum main quantum number of considered states
// for given angular momentum number "l".
//
size_t StateSet::GetNmax( size_t l )
{
size_t nMax = 0;

    for( const State& s : m_state )
    {
        if( s.L() != l )
            continue;

        if( s.N() > nMax )
            nMax = s.N();
    }
    return nMax + 1;
}

//
// Writes information about all states into file "out"
//
void StateSet::WriteSates( FILE* out, const EigResult& eigResult )
{
    fprintf(out, "\n\n");
    fprintf(out, "===================================================================\n");
    fprintf(out, "     E I G E N V A L U E S\n");
    // fprintf(out, "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +\n");
    fprintf(out, "-------------------------------------------------------------------\n");
    fprintf(out, "%16s %19s %20s\n", "State", "Value [Ha]", "Value [eV]");
    fprintf(out, "-------------------------------------------------------------------\n");
    for( const State& s : m_state )
    {

        const double eigVal = eigResult.GetEigVal( s.L(), s.N() );
        fprintf(out, "   (n=%lu, L=%lu) %-5s %15.7lf Ha = %15.7lf eV\n",
            static_cast<unsigned long>(s.N()),
            static_cast<unsigned long>(s.L()),
            s.Name().c_str(),
            eigVal,
            eigVal * RATOM_EV);
    }
    fprintf(out, "===================================================================\n");
}



