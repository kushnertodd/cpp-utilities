#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: %s count\n", argv[0]);
    exit(0);
  }
  int count = atoi(argv[1]);
  int j;
  for (int i = 0; i < count; i++)
    j = i * i;
}
