### CSci-3081W Project Support Code Makefile ###

# File History: This combines Prof. Keefe's Makefiles from past years
# with TA John Harwell's 3081W Makefiles from Fall 2016, which introduced
# auto-dependency generation and several other exciting features.


### Section 0: Change this when compiling on non-CSELabs machines ###

PROJECT_NAME = mia

# Path to pre-installed cs3081 support libraries (Google Test, MinGfx, nanogui, ...)
#CS3081DIR = /classes/csel-s18c3081
CS3081DIR = $(shell git rev-parse --show-toplevel)

### Section I: Definitions ###

# Root of the source tree for the project (e.g., could be just . or ./src)
SRCDIR = .

# Output directories for the build process
PROJ_DIR = $(CS3081DIR)/PROJ
BUILDDIR = $(PROJ_DIR)/build
BINDIR = $(BUILDDIR)/bin
OBJDIR = $(BUILDDIR)/obj/$(PROJECT_NAME)
LIBDIR = $(BUILDDIR)/lib
EXTERNAL_DIR = $(PROJ_DIR)/src/external
MINGFX_DIR = $(EXTERNAL_DIR)/MinGfx/build/install

# The name of the executable to create
EXEFILE = $(BINDIR)/$(PROJECT_NAME)

# The list of files to compile for this project.  Defaults to all
# of the .cpp and .cc files in the source directory.  (We use both .cpp
# and .cc in order to support two different popular naming conventions.)
SRCFILES = $(wildcard $(SRCDIR)/*.cc)

# For each of the source files found above, replace .cpp (or .cc) with
# .o in order to generate the list of .o files make should create.
OBJFILES = $(notdir $(patsubst %.cc,%.o,$(SRCFILES)))


# Add -Idirname to add directories to the compiler search path for finding .h files
INCLUDEDIRS = -I$(PROJ_DIR)/imagetools -I/classes/csel-f18c3081/include -I.. -I$(SRCDIR) -I$(SRCDIR)/.. -isystem$(MINGFX_DIR)/include -isystem$(MINGFX_DIR)/include/nanovg -isystem$(MINGFX_DIR)/include/MinGfx-1.0
# Add -Ldirname to add directories to the linker search path for finding libraries
LIBDIRS = -L$(LIBDIR) -L/classes/csel-f18c3081/lib -L$(MINGFX_DIR)/lib -L$(MINGFX_DIR)/lib/MinGfx-1.0

# Add -llibname to link with external libraries
LIBS = -limagetools -limageio -lMinGfxd -lnanogui -Wl,-rpath,$(MINGFX_DIR)/lib
#-lGL -lGLU

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin) # Mac OSX
	LIBS += -framework glut -framework opengl
else # LINUX
	LIBS += -lglut -lGL -lGLU
endif

# The command to run for the C++ compiler and linker
CXX = /soft/gcc/7.1.0/Linux_x86_64/bin/g++
OMP = -fopenmp

# Arguments to pass to the C++ compiler.
# -c is required, it tells the compiler to output a .o file
CXXFLAGS = -W -Werror -Wall -Wextra -fdiagnostics-color=always -Wfloat-equal -Wshadow -Wcast-align -Wcast-qual -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wswitch-default -Wsuggest-override -Wstrict-null-sentinel -Wsign-promo -Wold-style-cast -Woverloaded-virtual -Wctor-dtor-privacy -Wno-old-style-cast -Wno-cast-align -g -std=c++14 -c $(INCLUDEDIRS)

ifeq ($(UNAME), Darwin)
    CXXFLAGS += -Wno-unknown-warning-option
endif

# Arguments to pass to the C++ linker, such as -L, but not -lfoo, which should go in LDLIBS
LDFLAGS = $(LIBDIRS)

# Library names to pass to the C++ linker, such as -lfoo
LDLIBS = $(LIBS)

-include ../../Makefile.local

### Section II: Rules ###


# This is a list of "phony targets" -- targets that do not specify the name of a file.
# Rather they specify the name of a recipe to run whenever make is envoked with the target name.
.PHONY: clean all $(BINDIR) $(OBJDIR)


# The default target which will be run if the user just types "make"
all: $(MINGFX_DIR) $(EXEFILE)

# This rule says that each .o file in $(OBJDIR)/ depends on the
# presence of the $(OBJDIR)/ directory.
$(addprefix $(OBJDIR)/, $(OBJFILES)): | $(OBJDIR)

# And, this rule provides a recipe for creating that objdir.  The same rule applies
# to the bindir, where the exe will be output.
$(OBJDIR) $(BINDIR):
	@mkdir -p $@



# COMPILING (USING A PATTERN RULE):
# Since every .cpp (or .cc) file must be compiled into a .o, we will write this
# recipe using a pattern rule.  Using this recipe, any file that matches the pattern
# $(SRCDIR)/filename.cpp can be turned into $(OBJDIR)/filename.o.

# The same thing will also work for files with a .cc extension
$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(MINGFX_DIR)
	@echo "==== Auto-Generating Dependencies for $<. ===="
	$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	@echo "==== Compiling $< into $@. ===="
	$(CXX) $(OMP) $(CXXFLAGS) $(CXXLIBDIRS) -c -fPIC -o  $@ $<

# WITH AUTO-GENERATED DEPENDENCIES:
# Note that there are actually two steps to the compiling recipe above.  The second
# step should be familiar, it just calls g++ to compile the .cpp into a .o.  But,
# the first step is an advanced topic.  It calls the custom function make-depend-cxx()
# defined below, which calls the g++ compiler with special flags (the -M* parts)
# that tell g++ to output a make-compatable list of all of the .h files included
# by the specified C++ source file.  All of these .h files should be listed as
# dependencies of the .cpp file that is being compiled because if any of the included
# .h files change, our .cpp file will need to be recompiled in order to stay up to
# date.  So, we want to be thorough and capture all of these dependencies in our
# Makefile.  We could do this manually.  For each .cpp file we would need to add a
# rule to this Makefile that lists dependies, and would look something like this:
#    file1.o:  file1.cpp file1.h file2.h mydir/file3.h myotherdir/file4.h
# where all of the .h files are either included by file1.cpp or by each other.
# It's tedious and error prone to try to track down all these dependencies manually.
# So, instead, we ask the compiler to generate a list of dependencies for us and
# save it out to a new text file with a .d extension.  This text file lists the
# dependencies using the same Makefile syntax we would use if we wrote them down
# manually.  Read more about auto-dependency generation here:
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation
# usage: $(call make-depend,source-file,object-file,depend-file)
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $1

# Once the make-depend-cxx() function auto-generates the .d text file of additional
# dependency rules, we need to load it into make, as if those rules were actually
# written in this file.  This is done with make's own "include" command, which
# enables us to include one Makefile within another.
-include $(addprefix $(OBJDIR)/,$(OBJFILES:.o=.d))



# LINKING:
# This rule is for the linking step of building a program.  The dependencies mean that
# the executable target that we are building depends upon all of the .o files that are
# generated by the compiler as well as the $(BINDIR), which must exist so we can
# output the exe there.  The recipe that follows calls g++ to tell it to link all the
# .o files into an executable program.
$(EXEFILE): $(addprefix $(OBJDIR)/, $(OBJFILES)) | $(BINDIR)
	@echo "==== Linking $@. ===="
	$(CXX) $(OMP) $(LDFLAGS) $(addprefix $(OBJDIR)/, $(OBJFILES)) -o $@ $(LDLIBS)

check-style:
	@echo "==== Checking style is correct ===="
	$(CS3081DIR)/cpplint/cpplint.py --root=.. *.cc *.h

check-style-cse:
	@echo "==== Checking style is correct ===="
	$(CS3081DIR)/cpplint/cpplint-cse.sh --root=.. *.cc *.h

$(MINGFX_DIR):
	cd $(EXTERNAL_DIR)/MinGfx; make

# Clean up the project, removing ALL files generated during a build.
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(EXEFILE)
