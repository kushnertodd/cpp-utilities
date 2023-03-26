#include "stdlib.h"
#include <stdio.h>

void print(char *msg, int *vals, int ct) {
  printf("%s\n", msg);
  int i;
  for (i = 0; i < ct; i++)
    printf("%5d ", vals[i]);
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
  printf("ct %d\n", ct);
  int i;
  for (i = 0; i < ct; i++) {
    printf("read: %d %s\n", i, argv[i+1]);
    vals[i] = atoi(argv[i+1]);
  }
  print("read: ", vals, ct);
  for (i = 0; i < ct-1; i++) {
    int min = i;
    int j;
    for (j = i+1; j < ct; j++) {
        printf("iteration i=%d %d, j=%d %d\n", i, vals[i], j, vals[j]);
      if (vals[j] < vals[i])
        min = j;
      if (j != i) {
        printf(" swapping i=%d %d, j=%d %d\n", i, vals[i], j, vals[j]);
        int tmp = vals[i];
        vals[i] = vals[j];
        vals[j] = tmp;
      }
    }
  }
  print("sorted: ", vals, ct);
}
