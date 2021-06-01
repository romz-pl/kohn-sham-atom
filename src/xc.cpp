#include "xc.h"
#include "constants.h"
#include <cmath>


//
// Constructor
//
Xc::Xc(void)
{
}

//
// Destructor
//
Xc::~Xc(void)
{
}

//
// Returns difference betwee energy density and potential
// This function always works. Somtimes it is possible to give
// more efficient version of this function
//
double Xc::EdiffV(double rho, double gRho) const
{
    return E(rho, gRho) - V(rho, gRho);
}

//
// Helhepr function
//
double Xc::Rs(double rho)
{
    return pow(3. / (4. * RATOM_PI * rho), 1. / 3.);
}


