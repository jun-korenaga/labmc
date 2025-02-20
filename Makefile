# Makefile

CCC = /usr/bin/g++
CC = /usr/bin/gcc
CFLAGS = -ansi -O3
HOME = /Users/jk525/src/labmc
BINDIR = /Users/jk525/bin
PWD = ${HOME}
INCLUDE = -I${PWD}

# note: the following five files are not included in this public distribution:
# sm_mnbrak.cc is based on NR's mnbrak.c 
# sm_brent.cc is based on NR's brent.c
# gaussj.cc is identical to NR's gaussj.c
# gasdev.cc is identical to NR's gasdev.c
# ran2.cc is identical to NR's ran2.c

SRC_LABMC = main.cc parameter.cc flowlaw.cc state.cc statmodel.cc sm_mnbrak.cc sm_brent.cc gaussj.cc ran2.cc gasdev.cc util.cc error.cc
OBJ_LABMC = ${SRC_LABMC:.cc=.o}

.c.o: 
	$(CCC) $(CFLAGS) -c  $< $(INCLUDE)
.cc.o: 
	$(CCC) $(CFLAGS) -c  $< $(INCLUDE)

labmc: $(OBJ_LABMC)
	$(CCC) $(CFLAGS) -o $@ $(OBJ_LABMC) -lm
	cp $@ $(BINDIR)
