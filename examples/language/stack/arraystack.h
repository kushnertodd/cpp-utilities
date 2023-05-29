#include "stack.h"
class ArrayStack: public Stack {
	char *p;
	int max;
	int top;
public:
	ArrayStack();
	~ArrayStack(); 
	void push(char c);
	char pop();
};
