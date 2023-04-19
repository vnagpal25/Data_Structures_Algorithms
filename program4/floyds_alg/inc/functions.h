/**
 * Copyright 2023 - Function definitions for Floyd's Algorithm for all pairs
 * shortest paths Author - vnagpal
 */
#ifndef PROGRAM2_FLOYDS_ALG_INC_FUNCTIONS_H_
#define PROGRAM2_FLOYDS_ALG_INC_FUNCTIONS_H_
#include <chrono>    // for execution times
#include <cmath>     // floor()
#include <fstream>   // I/O to files
#include <iostream>  // I/O
#include <string>    // string functionality
using std::string;   // readability

/**
 * method reads the input.txt file and populates a 2d double array representing
 * it
 * @param file_name file name
 * @param size pass by reference pointer to the size n of the distance matrix
 * @return a 2d char array that is populated with 1s and 0s representing the
 * distance matrix
 */
double** ReadInput(string file_name, int* size);

void FloydsAlgorithm(string file_name);
#endif  // PROGRAM2_FLOYDS_ALG_INC_FUNCTIONS_H_
