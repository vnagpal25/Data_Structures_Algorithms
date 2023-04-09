/**
 * Copyright 2023 - Function definitions for Horspool's Algorithm
 * Author - vnagpal
 */
#ifndef PROGRAM3_PARTA_INC_FUNCTIONS_H_
#define PROGRAM3_PARTA_INC_FUNCTIONS_H_
#include <cctype>    // char manipulation
#include <chrono>    // for execution times
#include <cmath>     // floor()
#include <fstream>   // I/O to files
#include <iostream>  // I/O
#include <string>    // string functionality
using std::string;   // readability

void ReadInput(string file_name, string* search_pattern, string* search_text);
void ShiftTable(int* shift_table, int table_size, string search_patter);
int CharIndex(char c);
void WriteIndex(int i);
void Horspool(string file_name);
#endif  // PROGRAM3_PARTA_INC_FUNCTIONS_H_