/*
 * fib.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: Todd
 */
#include <iostream>
using namespace std;

int fib1(int n1, int n2, int ct) {
	//cout << "fib1(" << n1 << ", " << n2  << ", " << ct << ")" << endl;
	if (ct <= 1)
		return n1;
	else
		return fib1(n2, n1+n2, ct-1);
}
int fib(int n) {
	//cout << "fib(" << n << ")" << endl;
	if (n <= 0)
		return 0;
	else
		return fib1(0, 1, n);
}
int main() {
  for (int i = 1; i < 10; i++) {
    cout << "fib(" << i << "): " << fib(i) << endl;
    //cout << "fib(" << i << "): " << fib(i) << endl << endl;
  }
}
