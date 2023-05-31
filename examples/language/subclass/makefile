CXX      = g++
CXXFLAGS = -g -Wall
PROGRAM  = main
INCFILES = hello.hpp
SRCFILES = main.cpp hello.cpp
OBJFILES = $(SRCFILES:%.cpp=%.o)
TSTAMP  := $(shell date "+%F.%H-%M-%S")

all: $(PROGRAM)

%.o: %.cpp %.hpp
	$(CXX)	-c $(CXXFLAGS) $< -o $@

$(PROGRAM): $(OBJFILES)
	$(CXX) $^ -o $@

run: $(PROGRAM)
	./$(PROGRAM) | tee $(PROGRAM).txt

clean:
	rm -f $(OBJFILES)

clobber: clean
	rm -f $(PROGRAM) 

# DO NOT DELETE
