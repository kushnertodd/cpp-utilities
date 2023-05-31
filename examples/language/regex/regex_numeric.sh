make regex_numeric
for f in 1 1. 1.1 .1 +1 +1. +1.1 +.1 -1 -1. -1.1 -.1 1a a1 1a1 ; do
  #echo $f
  ./regex_numeric $f
done
