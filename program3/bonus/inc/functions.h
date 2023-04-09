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

/**
 * Function is meant to read a file and extract the pattern being searched for,
 * and the text that will be searched through
 * @param file_name name of the file that will be opened
 * @param search_pattern pass by ptr var that represents the pattern being
 * searched for
 * @param search_text pass by ptr var that represents the text being searched
 * through
 */
void ReadInput(string file_name, string* search_pattern, string* search_text);

/**
 * Function is meant to calculate the shift table for Horspool's Algorithm for
 * each letter in the pattern
 * @param shift_table array that will contain all the shifts of each letter in
 * the pattern
 * @param table_size size of the alphabet, and thus the size of the table, will
 * be 27
 * @param search_pattern the search pattern string for which the shift table is
 * being constructed
 */
void BadSymbolShiftTable(int* shift_table, int table_size,
                         string search_pattern);

void GoodSuffixShiftTable(int* shift_table, string search_pattern);

int findShift(string search_pattern, string substring, string mismatch);
/**
 * Helper function that is meant to calculate the index of each letter within
 * the alphabet: a - 0, b - 1, c - 2, ..., z - 25, ' ' - 26
 * @param c the character for which the index is being calculated
 * @return the index of the character
 */
int CharIndex(char c);

/**
 * Output function, that is meant to write the index of the first letter within
 * the main text of the found substring to output.txt
 * @param i the index of the found substring
 */
void WriteIndex(int i);

/**
 * Main Boyer-Moore's Algorithm
 * @param file_name name of the file, within which the pattern and the text are
 * located
 */
void BoyerMoore(string file_name);
#endif  // PROGRAM3_PARTA_INC_FUNCTIONS_H_
