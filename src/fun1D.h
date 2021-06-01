#ifndef RATOM_FUN1D_H
#define RATOM_FUN1D_H


/** \brief Represents function from R into R.
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/


class Fun1D
{
public:
    Fun1D(void) { }
    virtual ~Fun1D(void) { }

    virtual double Get(double x) const = 0;
};

#endif

