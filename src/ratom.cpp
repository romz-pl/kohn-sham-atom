#include "ratom.h"


RAtom::RAtom( const std::string& path ) : m_db( path )
{


}

void RAtom::Run()
{
    m_solver.Scf();
}
