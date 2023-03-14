// Copyright 2023 CSCE350
// Author vnagpal
// all function definitions
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include <iostream>
#include <string>
#include <vector>
using std::string, std::vector;
/**
 * method is meant to read input file of unsorted floating point numbers and
 * populate a vector with them
 * @param file_name file name of the file that has the numbers
 * @return a vector filled with the numbers in the same order as they were in
 * the input file
 */
vector<double> ReadInput(string file_name);

/**
 * method is meant to quicksort a sub-vector of the unsorted array, the given
 * range is values[low, ..., high]
 * @param values pass by reference pointer that specifies the vector with the
 * floating point numbers
 * @param low the left-most index of the sub-vector
 * @param high the right-most index of the sub-vector
 */
void QuickSort(vector<double>* values, int low, int high);

/**
 * method is meant to partition the sub-vector specified by low and high into 2
 * halves. The left half will be all values below the pivot, and the right half
 * will be all values above the pivot. The method actually does two things: move
 * all appropriate values before or after pivot (as well as the pivot itself in
 * the correct place), and return the index of the pivot.
 * @param values pass by reference pointer that specifies the vector with the
 * floating point numbers
 * @param low the left-most index of the sub-vector
 * @param high the right-most index of the sub-vector
 */
int Partition(vector<double>* values, int low, int high);

int RunQuickSort(int input_size);
#endif  // _FUNCTIONS_H_
