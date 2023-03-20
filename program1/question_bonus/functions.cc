// Copyright 2023 CSCE350
// Author vnagpal
// all function implementations for quicksort empirical analysis
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
  ifstream input(file_name);  // allows us to read file
  vector<double> values;      // double of values to be returned
  double value;               // particular value

  // while can read value, put it in the vector
  while (input >> value) values.push_back(value);
  return values;  // returns
}

int Partition(vector<double> *values, int low, int high) {
  // Hoare partition as explained in textbook, with slight tweaks to my liking
  double pivot = (*values)[low];  // picking first element as pivot
  int i = low;
  int j = high;
  while (true) {
    // finds the index first element from the left that is >= than the pivot
    while ((*values)[i] < pivot) i++;

    // finds the index first element from the right that is <= than the pivot
    while ((*values)[j] > pivot) j--;

    // then we have traversed over the index of the pivot and we should
    // return it. second condition checks if values found on left and right are
    // the same (must be pivot)
    if (i >= j || ((*values)[i] == (*values)[j])) {
      return j;
    }

    // swaps to move smaller value(that was found after expected pivot index)
    // before pivot index, and bigger value(that was found before expected
    // pivot
    // index) to after pivot index
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
  vector<int> run_times;  // new vector to store run times of sorting each file
  srand(time(NULL));      // seeding for pseudorandom number generation

  // 100 iterations for 100 input files to be sorted
  for (int i = 1; i <= 100; i++) {
    // input file name
    string input_file_name = "input" + to_string(i) + ".txt";

    string output_file_name = "output" + to_string(i) + ".txt";

    ofstream write_input_file(
        input_file_name);  // allows us to populate created files

    // in each file, put amount input_size floating point numbers
    for (int j = 0; j < input_size; j++) {
      // rand() returns numbers from 0 to RAND_MAX, dividing by RAND_MAX
      // normalizes to between 0 and 1. Multiplying this by 2 * input size gives
      // numbers that range from 0 to 2 * input_size. Subtracting input size now
      // returns numbers that range from -input size to input size
      double rand_num =
          (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) *
              (2 * input_size) -
          input_size;

      // puts random number in file, space delimited
      write_input_file << rand_num << " ";
    }

    write_input_file.close();  // closes writer

    // reads the input file, populates vector with floating point values, and
    // ensures it is cleared from previous trial
    vector<double> values = ReadInput(input_file_name);

    microseconds elapsed_time;  // run time = end - start
    auto start = high_resolution_clock::now();

    QuickSort(&values, 0, values.size() - 1);  // calls quicksort on the values

    auto end = high_resolution_clock::now();
    elapsed_time = std::chrono::duration_cast<microseconds>(end - start);

    run_times.push_back(
        elapsed_time.count());  // adds run time from that trial to the vector

    // for writing sorted array to a file
    ofstream output_file(output_file_name);
    for (int j = 0; j < static_cast<int>(values.size()); j++)
      output_file << values[j] << " ";

    output_file.close();  // closes writer
  }
  return run_times;  // returns all run times
}

int RunQuickSort(int input_size) {
  // holds the run times to sort 100 files with floating point numbers specified
  // by input size
  vector<int> run_times = GenerateNSortFiles(input_size);

  // sums all of the run times
  int sum = 0;
  for (int i = 0; i < static_cast<int>(run_times.size()); i++)
    sum += run_times[i];

  // double division to prevent any rounding issues
  double avg_time =
      static_cast<double>(sum) / static_cast<double>(run_times.size());

  return avg_time;  // returns the average
}

void Print(vector<double> nums) {
  // self-explanatory
  for (int i = 0; i < static_cast<int>(nums.size()); i++)
    cout << nums[i] << " ";
  cout << endl;
}
