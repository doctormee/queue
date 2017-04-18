CC = g++
CFLAGS = -Wall -Werror -std=c++11 -I$(IDIR)
SDIR = ./src
IDIR = ./include
ODIR = ./src/obj
_DEPS = hello.h
_OBJ = hello.o main.o
OUT = hello

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

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