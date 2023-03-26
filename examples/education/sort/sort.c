/* sort.c - sort a series of numbers
install C with cygwin from: http://cygwin.com/setup.exe

Here's a C program to sort a series of numbers.
compile: gcc -o sort sort.c
run:     ./sort
*/
#include <stdio.h>
#define MAXLEN 1000
int list[MAXLEN];
int len = 0;
int main(int argc, char** argv) 
{
  printf("This program sorts a list of numbers\n");
  while (1) 
  { // this says "do forever", until you break out of the loop
    printf("enter number (0 to stop): ");
    int number = 0;
    scanf("%d", &number);
    if (number == 0)
      break;
    list[len++] = number;
  }
  /* now we 'bubblesort' the list: 
     - bubble largest numbers from the bottom of the list to list[len], list[len-1], etc.
     0 1 2 ... len-1 len
     | | |       ^    ^ largest goes to list[len]
     +-+-+-------+----+
     | | |       | second-largest goes to list[len-1]
     +-+-+-------+
     etc.
  */
  int i, j;
  for (i = len; i > 0; i--)  // why 'i--'? 'i > 0'?
  {
    for (j = 0; j < i-1; j++) // why 'i-1'?
    {
      if (list[j] > list[j+1])
      {
        int t = list[j]; // what is this doing?
        list[j] = list[j+1];
        list[j+1] = t;
      }
    }
  } 
  for (i = 0; i < len; i++)
    printf("%d\n", list[i]);
}
/* assignment:
1. answer the questions in the comments above
2. print out the elements being exchanged around 'int t'
*/
