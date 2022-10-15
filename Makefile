# 	         Makefile for COMP 40 Homework 1
#
#     Author: Noah Mendelsohn (adapted from Norman Ramsey's compile script)
#     Edited by: Rodrigo Campos (rcampo01) and Yassin Kina (ykina01)
#
#  Maintenance targets:
#
#
#    all         - (default target) make sure everything's compiled
#    clean       - clean out all compiled object and executable files
#

# Executables to built using "make all"
EXECUTABLES = restoration

#
#  The following is a compromise. You MUST list all your .h files here.
#  If any .h file changes, all .c files will be recompiled. To do better,
#  we could make an explicit target for each .o, naming only the .h
#  files it really uses.
#
# Add your own .h files to the right side of the assingment below.
INCLUDES = parseFile.h manageTable.h

# Do all C compies with gcc (at home you could try clang)
CC = gcc

# Comp 40 directory
COMP40 = /comp/40

# Hanson directory
HANSON = /usr/sup/cii40

# Updating include path to use current directory
# (which is .), Comp 40 .h files, and CII interfaces
IFLAGS = -I. -I$(COMP40)/build/include -I$(HANSON)/include/cii


# the next three lines enable you to compile and link against course software
CFLAGS =  -g -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)
LIBS = $(CIILIBS) -lm    
LFLAGS = -L$(COMP40)/build/lib

# Linking flags, used in the linking step
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L$(COMP40)/build/lib -L$(HANSON)/lib64

# Libraries needed for any of the programs that will be linked
# Both programs need cii40 (Hanson binaries) and *may* need -lm (math)
# Only brightness requires the binary for pnmrdr.
LDLIBS = -lpnmrdr -lcii40 -lm


# 
#    'make all' will build all executables
#
#    Note that "all" is the default target that make will build
#    if nothing is specifically requested
#
all: $(EXECUTABLES)

# 
#    'make clean' will remove all object and executable files
#
clean:
	rm -f $(EXECUTABLES) *.o


# 
#    To get any .o, compile the corresponding .c
#
%.o:%.c $(INCLUDES) 
	$(CC) $(CFLAGS) -c $<

#
# Individual executables
#
#    Each executable depends on one or more .o files.
#    Those .o files are linked together to build the corresponding
#    executable.
#
restoration: restoration.o readaline.o parseFile.o manageTable.o
	$(CC) $(LDFLAGS) -o restoration  restoration.o readaline.o \
			    parseFile.o manageTable.o $(LDLIBS)
	
#
# Other Shortcuts worth nothing
# $@ takes the name of the build rule and inserts it into the command
# $^ inserts the relocatable object file names into the command
#

