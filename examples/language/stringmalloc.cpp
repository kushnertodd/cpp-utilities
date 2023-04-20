#include <cstdlib>
#include <cstring>
#include <iostream>

int main() {
    char* buf = (char*) malloc(10);
    strcpy(buf, "test1");
    std::string test1(buf);
    strcpy(buf, "other1");
    std::cout << "string test is still '" << test1 << "' after strcpy()" << std::endl;
    strcpy(buf, "test2");
    std::string test2(buf);
    free(buf);
    std::cout << "string test is still '" << test2 << "' after free()" << std::endl;
}
