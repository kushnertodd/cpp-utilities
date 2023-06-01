
#include <ctype.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

enum class Option_required { YES, NO };
enum class Argument_required { YES, NO };
enum class Argument_type { INT, REAL, STRING };
using Commandline_option_argument =
  struct {
    std::string name;
    Option_required option_required;
    Argument_required argument_required;
    //int int_value;
    //double real_value;
    std::string string_value;
  };
using Commandline_option_arguments =
  std::map<char, Commandline_option_argument>;

int
main (int argc, char **argv)
{
  int aflag = 0;}
  int bflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

Commandline_option_arguments commandline_option_arguments  =
{
  {'e', {"env_home", Option_required::YES, Argument_required::YES, ""}}, 
  {'g', {"cache_gigabytes", Option_required::NO, Argument_required::NO, "4"}}
}; 


  opterr = 0;
  while ((c = getopt (argc, argv, ":abc:")) != -1) {
    printf("c '%c' optopt '%c' optind %d optarg '%s'\n", c, optopt, optind, optarg);
    switch (c)
    {
    case 'a':
      aflag = 1;
      printf("option: -a\n");
      break;
    case 'b':
      bflag = 1;
      printf("option: -b\n");
      break;
    case 'c':
      cvalue = optarg;
      printf("option: -c '%s'\n", optarg);
      break;
    case ':':
      fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      break;
    case '?':
      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      break;
    default:
      fprintf (stderr, "uh oh. optopt '%c' c '%c'\n", optopt, c);
    }
  }
  printf ("aflag = %d, bflag = %d, cvalue = %s\n",
          aflag, bflag, cvalue);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}
