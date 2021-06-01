#include <stdexcept>
#include <sstream>
#include "statedb.h"


StateDb::StateDb()
{
const std::string He = "1s2";
const std::string Ne = He + " 2s2 2p6";
const std::string Ar = Ne + " 3s2 3p6";
const std::string Kr = Ar + " 3d10 4s2 4p6";
const std::string Xe = Kr + " 4d10 5s2 5p6";
const std::string Rn = Xe + " 4f14 5d10 6s2 6p6";


    m_config.push_back( "EMPTY" );

    m_config.push_back( "1s1" );                      // 01, H
    m_config.push_back( He );                         // 02, He
    m_config.push_back( He + " 2s1" );                // 03, Li
    m_config.push_back( He + " 2s2" );                // 04, Be
    m_config.push_back( He + " 2s2 2p1" );            // 05, B
    m_config.push_back( He + " 2s2 2p2" );            // 06, C
    m_config.push_back( He + " 2s2 2p3" );            // 07, N
    m_config.push_back( He + " 2s2 2p4" );            // 08, O
    m_config.push_back( He + " 2s2 2p5" );            // 09, F

    m_config.push_back( Ne );                         // 10, Ne
    m_config.push_back( Ne + " 3s1" );                // 11, Na
    m_config.push_back( Ne + " 3s2" );                // 12, Mg
    m_config.push_back( Ne + " 3s2 3p1" );            // 13, Al
    m_config.push_back( Ne + " 3s2 3p2" );            // 14, Si
    m_config.push_back( Ne + " 3s2 3p3" );            // 15, P
    m_config.push_back( Ne + " 3s2 3p4" );            // 16, S
    m_config.push_back( Ne + " 3s2 3p5" );            // 17, Cl

    m_config.push_back( Ar );                         // 18, Ar
    m_config.push_back( Ar + " 4s1" );                // 19, K
    m_config.push_back( Ar + " 4s2" );                // 20, Ca
    m_config.push_back( Ar + " 3d1 4s2" );            // 21, Sc
    m_config.push_back( Ar + " 3d2 4s2" );            // 22, Ti
    m_config.push_back( Ar + " 3d3 4s2" );            // 23, V
    m_config.push_back( Ar + " 3d5 4s1" );            // 24, Cr
    m_config.push_back( Ar + " 3d5 4s2" );            // 25, Mn
    m_config.push_back( Ar + " 3d6 4s2" );            // 26, Fe
    m_config.push_back( Ar + " 3d7 4s2" );            // 27, Co
    m_config.push_back( Ar + " 3d8 4s2" );            // 28, Ni
    m_config.push_back( Ar + " 3d10 4s1" );            // 29, Cu
    m_config.push_back( Ar + " 3d10 4s2" );            // 30, Zn
    m_config.push_back( Ar + " 3d10 4s2 4p1" );        // 31, Ga
    m_config.push_back( Ar + " 3d10 4s2 4p2" );        // 32, Ge
    m_config.push_back( Ar + " 3d10 4s2 4p3" );        // 33, As
    m_config.push_back( Ar + " 3d10 4s2 4p4" );        // 34, Se
    m_config.push_back( Ar + " 3d10 4s2 4p5" );        // 35, Br

    m_config.push_back( Kr );                         // 36, Kr
    m_config.push_back( Kr + " 5s1" );                // 37, Rb
    m_config.push_back( Kr + " 5s2" );                // 38, Sr
    m_config.push_back( Kr + " 4d1 5s2" );            // 39, Y
    m_config.push_back( Kr + " 4d2 5s2" );            // 40, Zr
    m_config.push_back( Kr + " 4d4 5s1" );            // 41, Nb
    m_config.push_back( Kr + " 4d5 5s1" );            // 42, Mo
    m_config.push_back( Kr + " 4d5 5s2" );            // 43, Tc
    m_config.push_back( Kr + " 4d7 5s1" );            // 44, Ru
    m_config.push_back( Kr + " 4d8 5s1" );            // 45, Rh
    m_config.push_back( Kr + " 4d10" );               // 46, Pd
    m_config.push_back( Kr + " 4d10 5s1" );           // 47, Ag
    m_config.push_back( Kr + " 4d10 5s2" );           // 48, Cd
    m_config.push_back( Kr + " 4d10 5s2 5p1" );       // 49, In
    m_config.push_back( Kr + " 4d10 5s2 5p2" );       // 50, Sn
    m_config.push_back( Kr + " 4d10 5s2 5p3" );       // 51, Sb
    m_config.push_back( Kr + " 4d10 5s2 5p4" );       // 52, Te
    m_config.push_back( Kr + " 4d10 5s2 5p5" );       // 53, I

    m_config.push_back( Xe );                           // 54, Xe
    m_config.push_back( Xe + " 6s1" );                  // 55, Cs
    m_config.push_back( Xe + " 6s2" );                  // 56, Ba
    m_config.push_back( Xe + " 5d1 6s2" );              // 57, La
    m_config.push_back( Xe + " 4f1 5d1 6s2" );          // 58, Ce
    m_config.push_back( Xe + " 4f3 6s2" );              // 59, Pr
    m_config.push_back( Xe + " 4f4 6s2" );              // 60, Nd
    m_config.push_back( Xe + " 4f5 6s2" );              // 61, Pm
    m_config.push_back( Xe + " 4f6 6s2" );              // 62, Sm
    m_config.push_back( Xe + " 4f7 6s2" );              // 63, Eu
    m_config.push_back( Xe + " 4f7 5d1 6s2" );          // 64, Gd
    m_config.push_back( Xe + " 4f9 6s2" );              // 65, Tb
    m_config.push_back( Xe + " 4f10 6s2" );             // 66, Dy
    m_config.push_back( Xe + " 4f11 6s2" );             // 67, Ho
    m_config.push_back( Xe + " 4f12 6s2" );             // 68, Er
    m_config.push_back( Xe + " 4f13 6s2" );             // 69, Tm
    m_config.push_back( Xe + " 4f14 6s2" );             // 70, Yb
    m_config.push_back( Xe + " 4f14 5d1 6s2" );         // 71, Lu
    m_config.push_back( Xe + " 4f14 5d2 6s2" );         // 72, Hf
    m_config.push_back( Xe + " 4f14 5d3 6s2" );         // 73, Ta
    m_config.push_back( Xe + " 4f14 5d4 6s2" );         // 74, W
    m_config.push_back( Xe + " 4f14 5d5 6s2" );         // 75, Re
    m_config.push_back( Xe + " 4f14 5d6 6s2" );         // 76, Os
    m_config.push_back( Xe + " 4f14 5d7 6s2" );         // 77, Ir
    m_config.push_back( Xe + " 4f14 5d9 6s1" );         // 78, Pt
    m_config.push_back( Xe + " 4f14 5d10 6s1" );        // 79, Au
    m_config.push_back( Xe + " 4f14 5d10 6s2" );        // 80, Hg
    m_config.push_back( Xe + " 4f14 5d10 6s2 6p1" );    // 81, Tl
    m_config.push_back( Xe + " 4f14 5d10 6s2 6p2" );    // 82, Pb
    m_config.push_back( Xe + " 4f14 5d10 6s2 6p3" );    // 83, Bi
    m_config.push_back( Xe + " 4f14 5d10 6s2 6p4" );    // 84, Po
    m_config.push_back( Xe + " 4f14 5d10 6s2 6p5" );    // 85, At

    m_config.push_back( Rn );                            // 86, Rn
    m_config.push_back( Rn + " 7s1" );                   // 87, Fr
    m_config.push_back( Rn + " 7s2" );                   // 88, Ra
    m_config.push_back( Rn + " 6d1 7s2" );               // 89, Ac
    m_config.push_back( Rn + " 6d2 7s2" );               // 90, Th
    m_config.push_back( Rn + " 5f2 6d1 7s2" );           // 91, Pa
    m_config.push_back( Rn + " 5f3 6d1 7s2" );           // 92, U


}

//
// Returns electronic configuration for atom with "proton" protons
//
std::vector< std::string > StateDb::GetConfig( size_t proton ) const
{
    if( proton < 1 || proton > 92 )
    {
        throw std::invalid_argument( "Invalid value of argument 'Atom_Proton'. It must be between 1 and 92." );
    }

    std::vector< std::string > ret;
    std::string buf;
    const std::string name = m_config[ proton ];
    std::stringstream ss( name );

    while( ss >> buf )
        ret.push_back( buf );

    return ret;
}
