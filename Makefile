#operating system
UNAME = $(shell uname)
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
#googletest installing directory
GTESTIDIR = ../googletest
#googletest directory
GTESTDIR = $(GTESTIDIR)/googletest
#user libraries directory
LIBDIR = ./libs
#all compiler flags
CPPFLAGS = -std=c++11 $(IDIRS:%=-I% ) -Wall -Werror --coverage
#test flags
TESTFLAGS = -isystem $(GTESTDIR)/include $(LIBDIR)/libgtest.a
#adding -pthread if not on mac 
ifneq ($(UNAME),Darwin)
TESTFLAGS += -pthread
endif
#file with int main name
MAIN = main
#output executable names
OUT = priority_queue
#test executable names
TEST = test
#all source .cpp files, except for main
CPPFILES = $(shell ls $(SRCDIRS) | grep .cpp | grep -v $(MAIN).cpp)
#all test files
TESTFILES = $(shell ls $(TESTDIR)| grep .cpp)
#test obj files
TOBJ = $(TESTFILES:%.cpp=$(OBJDIR)/%.o)
#all header files
DEPS = $(shell ls $(IDIRS) | grep .h)
#all object files (full paths), derived from source .cpp files
OBJFILES = $(CPPFILES:%.cpp=$(OBJDIR)/%.o)
#all source files
SRCFILES = $(CPPFILES) $(DEPS) $(TESTFILES) $(MAIN).cpp
vpath
vpath %.h $(IDIRS)
vpath %.cpp $(SRCDIRS) $(TESTDIR)
vpath %.o $(OBJDIR)

all: gtest libtest build test

build: $(OBJFILES) $(OBJDIR)/$(MAIN).o
	@ echo Compiling objective files into $(OUT) executable
	@ $(CPPC) -o $(OUT) $^ $(CPPFLAGS)
	@ echo Done!

test: $(OBJFILES) $(TOBJ)
	@ make swipe
	@ make gtest
	@ echo Done!
	@ echo Compiling objective files into $(TEST) test executable
	@ $(CPPC) $^ -o $(TEST) $(CPPFLAGS) $(TESTFLAGS) 
	@ echo Done!
	@ echo Now launching tests
	@ ./$(TEST)

$(OBJDIR)/%.o: %.cpp
	@ echo Making $@
	@ $(CPPC) -c $(CPPFLAGS) $< -o $@

gtest:
	@ echo Checking Google Tests in $(GTESTIDIR).
	@ (git clone https://github.com/google/googletest -q $(GTESTIDIR) 2>/dev/null && make libtest) || echo Already installed!

$(DEPSDIR)/deps.make: $(SRCFILES)
	@ echo Making a dependencies list
	@ rm -rf $(DEPSDIR)/deps.make $(foreach cpp, $(filter-out %.h, $^), && $(CPPC) -MM -MT '$(patsubst %.cpp,$(OBJDIR)/%.o, $(notdir $(cpp)))' $(cpp) $(CPPFLAGS) >> $(DEPSDIR)/deps.make)
	@echo Done!
include $(DEPSDIR)/deps.make

.PHONY: clean libtest cov swipe
libtest:
	@ echo Making a gtest library in $(LIBDIR)...
	@ $(CPPC) -isystem $(GTESTDIR)/include -I$(GTESTDIR) -pthread -c $(GTESTDIR)/src/gtest-all.cc -o $(OBJDIR)/gtest-all.o
	@ ar -rv $(LIBDIR)/libgtest.a $(OBJDIR)/gtest-all.o
	@ echo Done!

clean:
	@ echo Cleaning...
	@ rm -rf ./.*.txt $(OBJDIR)/* *~ $(foreach exec, $(OUT) $(TEST), ./$(exec)) $(DEPSDIR)/deps.make 
	@ echo Done!
cov:
	@ echo Making coverage...
	@ lcov -c -d . -o cov.info 
	@ genhtml -o html cov.info --demangle-cpp --branch-coverage
	@ rm cov.info
	@ open html/index.html
	@ echo Done!
swipe:
	@ rm -rf $(OBJDIR)/*.gcda $(DEPSDIR)/deps.make 
