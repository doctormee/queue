#default cpp compiler
CPPC = g++
#include directories
IDIRS = include/logic include/interface include/model
#source directories
SRCDIRS = src/logic src/interface src/model
#object directory
OBJDIR = ./src/obj
#dependables file (deps.make) directory
DEPSDIR = ./src/deps
#all compiler flags
CPPFLAGS = -Wall -Werror -std=c++11 $(IDIRS:%=-I% )
#all .cpp files (names)
CPPFILES = main.cpp 
#all header files (names), derived from .cpp files
DEPS = $(filter-out main.h,$(CPPFILES:%.cpp=%.h))
#all object files (full paths), derived from .cpp files
OBJFILES = $(CPPFILES:%.cpp=$(OBJDIR)/%.o)
#all source files
SRCFILES = $(CPPFILES) $(DEPS) 
#output executable name
OUT = test
#full objectives list (with path)
##OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
vpath
vpath %.h $(IDIRS)
vpath %.cpp $(SRCDIRS)
vpath %.o $(OBJDIR)

all: build #test

$(DEPSDIR)/deps.make: $(SRCFILES)
	rm -rf $(DEPSDIR)/deps.make $(foreach cpp, $(filter-out %.h, $^), && $(CPPC) -MM -MT '$(patsubst %.cpp,$(OBJDIR)/%.o, $(notdir $(cpp)))' $(cpp) $(CPPFLAGS) >> $(DEPSDIR)/deps.make)

include $(DEPSDIR)/deps.make

$(OBJDIR)/%.o: %.cpp
	$(CPPC) -c $(CPPFLAGS) $< -o $@

build: $(OBJFILES)
	$(CPPC) -o $(OUT) $^ $(CPPFLAGS)
	
gg: build 
	clear && ./$(OUT) && rm -rf *.o *~ $(OUT) *~

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/*.o *~ ./$(OUT) $(DEPSDIR)/deps.make