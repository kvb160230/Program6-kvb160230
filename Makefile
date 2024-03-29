#
# UTD CS3377 CDK Example
# Dr. Perkins
# stephen.perkins@utdallas.edu
#

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS =  -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = example1.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
