CXX      = g++
CXXFLAGS = -g -Wall
PROGRAMS = histogram vector 
#OBJFILES = $(%.cpp=%.o)
OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TSTAMP  := $(shell date "+%F.%H-%M-%S")
all: $(PROGRAMS)

%.o: %.cpp %.hpp
	$(CXX)	-c $(CXXFLAGS) $< -o $@

vec-array: vec-array.o
	$(CXX) $^ -o $@

vector: vector.o
	$(CXX) $^ -o $@

histogram: histogram.o
	$(CXX) $^ -o $@

clean:
	rm -f $(OBJFILES)

clobber: clean
	rm -f $(PROGRAMS) 

# DO NOT DELETE
