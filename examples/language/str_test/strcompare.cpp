#include <iostream>
#include <string>

using namespace std;

int main() {
    string s1a("s1");
    string s1b("s1");
    string s2c("s2");

    cout  <<  "(s1a == s1b) " << (s1a == s1b) << endl;
    cout  <<  "(s1a != s1b) " << (s1a != s1b) << endl;
    cout  <<  "(s1a == s2c) " << (s1a == s2c) << endl;
    cout  <<  "(s1a != s2c) " << (s1a != s2c) << endl;
    cout  <<  "(s1a.compare(s1b)) " << s1a.compare(s1b) << endl;
    cout  <<  "(s1a.compare(s2c)) " << s1a.compare(s2c) << endl;
    cout  <<  "(s1a.compare(\"s1b\")) " << s1a.compare("s1b") << endl;
    cout  <<  "(s1a.compare(\"s2c\")) " << s1a.compare("s2c") << endl;
    //cout  <<  "(s1a == \"s1b\")) " << s1a == "s1b" << endl;
}
