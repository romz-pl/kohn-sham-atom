#ifndef RATOM_STATEDB_H
#define RATOM_STATEDB_H


//
// Database of state names
//
// The ground electronic configurations of the neutral atoms
// http://physics.nist.gov/PhysRefData/DFTdata/configuration.html
//
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//

#include <string>
#include <vector>
#include <cstddef>

class StateDb
{
public:
    StateDb();
    ~StateDb() = default;

    std::vector< std::string > GetConfig( size_t proton ) const;

private:
    std::vector< std::string > m_config;

};


#endif
