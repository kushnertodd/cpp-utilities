CXX      = g++
CXXFLAGS = -g -Wall
PROGRAMS = \
  arg \
  array \
  assert \
  bitset \
  construct \
  destructor \
  destructor_vec \
  directory \
  except \
  filect \
  filesystem \
  free \
  init \
  intToString \
  iomanip \
  listinter \
  my_namespace \
  no_assert \
  ofstream \
  parsedigits \
  static_helper \
  static_member \
  statics \
  strcompare \
  stringfind \
  stringfind_substr \
  stringstream \
  strtok  

#OBJFILES = $(%.cpp=%.o)
OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TSTAMP  := $(shell date "+%F.%H-%M-%S")
all: $(PROGRAMS)

%.o: %.cpp %.hpp
	$(CXX)	-c $(CXXFLAGS) $< -o $@

assert: assert.o
	$(CXX) $^ -o $@

no_assert: no_assert.cpp
	$(CXX) -DNDEBUG no_assert.cpp -o no_assert

directory: directory.o
	$(CXX) $^ -o $@

filename: filename.o
	$(CXX) $^ -o $@

intToString: intToString.o
	$(CXX) $^ -o $@

iomanip: iomanip.o
	$(CXX) $^ -o $@

my_namespace: my_namespace1.o my_namespace2.o my_namespace.hpp
	$(CXX) -o my_namespace my_namespace1.o my_namespace2.o

ofstream: ofstream.o
	$(CXX) $^ -o $@

static_member: static_member_main.o static_member.o
	$(CXX) $^ -o $@ 

statics: statics.o statics_helper.o
	$(CXX) $^ -o $@ 

stringfind: stringfind.o
	$(CXX) $^ -o $@

stringfind_substr: stringfind_substr.o
	$(CXX) $^ -o $@

stringstream: stringstream.o
	$(CXX) $^ -o $@

strtok: strtok.o
	$(CXX) $^ -o $@

clean:
	rm -f $(OBJFILES)

clobber: clean
	rm -f $(PROGRAMS) 

# DO NOT DELETE
