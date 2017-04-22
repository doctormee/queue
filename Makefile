#c compiler
CC = g++
#compiler flags
CFLAGS = -Wall -Werror -std=c++11 -I ./include/logic -I ./include/interface -I ./include/model
#source directory
#SDIR = ./src 
#include directory
#IDIR = ./include
#object directory
ODIR = ./src/obj

#all dependent files (names)
DEPS = main.h
#all objective targets (names)
_OBJ = main.o
#output exxecutable name
OUT = main
#full dependables list (with path)
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#full objectives list (with path)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#this target makes an objective module from corresponding .cpp file for each file in _OBJ
vpath
vpath %.h include/logic include/interface include/model
vpath %.cpp src/logic src/interface src/model
vpath %.o ./src/obj

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: build #test

build: $(OBJ) 
	$(CC) -o $(OUT) $^ $(CFLAGS)
	
gg: build 
	clear && ./$(OUT) && rm -rf *.o *~ $(OUT) *~

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *~ ./$(OUT) *~