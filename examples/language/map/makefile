CXXFLAGS=-std=c++17 -g -Wall -Wextra -Werror -lstdc++
%.o: %.cpp %.hpp
	$(CXX)	-c $(CXXFLAGS) $< -o $@
iter: iter.o
	gcc iter.o -o iter $(CXXFLAGS)
