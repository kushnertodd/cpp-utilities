#include <iostream>
#include "hello.hpp"
using namespace std;
void a::hello() { cout << "a::hello: hello!" << endl; }
void a::b::hello() { cout << "a::b::hello: hello!" << endl; }

