#include "stdlib.h"
#include <stdio.h>
#include <vector>
using namespace std;

typedef vector<int> int_vector;
typedef vector<int>::iterator int_iter;

void print(int_vector vals, char* msg) {
  int i;
  if (msg) printf("%s ", msg);
  for (int_iter i =  vals.begin(); i != vals.end(); ++i)
    printf("%-3d ", *i);
  printf("\n");
}

int main(int argc, char **argv) {
  printf("argc: %d\n", argc);
  if (argc < 2) {
    printf("usage: %s num num num...\n", argv[0]);
    exit(1);
  }
  int_vector vals;
  int ct = argc - 1;
  for (int i = 0; i < ct; i++) {
    vals.push_back(atoi(argv[i+1]));
  }
  ct = 0;
  // assumes at least two numbers in vals
  for (int_iter i = vals.begin(); (i+1) != vals.end(); ++i, ++ct) {
    int j;
    char buf[20];
    printf("-------------------------------------\n");
    sprintf(buf, "iteration %3d: ", ct);
    print(vals, buf);
    int pos=0;
    for (int_iter j = i+1; j != vals.begin() && *j < *(j-1); --j, ++pos) {
      iter_swap(j-1, j);
      sprintf(buf, " swap %d and %d: ", *(j-1), *j);
      print (vals, buf);
    }
  }
  print(vals, "sorted:");
}
