# Makefile

CCC = /usr/bin/g++
CC = /usr/bin/gcc
CFLAGS = -ansi -O3
HOME = /Users/jk525/src/labmc
BINDIR = /Users/jk525/bin
PWD = ${HOME}
INCLUDE = -I${PWD}

SRC_LABMC = main.cc parameter.cc flowlaw.cc state.cc statmodel.cc sm_mnbrak.cc sm_brent.cc gauss_jordan.cc util.cc error.cc
OBJ_LABMC = ${SRC_LABMC:.cc=.o}

.c.o: 
	$(CCC) $(CFLAGS) -c  $< $(INCLUDE)
.cc.o: 
	$(CCC) $(CFLAGS) -c  $< $(INCLUDE)

labmc: $(OBJ_LABMC)
	$(CCC) $(CFLAGS) -o $@ $(OBJ_LABMC) -lm
	cp $@ $(BINDIR)
