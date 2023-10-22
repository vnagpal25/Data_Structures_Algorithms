First, make sure you have the following in your directory:

- makefile
- inc/functions.h
- src/functions.cc
- src/floyds.cc
- input.txt
  - make sure disconnected nodes are represented by 0 weight distances as well
  - have the input formatted as, with spaces within lines. If infinite distance between two nodes
    , represent as inf in the input (see input.txt for reference):
    - X X X X
    - X X X X
    - X X X X
    - X X X X

Second, type "make" into your command line

Third, type "./floyds" into your command line

There should be a file named output.txt with the resulting distance matrix.