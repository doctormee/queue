#default cpp compiler
CPPC = g++
#include directories
IDIRS = include/logic include/interface include/model $(GTESTDIR)/include
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
CPPFLAGS = -std=c++11 $(IDIRS:%=-I% ) --coverage -Wall -Werror
#test flags
TESTFLAGS = -isystem $(GTESTDIR)/include $(LIBDIR)/libgtest.a 
#output executable names
OUT =
#test executable names
TEST = test
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

.PHONY: clean libtest cov swipe

libtest:
	@ echo Making a gtest library in $(LIBDIR)...
	@ $(CPPC) -isystem $(GTESTDIR)/include -I$(GTESTDIR) -pthread -c $(GTESTDIR)/src/gtest-all.cc -o $(OBJDIR)/gtest-all.o
	@ ar -rv $(LIBDIR)/libgtest.a $(OBJDIR)/gtest-all.o
	@ echo Done!

clean:
	@ echo Cleaning...
	@ rm -rf $(OBJDIR)/* *~ $(foreach exec, $(OUT) $(TEST), ./$(exec)) $(DEPSDIR)/deps.make
	@ echo Done!
cov:
	@ Echo Making coverage...
	@ lcov -c -d . -o cov.info
	@ genhtml -o html cov.info
	@ rm cov.info
	@ open html/index.html
	@ make swipe
	@ echo Done!
swipe:
	@ rm -rf $(OBJDIR)/*.gcda

$(OBJDIR)/%.o: %.cpp
	@ echo Making $@
	@ $(CPPC) -c $(CPPFLAGS) $< -o $@

$(DEPSDIR)/deps.make: $(SRCFILES)
	@ echo Making a dependencies list
	@ rm -rf $(DEPSDIR)/deps.make $(foreach cpp, $(filter-out %.h, $^), && $(CPPC) -MM -MT '$(patsubst %.cpp,$(OBJDIR)/%.o, $(notdir $(cpp)))' $(cpp) $(CPPFLAGS) >> $(DEPSDIR)/deps.make)
	@echo Done!
	@ #$(CPPC) $(CPPFLAGS) -MM $(filter-out %.h, $^) > $(DEPSDIR)/deps.make 

include $(DEPSDIR)/deps.make

build: $(OBJFILES) 
	@ echo Compiling objective files into $(OUT) executable(s)
	@ $(CPPC) -o $(OUT) $^ $(CPPFLAGS)
	@ echo Done!
	
gg: build 
	clear && ./$(OUT) && rm -rf *.o *~ $(OUT) *~

test: $(TOBJ) $(OBJFILES)
	@ echo Compiling objective files into $(TEST) test executable
	@ $(CPPC) $^ -o $(TEST) $(CPPFLAGS) $(TESTFLAGS) 
	@ echo Done!
	@ echo Now launching tests
	@ ./$(TEST)
