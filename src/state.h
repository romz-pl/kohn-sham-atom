#ifndef RATOM_STATE_H
#define RATOM_STATE_H

//
// Electron state of the atom.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <cstddef>
#include <string>

class State
{
public:
    explicit State( const std::string& name );
    ~State( ) = default;

    std::string Name() const { return m_name; }
    size_t Occ() const { return m_occ; }
    size_t N() const { return m_n; }
    size_t L() const { return m_ell; }

private:
    size_t ChangeToNumber( char charEll ) const;

private:
    // Main quantum number
    size_t m_n;

    // Angular quantum number
    size_t m_ell;

    // Occupation factor. Number of electrons on the state.
    size_t m_occ;

    // Name of the state
    const std::string m_name;
};


#endif

