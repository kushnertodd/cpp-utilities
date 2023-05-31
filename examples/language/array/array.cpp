#include <iostream>
using namespace std;
int main() {
    int* arr = new int[5];
    for (int i = 0; i < 9; i++) {
        cout << "arr[" << i <<"] = " << i << endl;
    }
}
