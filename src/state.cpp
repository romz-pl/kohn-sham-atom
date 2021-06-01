#include <sstream>
#include "state.h"



//
// Constructor
//
State::State( const std::string &name ) : m_name( name )
{
    std::stringstream ss( name );
    char charEll;

    ss >> m_n >> charEll >> m_occ;
    if( ss.fail() )
    {
        throw std::runtime_error( "Format of state name is not correct! Check data in class StateDb." );
    }

    m_ell = ChangeToNumber( charEll );
    if( m_n + 1 < m_ell )
    {
        throw std::runtime_error( "StateDb is wrong! Check data in class StateDb." );
    }

    //
    // Rearrange the main quantum number to values related to the smallest calculated eigenvalues
    // This "shifts" allows using main quantum number "n" as the index of the calculated smallest eigenvalues
    m_n = static_cast< size_t >( m_n - m_ell - 1 );
}


size_t State::ChangeToNumber( char charEll ) const
{
    size_t ret = 0;

    switch( charEll )
    {
        case 's': ret = 0; break;
        case 'p': ret = 1; break;
        case 'd': ret = 2; break;
        case 'f': ret = 3; break;

        default:
            throw std::runtime_error( "Angular quantum number s, p, d, f are supported only." );
        break;
    }
    return ret;
}

