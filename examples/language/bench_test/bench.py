import sys

nargs = len(sys.argv)
program_name = sys.argv[0]
if nargs < 2:
  print("usage: py "+program_name+" count")
  exit(0)
count_string = sys.argv[1]     
count = int(count_string)
for i in range(count):
  j = i * i
