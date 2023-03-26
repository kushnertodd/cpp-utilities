/*
 * Sorter.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: Todd
 */
#include <iostream>
#include <vector>
using namespace std;

#include "Sorter.h"

Sorter::Sorter() {
	// TODO Auto-generated constructor stub

}

Sorter::~Sorter() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char **argv) {
	/*
	 * sort.cpp
	 *
	 *  Created on: Feb 19, 2014
	 *      Author: Todd
	 */
	int int_values[] = { 4, 2, 9, 1 };
	vector<int> values;
  for (int i =1; i < 4; i++)
    values.push_back(int_values[i]);
  cout << "argc: " << 2 << endl;
  /*
	if (argc < 2) {
		cout << "usage " << argv[0] << "type data" << endl;
		cout
				<< "  type = [s]election, [i]nsertion, [q]uicksort, [m]ergesort, [h]eapsort" << endl;
	} else {
		char stype;
		cin >> stype;
		int intval;
		for (cin >> intval; !cin.eof(); cin >> intval)
      cout << "  read: " << intval << endl;
			values.push_back(intval);
	}
  */
}

