// Copyright 2023 CSCE350
// Author vnagpal
// all function implementations
#include "functions.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
using std::ifstream, std::vector, std::swap, std::cout, std::endl,
    std::ofstream, std::to_string, std::chrono::microseconds,
    std::chrono::high_resolution_clock;

vector<double> ReadInput(string file_name) {
  ifstream input(file_name);
  vector<double> values;
  double value;
  while (input >> value) values.push_back(value);
  return values;
}

int Partition(vector<double> *values, int low, int high) {
  // Hoare partition as explained in textbook
  // cout << "Partition " << low << " " << high << endl;
  double pivot = (*values)[low];  // picking first element as pivot
  int i = low;
  int j = high;
  while (true) {
    // finds the index first element from the left that is >= than the pivot
    while ((*values)[i] < pivot) i++;

    // finds the index first element from the right that is <= than the pivot
    while ((*values)[j] > pivot) j--;
    // then we have traversed over the index of the pivot and we should
    // return
    // it
    // cout << "i,j" << i << " " << j << " " << (*values)[i] << " " <<
    // (*values)[j]
    //  << endl;
    // cout << "are they equal: " << ((*values)[i] == (*values)[j]) << endl;
    if (i >= j || ((*values)[i] == (*values)[j])) {
      // cout << "Done partition\n" << endl;
      return j;
    }

    // swaps to move smaller value(that was found after expected pivot index)
    // before pivot index, and bigger value(that was found before expected
    // pivot
    // index) to after pivot index
    // cout << "i,j" << i << " " << j << endl;
    swap((*values)[i], (*values)[j]);
  }
}

void QuickSort(vector<double> *values, int low, int high) {
  // base case(0-1 elements):
  // when low == high, singular element, need not be sorted
  //  when low>high, there is no element, nothing to sort
  // cout << "low, high:" << low << " " << high << endl;
  if (low >= high) return;

  // cout << "low, high: " << low << ", " << high << endl;
  //  pi is the correct index of the pivot
  //  element within the to-be-sorted array
  int pi = Partition(values, low, high);

  // sorts everything before pivot
  QuickSort(values, low, pi - 1);

  // sorts everything after pivot
  QuickSort(values, pi + 1, high);
}

vector<int> GenerateNSortFiles(int input_size) {
  vector<int> run_times;
  srand(time(NULL));
  for (int i = 1; i <= 100; i++) {
    string input_file_name = "input" + to_string(i) + ".txt";

    string output_file_name = "output" + to_string(i) + ".txt";

    ofstream out_file(input_file_name);
    // in each file, put amount input_size floating point numbers
    // cout << iteration << "populating file with random numbers" << endl;
    for (int j = 0; j < input_size; j++) {
      double rand_num = static_cast<double>(rand()) /
                            static_cast<double>(RAND_MAX) * (2 * input_size) -
                        input_size;
      out_file << rand_num << " ";
    }
    // cout << iteration << "done populating file with random numbers" << endl
    //      << iteration << "reading input now" << endl;
    out_file.close();

    vector<double> values = ReadInput(input_file_name);

    microseconds elapsed_time;
    auto start = high_resolution_clock::now();

    // cout << iteration << "sorting said file" << endl;
    QuickSort(&values, 0, values.size() - 1);
    // cout << iteration << "SORTED" << endl;

    auto end = high_resolution_clock::now();
    elapsed_time = std::chrono::duration_cast<microseconds>(end - start);
    run_times.push_back(elapsed_time.count());
    ofstream output_file(output_file_name);
    for (int j = 0; j < static_cast<int>(values.size()); j++)
      output_file << values[j] << " ";
  }
  return run_times;
}

int RunQuickSort(int input_size) {
  // cout << "Analyzing for input_size " << input_size << endl;
  vector<int> run_times = GenerateNSortFiles(input_size);
  // cout << "Done for input_size " << input_size << endl;

  int sum = 0;
  for (int i = 0; i < static_cast<int>(run_times.size()); i++)
    sum += run_times[i];
  double avg_time =
      static_cast<double>(sum) / static_cast<double>(run_times.size());
  return avg_time;
}

void Print(vector<double> nums) {
  for (int i = 0; i < static_cast<int>(nums.size()); i++)
    cout << nums[i] << " ";
  cout << endl;
}
