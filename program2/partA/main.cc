#include "functions.h"
int main(int argc, char** argv) {
  int* max_heap = MaxHeapBottomUp("input.txt");
  int min_heap = MinHeapBottomUp("input.txt");
  return 0;
}