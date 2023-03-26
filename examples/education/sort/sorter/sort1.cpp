#include <stdio.h>
int main(int argc, char **argv) {
  int arr[] = { 3, 9, 0, 7, 1, 6, 8, 5, 2};
  int N = 9;
  for (int i = 0; i < N-1; i++) {
    int low_index = i;
    for (int j = i+1; j < N; j++) {
      if (arr[j] < arr[low_index])
        low_index = j;
    }
    if (low_index != i) {
      int temp = arr[low_index];
      arr[low_index] = arr[i];
      arr[i] = temp;
    }
  }
  for (int i = 0; i < N; i++)

    printf("%d: %d\n", i, arr[i]);
}
