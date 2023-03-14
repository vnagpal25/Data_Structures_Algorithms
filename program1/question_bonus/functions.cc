// Copyright 2023 CSCE350
// Author vnagpal
// all function implementations
#include "functions.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <ctime>
using std::ifstream, std::vector, std::swap, std::cout, std::endl,
    std::ofstream, std::to_string;

vector<double> ReadInput(string file_name) {
  ifstream input(file_name);
  vector<double> values;
  double value;
  while (input >> value) values.push_back(value);
  return values;
}

int Partition(vector<double> *values, int low, int high) {
  // Hoare partition as explained in textbook
  double pivot = (*values)[low];  // picking first element as pivot
  int i = low;
  int j = high;
  while (true) {
    // finds the index first element from the left that is >= than the pivot
    while ((*values)[i] < pivot) i++;

    // finds the index first element from the right that is <= than the pivot
    while ((*values)[j] > pivot) j--;
    // then we have traversed over the index of the pivot and we should return
    // it
    if (i >= j) return j;

    // swaps to move smaller value(that was found after expected pivot index)
    // before pivot index, and bigger value(that was found before expected pivot
    // index) to after pivot index
    swap((*values)[i], (*values)[j]);
  }
}

void QuickSort(vector<double> *values, int low, int high) {
  // base case(0-1 elements):
  // when low == high, singular element, need not be sorted
  //  when low>high, there is no element, nothing to sort
  if (low >= high) return;

  // pi is the correct index of the pivot
  // element within the to-be-sorted array
  int pi = Partition(values, low, high);

  // sorts everything before pivot
  QuickSort(values, low, pi);

  // sorts everything after pivot
  QuickSort(values, pi + 1, high);
}

int RunQuickSort(int input_size) {
  for (int i = 1; i <= 10; i++) {
    string file_name = "input" + to_string(i) + ".txt";
    ofstream out_file(file_name);
    // in each file, put amount input_size floating point numbers
    for(int j = 0; j<input_size;j++){
      srand(time(NULL));
      out_file << rand() % 19 + (-9) << " ";
    }
    out_file.close();
  }
}
