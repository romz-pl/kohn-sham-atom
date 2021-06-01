# Kohn-Sham for atom

## Introduction

`RAtom` solves nonlinear [Kohn-Sham](https://en.wikipedia.org/wiki/Kohn%E2%80%93Sham_equations) equation for an neutral atom.
The adaptive algorithm based on [finite element method (FEM)](https://en.wikipedia.org/wiki/Finite_element_method) is implemented.

## References

The implemented algorithm is described in my papers:

1. Z. Romanowski, *Adaptive solver of a Kohn-Sham equation for an atom*,
   Modelling and Simulation in Materials Science and Engineering vol. 17, 045001 (2009), [abstract](https://iopscience.iop.org/article/10.1088/0965-0393/17/4/045001/meta)
   
2. Z. Romanowski, *Application of h-adaptive, high order finite 
   element method to solve radial Schrödinger equation*,
   Molecular Physics vol. 107, pp. 1339-1348  (2009), [abstract](https://www.tandfonline.com/doi/abs/10.1080/00268970902873554)

3. Z. Romanowski, *A B-spline finite element solution of Kohn Sham equation for an atom*,
   Modelling and Simulation in Materials Science and Engineering vol. 16, p. 015003 (2008),
   [abstract](http://iopscience.iop.org/article/10.1088/0965-0393/16/1/015003/meta)

4. Z. Romanowski, *Numerical Solution of Kohn–Sham Equation for Atom*,
   Acta Physica Polonica B vol. 38, p. 3263 (2007),
   [full paper](http://www.actaphys.uj.edu.pl/fulltext?series=Reg&vol=38&page=3263)


## Algorithm description 

1. `RAtom` is the solver for non-linear Kohn-Sham equation, which is
   non-linear differential, second order, eigenvalue problem.

3. `RAtom` solves linear Kohn-Sham equation by Finite Element Method (FEM)
   with Lobatto polynomials as basis functions.

4. `RAtom` solves the non-linear Kohn-Sham equation iteratively
   by so called Self Consistent Field (SCF) procedure.

5. In order to calculate interaction potential in linear Kohn-Sham equation,
   Poisson equation is solved.

6. The Poisson equation is the differential, second order, equation.
   `RAtom `solves Poisson equation by Finite Element Method (FEM) with
   Lobatto polynomials as the basis functions.

7. For Poisson equation and Kohn-Sham equation, the electron density is needed.
   The electron density is represented (approximated), as the linear
   combination of Lobatto polynomials.

8. The distinguished feature of `RAtom` is the implemented h-adaptive procedure.
   The following problems are solved adaptively:
      a) Linear Kohn-Sham equation
      b) Poisson equation
      c) Approximation of electron density

9. The disctretization of linear Kohn-Sham equation leads to the generalized eigenvalue problem,
   which is solved by procedures from LAPACK libraries.

10. High order Gauss quadratures are applied in order to obtain 
    the total energy of atom with absolute accuracy of 1E-6 hartree.

11. The program RAtom is implemented in C++, it runs as a single thread. 


## How to build

1. In order to build RAtom, type `make` in the main directory.
First, the LAPACK library is compiled. It requires `gfortran` compiler.
Second, `RAtom` is compiled and it is compiled with `g++` compiler.

2. After compilation the binary file `ratom.x` is stored in `./bin` directory.
Program `ratom.x` requires one input parameter, which is a path to file
with keywords. The format of input file for `ratom.x` is very simple, and can be
figure out by checking the examples located in `exm` directory. The directory `doc`
containes description of the format and meaning of input file.

3. In order to check the functionality of `RAtom` program go to `./exm` directory.
There are 92 sub-directories. Each of the sub-directory
contains an input file named `atom.inp` for the atoms from Hydrogen to Uranium.
Additionally, each atom-specific directory contains referential solution stored in
`solution.dat.ref`.

4. In order to run all prepared examples (tests), go to `./exm` directory and type `./run`.
Obtained solutions (i.e. total energies and eigenvalues) are listed
in the file `solution.dat` in each sub-directory and compared to the referential data.

5. Directory `./src` contains the source code of `RAtom` plus `Makefile`. 

6. It is recommended to start reading the program `RAtom` from `src/main.cpp` file.

## Author
Zbigniew Romanowski, e-mail: romz@wp.pl
