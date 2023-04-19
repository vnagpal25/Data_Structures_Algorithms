First, make sure you have the following in your directory:

- makefile
- inc/functions.h
- src/functions.cc
- src/maxheap.cc
- src/minheap.cc
- input.txt
  - make sure disconnected nodes are represented by 0 weight distances as well
  - have the input formatted as, with spaces within lines. If infinite distance between two nodes
    , represent as inf in the input:
    - X X X X
    - X X X X
    - X X X X
    - X X X X
      


Second, depending on if you want to run the minheap or maxheap function, type "make minheap" or "make maxheap"into the command line

Third, type "./maxheap" if you want to execute the maxheap function, or "./minheap" if you want to execute the minheap function.

Depending on which command was entered "output.txt" should contain either the minheap or the maxheap from the given data.