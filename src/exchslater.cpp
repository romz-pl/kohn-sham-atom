#include <cmath>
#include "exchslater.h"
#include "constants.h"

//
// Constructor
//
ExchSlater::ExchSlater(void) : m_c(-pow(1.5 / RATOM_PI, 2. / 3.))
{
}

//
// Destructor
//
ExchSlater::~ExchSlater(void)
{
}

//
// Potencial
//
double ExchSlater::V(double rho, double /* gRho */) const
{
    if(rho == 0)
        return 0;

    return m_c / Rs(rho);
}

//
// Energy density
//
double ExchSlater::E(double rho, double /* gRho */) const
{
    if(rho == 0)
        return 0;

    return 0.75 * m_c / Rs(rho);
}

//
// Difference. Optimized version :-)
//
double ExchSlater::EdiifV(double rho, double /* gRho */) const
{
    if(rho == 0)
        return 0;

    return -0.25 * m_c / Rs(rho);
}


