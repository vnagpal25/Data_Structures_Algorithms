#ifndef _PROGRAM2_PARTA_INC_FUNCTIONS_H_
#define _PROGRAM2_PARTA_INC_FUNCTIONS_H_
#include <cmath>
#include <fstream>
#include <iostream>
using std::string;
int* ReadInput(string file_name, int* kSize);
void MaxHeapBottomUp(string file_name);
void MinHeapBottomUp(string file_name);
void PrintHeap(int* array, int size);

#endif  // _PROGRAM2_PARTA_INC_FUNCTIONS_H_