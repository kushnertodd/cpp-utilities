#include "stdlib.h"
#include <stdio.h>

void print(int *vals, int ct, char* msg) {
  int i;
  if (msg) printf("%s ", msg);
  for (i = 0; i < ct; i++)
    printf("%02d=%-3d ", i, vals[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  printf("argc: %d\n", argc);
  if (argc < 2) {
    printf("usage: %s ct num num num...\n", argv[0]);
    exit(1);
  }
  int ct = argc - 1;
  int* vals = (int *) malloc(ct * sizeof(int));
  //printf("ct %d\n", ct);
  int i;
  for (i = 0; i < ct; i++) {
    //printf("read: %d %s\n", i, argv[i+1]);
    vals[i] = atoi(argv[i+1]);
  }
  for (i = 0; i < ct-1; i++) {
    int j;
    char buf[20];
    sprintf(buf, "iteration %3d\n", i);
    print(vals, ct, buf);
    for (j = i+1; j > 0 && vals[j] < vals[j-1]; j--) {
      int tmp = vals[j-1];
      vals[j-1] = vals[j];
      vals[j] = tmp;
      sprintf(buf, " swap %02d=%d and %02d=%d: ", j-1, vals[j-1], j, vals[j]);
      print (vals, ct, buf);
    }
  }
  print(vals, ct, "sorted:");
}
