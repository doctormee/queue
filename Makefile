#default compiler
CPPC = g++
#include directories
IDIRS = include/logic include/interface include/model
#source directories
SRCDIRS = src/logic src/interface src/model
#object directory
OBJDIR = ./src/obj
#all compiler flags
CPPFLAGS = -Wall -Werror -std=c++11 $(IDIRS:%=-I% )
#all header files (names)
DEPS = main.h
#all .cpp files (names)
CPPFILES = main.cpp
#all source files
SRCFILES = $(CPPFILES) $(DEPS) 
#output executable name
OUT = main
#full objectives list (with path)
##OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
vpath
vpath %.h $(IDIRS)
vpath %.cpp $(SRCDIRS)
vpath %.o $(OBJDIR)

all: build #test

$(OBJDIR)/%.o: %.cpp
	$(CPPC) -c $(CPPFLAGS) $< -o $@

deps.make: $(SRCFILES)
	$(CPPC) -MM $(filter-out %.h,$^) $(CPPFLAGS) > deps.make

include deps.make

build: $(CPPFILES:%.cpp=$(OBJDIR)/%.o) 
	$(CPPC) -o $(OUT) $^ $(CPPFLAGS)
	
gg: build 
	clear && ./$(OUT) && rm -rf *.o *~ $(OUT) *~

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*.o *~ ./$(OUT) ./deps.make