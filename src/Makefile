
#
# Makefile for g++ compiler
#

# Path to LAPACK library
LAPACK := ../lib/lapack-3.7.0/liblapack.a

# Path to BLAS library
BLAS := ../lib/lapack-3.7.0/librefblas.a

# Name of GNU compiler
CXX := g++

#Compilation flags
# CXXFLAGS := -std=c++11 -DNDEBUG -O2 -funroll-all-loops -ffast-math -Wall
CXXFLAGS := -std=c++11 -DNDEBUG -O2 -Wall -mtune=native -march=native
# CXXFLAGS := -std=c++11 -g -O -Wall -D_DEBUG

# Required libraries 
CXXLIB = $(LAPACK) $(BLAS) -lgfortran

# Name of resulted binaries
BINOUT := ../bin/ratom.x

# Directory with source code
VPATH := ../src/

# Source files (listed in alphabetical order)
SOURCE := approx.cpp
SOURCE += approxsolver.cpp
SOURCE += clpmtxband.cpp
SOURCE += clpmtx.cpp
SOURCE += corrlyp.cpp
SOURCE += corrvwn.cpp
SOURCE += eigprob.cpp
SOURCE += eigresult.cpp
SOURCE += element.cpp
SOURCE += energy.cpp
SOURCE += exchb88.cpp
SOURCE += exchbbe.cpp
SOURCE += exchs.cpp
SOURCE += exchslater.cpp
SOURCE += funener.cpp
SOURCE += funtilde.cpp
SOURCE += gauleg.cpp
SOURCE += gauss.cpp
SOURCE += heapelt.cpp
SOURCE += kohnsham.cpp
SOURCE += lobatto.cpp
SOURCE += main.cpp
SOURCE += mesh.cpp
SOURCE += nonlinks.cpp
SOURCE += paramdb.cpp
SOURCE += poissonprob.cpp
SOURCE += pot.cpp
SOURCE += ratom.cpp
SOURCE += rho.cpp
SOURCE += state.cpp
SOURCE += statedb.cpp
SOURCE += stateset.cpp
SOURCE += xc.cpp

#Object files
OBJECT := $(SOURCE:.cpp=.o)

#Dependency files
DEP := $(SOURCE:.cpp=.d)


$(BINOUT) : $(OBJECT)
	$(CXX) $(CXXFLAGS) $(OBJECT) $(CXXLIB) -o $(BINOUT)

-include $(DEP)

%.d : %.cpp
	@$(CC) -MM $(CPPFLAGS) $< | sed 's#\(.*\)\.o: #\1.o \1\.d: #g' > $@


%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<


.PHONY : clean


clean :
	rm -f *.o *.d $(BINOUT)


