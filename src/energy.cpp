#include "energy.h"
#include "constants.h"
#include "gauss.h"
#include "paramdb.h"

//
// Constructor
//
Energy::Energy( const Pot& pot, const EigResult& eigResult , const std::vector< double >& node )
    : m_pot( pot )
    , m_eigResult( eigResult )
    , m_node( node )
{

}


//
// Returns total energy of system
//
double Energy::Total() const
{
    EnerTotal fun( m_pot );
    return m_eigResult.EigenEnerg() + Integ( fun );
}

//
// Returns interaction energy  of electrons with atomic core.
//
double Energy::Nucleus() const
{
    EnerNucleus fun( m_pot );
    return Integ( fun );
}

//
// Returns Hartree energy
//
double Energy::Hartree() const
{
    EnerHartree fun( m_pot );
    return Integ( fun );
}

//
// Returns exchange energy
//
double Energy::Exch() const
{
    EnerExch fun( m_pot );
    return Integ( fun );
}

//
// Returns correlation energy
//
double Energy::Corr() const
{
    EnerCorr fun( m_pot );
    return Integ( fun );
}

//
// Returns kinetic energy
//
double Energy::Kinetic() const
{
    EnerKinetic fun( m_pot );
    return m_eigResult.EigenEnerg() - Integ( fun );
}


//
// Returns integral for integrand "fun"
//
double Energy::Integ( const Fun1D& fun ) const
{
    double val = 0;

    for(size_t i = 0; i < m_node.size() - 1; ++i)
    {
        val += Gauss::Calc( fun, m_node[i], m_node[i + 1] );
    }
    return val;
}

//
// Writes information about energy int file
//
void Energy::WriteEnergy( FILE* out ) const
{
double v, ex, ec;

    fprintf(out, "\n\n");
    fprintf(out, "==========================================================\n");
    fprintf(out, "     E N E R G Y \n");
    fprintf(out, "----------------------------------------------------------\n");

    v = Total();
    fprintf(out, "\t Etot   = %15.7lf Ha =  %13.4lf eV\n", v, v * RATOM_EV);

    v = Kinetic();
    fprintf(out, "\t Ekin   = %15.7lf Ha =  %13.4lf eV\n", v, v * RATOM_EV);

    v = Hartree();
    fprintf(out, "\t Ecoul  = %15.7lf Ha =  %13.4lf eV\n", v, v * RATOM_EV);

    v = Nucleus();
    fprintf(out, "\t Eenucl = %15.7lf Ha =  %13.4lf eV\n", v, v * RATOM_EV);

    ex = Exch();
    fprintf(out, "\t Eexch  = %15.7lf Ha =  %13.4lf eV\n", ex, ex * RATOM_EV);

    ec = Corr();
    fprintf(out, "\t Ecorr  = %15.7lf Ha =  %13.4lf eV\n", ec, ec * RATOM_EV);

    fprintf(out, "\t Exc    = %15.7lf Ha =  %13.4lf eV\n", ex + ec, (ex + ec) * RATOM_EV);

    fprintf(out, "==========================================================\n");
}
