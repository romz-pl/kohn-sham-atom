#
# Makefile for RAtom
# Zbigniew ROMANOWSKI
# e-mail: romz@wp.pl
# https://sourceforge.net/p/ratom
#

.PHONY : ratom clean

#
# RATOM depends on LAPACK and BLAS libraries.
#
ratom : lib/lapack-3.7.0/liblapack.a lib/lapack-3.7.0/librefblas.a
	cd build && $(MAKE)


#
# Compile LAPACK and BLAS from source code.
# It requires gfortran compiler.
#
lib/lapack-3.7.0/liblapack.a lib/lapack-3.7.0/librefblas.a : 
	(cd lib; \
	tar -zxf lapack-3.7.0.tgz; \
	cd lapack-3.7.0; \
	cp make.inc.example make.inc; \
	$(MAKE) blaslib; \
	$(MAKE) lapacklib)

clean :
	cd build && $(MAKE) clean
	rm -rf lib/lapack-3.7.0

