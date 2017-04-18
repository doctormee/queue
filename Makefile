#c compiler
CC = g++
#compiler flags
CFLAGS = -Wall -Werror -std=c++11 -I$(IDIR) 
#source directory
SDIR = ./src 
#include directory
IDIR = ./include
#object directory
ODIR = ./src/obj

#all dependent files (names)
_DEPS = hello.h
#all objective targets (names)
_OBJ = hello.o main.o
#output exxecutable name
OUT = hello
#full dependables list (with path)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#full objectives list (with path)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#this target makes an objective module from corresponding .cpp file for each file in _OBJ
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: build #test

build: $(OBJ)
	$(CC) -o $(OUT) $^ $(CFLAGS)
	
gg: build 
	clear && ./$(OUT) && rm -f $(ODIR)/*.o *~ $(OUT) $(IDIR)/*~

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(OUT) $(IDIR)/*~