#include "functions.h"
using std::ifstream;
int* ReadInput(string file_name) {
  ifstream file_in(file_name);

  if (!file_in) {
    std::cerr << "File could not be opened" << std::endl;
    exit(errno);
  }

  int size;
  file_in >> size;
  std::cout << size << std::endl;

  int arr[size];
  for (int i = 0; i < size; i++) {
    file_in >> arr[i];
  }

  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  return arr;
}

int* MinHeapBottomUp(string file_name) { int* array = ReadInput("input.txt"); }

int* MaxHeapBottomUp(string file_name) { int* array = ReadInput("input.txt"); }
