#include "arraystack.h"
ArrayStack::ArrayStack() :
    max(1000), top(0) {
  p = new char[1000];
}

ArrayStack::~ArrayStack() {
  delete[] p;
}

void ArrayStack::push(char c) {
  p[top++] = c;
}

char ArrayStack::pop() {
  return p[--top];
}

