#include <cmath>
#include <cassert>
#include "gauleg.h"

//
// Given the lower and upper limits of integration x1 and x2, and given n, this routine returns
// arrays x[1..n] and w[1..n] of length n, containing the abscissas and weights of the Int1DGauss-
// Legendre n-point quadrature formula.
// "eps" - accuracy of Gauss coordinates calculations
//
void gauleg( double x1, double x2, std::vector< double >& x, std::vector< double >& w, size_t n )
{
// const double eps = 100.0 * DBL_MIN;
const double eps = 1E-14;
size_t m, j, i;
double z1, z, xm, xl, pp, p3, p2, p1; // High precision is a good idea for this routine.
const double pi = 4 * atan(1.);

    assert(x.size() == n);
    assert(w.size() == n);

    m = (n + 1) / 2; // The roots are symmetric in the interval, so
    xm = 0.5 * (x2 + x1); //we only have to find half of them.
    xl = 0.5 * (x2 - x1);
    for(i = 1; i <= m; i++) // Loop over the desired roots.
    {
        z = cos(pi * (i - 0.25) / (n + 0.5));
        // Starting with the above approximation to the ith root, we enter the main loop of
        // refinement by Newton's method.
        do
        {
            p1 = 1.0;
            p2 = 0.0;
            for(j = 1; j <= n; j++) //Loop up the recurrence relation to get the
            {
                p3 = p2; // Legendre polynomial evaluated at z.
                p2 = p1;
                p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3) / j;
            }
            // p1 is now the desired Legendre polynomial. We next compute pp, its derivative,
            // by a standard relation involving also p2, the polynomial of one lower order.
            pp = n * (z * p1 - p2) / (z * z - 1.0);
            z1 = z;
            z = z1 - p1 / pp; // Newton's method.
        }
        while(fabs(z - z1) > eps);

        x[i - 1] = xm - xl * z; // Scale the root to the desired interval,
        x[n - i] = xm + xl * z; // and put in its symmetric counterpart.
        w[i - 1] = 2.0 * xl / ((1.0 - z * z) * pp * pp); //Compute the weight
        w[n - i] = w[i - 1]; //and its symmetric counterpart.
    }
}


