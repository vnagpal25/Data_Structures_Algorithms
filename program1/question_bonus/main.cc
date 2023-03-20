// Copyright 2023 CSCE350
// Author vnagpal
// main method for quicksort numbers in input file
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "functions.h"
using std::cout, std::endl;
int main() {
  cout << "average run time for quick sort for sorting 10 numbers: "
       << RunQuickSort(10) << " microseconds" << endl;

  cout << "average run time for quick sort for sorting 100 numbers: "
       << RunQuickSort(100) << " microseconds" << endl;

  cout << "average run time for quick sort for sorting 1,000 numbers: "
       << RunQuickSort(1000) << " microseconds" << endl;

  cout << "average run time for quick sort for sorting 10,000 numbers: "
       << RunQuickSort(10000) << " microseconds" << endl;

  cout << "average run time for quick sort for sorting 100,000 numbers: "
       << RunQuickSort(100000) << " microseconds" << endl;
  return 0;
}
