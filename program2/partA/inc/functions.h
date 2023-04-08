/**
 * Copyright 2023 - Function definitions for Heapifying
 * Author - vnagpal
 *
 */
#ifndef PROGRAM2_PARTA_INC_FUNCTIONS_H_
#define PROGRAM2_PARTA_INC_FUNCTIONS_H_
#include <cmath>     // floor()
#include <fstream>   // I/O to files
#include <iostream>  // I/O
#include <string>    // string functionality
using std::string;   // readability

/**
 * Function is meant to read input file and populate an array with the given
 * size in the file
 * @param file_name name of the .txt file
 * @param kSize pass by pointer variable that will define the size of the array
 * @return a populated array given the integers from the input file
 */
int* ReadInput(string file_name, int* kSize);

/**
 * Function is meant to implement the heap-bottom-up algorithm to construct a
 * max heap of the integers in the file specified by file_name
 * @param file_name name of the file that contains the integers
 */
void MaxHeapBottomUp(string file_name);

/**
 * Function is meant to implement the heap-bottom-up algorithm to construct a
 * min heap of the integers in the file specified by file_name
 * @param file_name name of the file that contains the integers
 */
void MinHeapBottomUp(string file_name);

/**
 * Function is meant to write the min and max heaps to an output.txt file
 * @param array the min or max heap, or any array in general
 * @param size the size of the heap
 */
void PrintHeap(int* array, int size);

#endif  // PROGRAM2_PARTA_INC_FUNCTIONS_H_
