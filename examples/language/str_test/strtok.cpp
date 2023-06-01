#include <cstring>
#include <iostream>
#include <iomanip>
 
/*
Output:
"one" "two" "three" "four" 
Contents of the input string now:
"one\0+ two\0* (three\0- four\0!\0"
*/
using namespace std;
int main() 
{
    char input[] = "one + two * (three - four)!";
    const char* delimiters = "! +- (*)";
    char *token = strtok(input, delimiters);
    while (token) {
        cout << quoted(token) << ' ';
        token = strtok(nullptr, delimiters);
    }
 
    cout << "\nContents of the input string now:\n\"";
    for (size_t n = 0; n < sizeof input; ++n) {
        if (input[n] != '\0')
            cout << input[n];
        else
            cout << "\\0";
    }
    std::cout << "\"\n";
}
