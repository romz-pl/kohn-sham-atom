#ifndef RATOM_STATESET_H
#define RATOM_STATESET_H


/** \brief Stores infomation about eigenfunctions of atom
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/

#include "state.h"
#include <vector>
#include <cstddef>
#include "statedb.h"
#include "eigresult.h"

class StateSet
{
public:
    StateSet( );
    ~StateSet() = default;

    static size_t GetLmax();
    static size_t GetNmax(size_t l);

    static double Occ(size_t l, size_t n);
    static std::string Name(size_t l, size_t n);

    static void WriteSates( FILE* out, const EigResult &eigResult );

private:
    static size_t Key(size_t l, size_t n);
    static const State& Find(size_t l, size_t n);

private:
    // Set of states
    static std::vector< State > m_state;

    // The ground electronic configurations of the neutral elements
    const static StateDb m_stateDb;
};

#endif

