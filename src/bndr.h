#ifndef RATOM_BNDR_H
#define RATOM_BNDR_H

//
// Boundary conditions
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//




//
// Vertex boundary conditions
//
enum BndrType
{
    BndrType_Emp = 0, // Empty
    BndrType_Dir, // Dirichlet
    BndrType_Neu // Neumann
};


class Bndr
{
public:
    Bndr() : m_type( BndrType_Emp ), m_val( 0 ) { }

    Bndr( BndrType type, double val ) : m_type( type ), m_val( val ) { }

    ~Bndr() = default; 

public:
    // Type of boundary condition
    BndrType m_type;

    // Value of boundary contition
    double m_val;
};

#endif

