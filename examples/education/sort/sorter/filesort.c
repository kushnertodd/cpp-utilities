/* filesort.c - sorts a file named 'file' containing numbers one per line 
create a file called 'file' that looks like:
  342
  1 
  92
  etc.
with numbers one per line, and this program will:
- read the file
- sort them
- and write out the sorted list
*/
#include <errno.h>
#include <stdio.h>
#include <string.h>
/* sort - 'bubblesort' alist: 
   'sort()' is a subroutine, containing the code from sort.c
   bubble largest numbers from the bottom of the list to list[len], list[len-1], etc.
     0 1 2 ... len-1 len
     | | |       ^    ^ largest goes to list[len]
     +-+-+-------+----+
     | | |       | second-largest goes to list[len-1]
     +-+-+-------+
     etc.
  */
void sort(int *list, int len)
{
  int i, j;
  for (i = len; i > 0; i--) 
  {
    for (j = 0; j < i-1; j++)
    {
      if (list[j] > list[j+1])
      {
        int t = list[j]; 
        list[j] = list[j+1];
        list[j+1] = t;
      }
    }
  } 
}

// main program
#define MAXLEN 1000
int list[MAXLEN];
int len = 0;
int main(int argc, char **argv) {
  char *file = "file";
  char line[1000];
  FILE *f = fopen(file, "r");
  if (f == NULL) {
    printf("cannot open file '%s': %s\n", file, strerror(errno));
    exit(1);
  }
  printf("input data:\n");
  while (fgets(line, 1000, f) != NULL)
  {
    int number;
    sscanf(line, "%d", &number);
    printf("    %d\n", number);
    list[len++] = number;
    if (len >= MAXLEN)
      break;  // don't overflow list
  }
  fclose(f);
  sort(list, len);
  int i;
  printf("sorted data:\n");
  for (i = 0; i < len; i++)
    printf("    %d\n", list[i]);
}
