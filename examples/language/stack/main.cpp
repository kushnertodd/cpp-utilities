/*
 * main.cpp
 *
 *  Created on: Feb 16, 2014
 *      Author: Todd
 */
#include <iostream>
#include "arraystack.h"
using namespace std;
int main(int argc, char** argv) {
	ArrayStack as;
	as.push('a');
	char c = as.pop();
	cout << "result of pop is " << c << endl;
}



