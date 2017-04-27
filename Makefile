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
#test directory
TESTDIR = ./tests
#googletest directory
GTESTDIR = ../googletest/googletest
#user libraries directory
LIBDIR = ./libs
#all compiler flags
CPPFLAGS = -Wall -Werror -std=c++11 $(IDIRS:%=-I% )
#output executable names
OUT =
#test executable names
TEST = 
#all .cpp files 
CPPFILES = $(shell ls $(SRCDIRS)| grep .cpp)
#all test files
TESTFILES = $(shell ls $(TESTDIR)| grep .cpp)
#test obj files
TOBJ = $(TESTFILES:%.cpp=$(OBJDIR)/%.o)
#all header files
DEPS = $(shell ls $(IDIRS) | grep .h)
#all object files (full paths), derived from .cpp files
OBJFILES = $(CPPFILES:%.cpp=$(OBJDIR)/%.o)
#all source files
SRCFILES = $(CPPFILES) $(DEPS) $(TESTFILES)
#full objectives list (with path)
##OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
vpath
vpath %.h $(IDIRS)
vpath %.cpp $(SRCDIRS) $(TESTDIR)
vpath %.o $(OBJDIR)

all: build #test

$(DEPSDIR)/deps.make: $(SRCFILES)
	rm -rf $(DEPSDIR)/deps.make $(foreach cpp, $(filter-out %.h, $^), && $(CPPC) -MM -MT '$(patsubst %.cpp,$(OBJDIR)/%.o, $(notdir $(cpp)))' $(cpp) $(CPPFLAGS) >> $(DEPSDIR)/deps.make)
	#$(CPPC) $(CPPFLAGS) -MM $(filter-out %.h, $^) > $(DEPSDIR)/deps.make 

include $(DEPSDIR)/deps.make

$(OBJDIR)/%.o: %.cpp
	$(CPPC) -c $(CPPFLAGS) $< -o $@

build: $(OBJFILES) 
	$(CPPC) -o $(OUT) $^ $(CPPFLAGS)
	
gg: build 
	clear && ./$(OUT) && rm -rf *.o *~ $(OUT) *~
test: $(TOBJ) $(OBJFILES)
	$(CPPC) -isystem $(GTESTDIR)/include -pthread -c $(OBJFILES) -c $(TOBJ) $(LIBDIR)/libgtest.a -o $(TEST)

.PHONY: clean libtest

libtest:
	$(CPPC) -isystem $(GTESTDIR)/include -I$(GTESTDIR) -pthread -c $(GTESTDIR)/src/gtest-all.cc -o $(OBJDIR)/gtest-all.o
	ar -rv $(LIBDIR)/libgtest.a $(OBJDIR)/gtest-all.o

clean:
	rm -rf $(OBJDIR)/*.o *~ $(foreach exec, $(OUT), ./$(exec)) $(DEPSDIR)/deps.make