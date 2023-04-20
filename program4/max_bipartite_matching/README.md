First, make sure you have the following in your directory:
- makefile
- inc/functions.h
- src/functions.cc
- src/max_bipartite.cc
- bin/ (directory)
- input.txt
  - have the first two rows represent the nodes that are in sets V and U, with spaces in between them
  - number the nodes in the first two rows of the file starting from 1 (not 0)
  - have the adjacency matrix formatted as follows, with spaces within lines. Make sure the size of the adjacency matrix is |V|+|U|
    - X X X X
    - X X X X
    - X X X X
    - X X X X
  - see input.txt and input2.txt for correctly formatted inputs

Second, type "make" into your command line

Third, type "./bipartite" into your command line

There should be a file named output.txt with the resulting maximum matching of the bipartite graph.
