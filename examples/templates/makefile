clean:
		rm *.o out1a out1b
out1.o: out1.cpp
	g++ -c out1.cpp
out1a.o: out1a.cpp
	g++ -c out1a.cpp
out1b.o: out1b.cpp
	g++ -c out1b.cpp
out1a:	out1a.o out1.o
	g++ out1a.o out1.o -o out1a
out1b:	out1b.o out1.o
	g++ out1b.o out1.o -o out1b
out2.o: out2.cpp
	g++ -c out2.cpp
out2a.o: out2a.cpp
	g++ -c out2a.cpp
out2a:	out2.o out2a.o
	g++ out2.o out2a.o -o out2a
