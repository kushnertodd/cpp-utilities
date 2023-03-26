#include <stdio.h>
int s[7] = {0, 3, 2, 9, 1, 4, 5};
int n = 7;
int main(int argc, char** argv) {
  //printf("argc %d\n", argc);
  int i, j;
  printf("start:\n");
  for (i = 0; i < n; i++)
    printf("%2d: %d\n", i, s[i]);
  for (i = n - 1; i > 0; i--) {
    //printf(" i %d\n", i);
    for (j = 0; j < i; j++) {
      //printf("j %d s[%d] %d j+1 %d s[%d] %d\n", j, s[j], j+1, s[j+1]);
      if (s[j] > s[j+1]) {
        //printf("hello world!\n");
        //printf(" swapping s[%d] s[%d]\n", j, j+1);
        //printf(" j %d s[j] %d\n", j, s[j]);
        //swap(s[j], s[j+1]);
        int t = s[j];
        s[j] = s[j+1];
        s[j+1]= t;
      }
    }
  }
  printf("final:\n");
  for (i = 0; i < n; i++)
    printf("%2d: %d\n", i, s[i]);
}
