CC=gcc
CXX=g++
#CCREC=gccrec g++-code-assist
CFLAGS=-g
CXXFLAGS=-g

%.run: %.cpp
#	$(CCREC) $<
	$(CXX) $(CXXFLAGS) $<
	if ! [ -f $*.in ]; then touch $*.in; fi
	./$* < $*.in
