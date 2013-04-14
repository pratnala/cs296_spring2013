.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
CD	= cd
MKDIR   = mkdir
LATEX 	= latex
BIBTEX  = bibtex
PDFLATEX = pdflatex
DVIPS   = dvips
PS2PDF  = ps2pdf
PERF    = perf
CP      = cp
PYTHON3 = python3

######################################
# Project Name (generate executable with this name)
TARGET = g01_rubegoldberg
TARGET_PERF = g01_perf


# Project Paths
PROJECT_ROOT=$(HOME)/cs296_g01_git/project/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
OBJDIR_PERF = $(OBJDIR)/perf
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
DATADIR = $(PROJECT_ROOT)/data
PLOTDIR = $(PROJECT_ROOT)/plots
SCRIPTDIR = $(PROJECT_ROOT)/scripts
INSTALL_PATH = $(HOME)

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall -w
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS_ALL := $(wildcard $(SRCDIR)/*.cpp)
SRCS := $(filter-out $(SRCDIR)/main_perf.cpp, $(SRCS_ALL))
SRCS_PERF := $(filter-out $(SRCDIR)/main.cpp, $(SRCS_ALL))
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS_PERF := $(SRCS_PERF:$(SRCDIR)/%.cpp=$(OBJDIR_PERF)/%.o)


.PHONY: all exe setup perf_setup doc clean distclean

all: install_box2d exe doc report 

exe: setup $(BINDIR)/$(TARGET)

perf_setup: setup $(BINDIR)/$(TARGET_PERF)

setup:
	@$(ECHO) "Setting up compilation..."
	@$(MKDIR) -p $(OBJDIR)
	@$(MKDIR) -p $(BINDIR)
	@$(MKDIR) -p $(DATADIR)
	@$(MKDIR) -p $(PLOTDIR)
	@$(MKDIR) -p $(OBJDIR_PERF)
	@$(MKDIR) -p $(INSTALL_PATH)
	@$(MKDIR) -p $(INSTALL_PATH)/doc

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

$(BINDIR)/$(TARGET_PERF): $(OBJS_PERF)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS_PERF) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS_PERF:.o=.d)

$(OBJS_PERF): $(OBJDIR_PERF)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf $(DOCDIR)/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(DOCDIR)/html $(BINDIR) *.data* *.dat $(DATADIR) $(PLOTDIR)
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html

clean_box2d:
	@$(RM) -rf $(EXTERNAL_ROOT)/include $(EXTERNAL_ROOT)/lib $(EXTERNAL_ROOT)/src/Box2D/
	@$(ECHO) "Box2D uninstalled"

install_box2d:
	@$(CD) $(EXTERNAL_ROOT)/src; \
	tar -xf Box2D.tgz; \
	$(CD) Box2D; \
	$(MKDIR) -p build296; \
	$(CD) build296; \
	cmake ../; \
	make; \
	make install; \
	$(CD) ../../../../;
	$(ECHO) "Box2D installed"

report:
	@$(ECHO) -n "Generating the LaTeX Report ..."
	@ $(CD) $(DOCDIR); \
	$(PDFLATEX) report_cs296_01; \
	$(BIBTEX) report_cs296_01; \
	$(PDFLATEX) report_cs296_01; \
	$(PDFLATEX) report_cs296_01; \
	$(RM) *.aux *.bbl *.blg *.log; \
	cd ..;
	@$(ECHO) "Done"

debug_prof:box2d_debug debug_prof_unset perf_setup perf_debug

debug_prof_unset:
	@CPPFLAGS="-g -Wall"
	@CPPFLAGS+="-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include"
	@LDFLAGS+="-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib"

perf_debug:
	@$(PERF) record $(BINDIR)/$(TARGET_PERF) 50000
	@$(PERF) report > g01_debug_prof.dat

box2d_debug:
	@$(CD) external/src; \
	tar -xf Box2D.tgz; \
	$(CD) Box2D; \
	mkdir build296; \
	$(CD) build296; \
	cmake -DCMAKE_BUILD_TYPE=Debug ../; \
	make; \
	make install; \
	$(CD) ../../../../;

release_prof:box2d_release release_prof_unset perf_setup perf_release

release_prof_unset:
	@CPPFLAGS="-g -O3 -Wall"
	@CPPFLAGS+="-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include"
	@LDFLAGS+="-O3 -L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib"

perf_release:
	$(PERF) record $(BINDIR)/$(TARGET_PERF) 50000
	@$(PERF) report > g01_release_prof.dat

box2d_release:
	@$(CD) external/src; \
	tar -xf Box2D.tgz; \
	$(CD) Box2D; \
	mkdir build296; \
	$(CD) build296; \
	cmake -DCMAKE_BUILD_TYPE=Release ../; \
	make; \
	make install; \
	$(CD) ../../../../;

dist:clean clean_box2d
	@$(CD) ..; \
	tar -zcf cs296_g01_project.tar.gz cs296_base_code/; \
	$(CD) cs296_base_code/;

install:install_box2d exe doc path_copy clean clean_box2d

path_copy:
	@$(CP) $(BINDIR)/$(TARGET) $(INSTALL_PATH)
	@$(CP) -r $(DOCDIR)/html $(INSTALL_PATH)/doc

plots: setup perf_setup
	@$(ECHO) -n "Generating the CSV file..."
	@$(PYTHON3) $(SCRIPTDIR)/g01_gen_csv.py
	@$(ECHO) "Done"
	@$(ECHO) -n "Generating the plots using a python script..."
	@$(PYTHON3) $(SCRIPTDIR)/g01_gen_plots.py
	@$(ECHO) "Done"

