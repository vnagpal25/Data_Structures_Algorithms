/**
 * Copyright 2023 - Function definitions for Floyd's Algorithm for all pairs
 * shortest paths Author - vnagpal
 */
#ifndef PROGRAM4_FLOYDS_ALG_INC_FUNCTIONS_H_
#define PROGRAM4_FLOYDS_ALG_INC_FUNCTIONS_H_
#include <chrono>                // for execution times
#include <cmath>                 // floor()
#include <fstream>               // I/O to files
#include <iostream>              // I/O
#include <string>                // string functionality
#include <vector>                // vector functionality
using std::string, std::vector;  // readability

/**
 * method reads the input.txt file and populates a 2d double vector representing
 * it
 * @param file_name file name
 * @return a 2d double vector that is filled with non-negative floating point
 * numbers representing the distance between nodes
 */
vector<vector<double>> ReadInput(string file_name);

/**
 * method writes the output distance matrix to a file "output.txt"
 * @param dist_mat 2d double vector that represents the distance matrix of
 * shortest path between two nodes, as a result of Floyd's Algorithm
 */
void WriteOutput(vector<vector<double>> dist_mat);

/**
 * method runs floyds algorithm to solve the All-Pairs shortest paths problem
 * The weight matrix of the graph will be extracted from file_name
 * @param file_name contains the weight matrix of a specific graph
 */
void FloydsAlgorithm(string file_name);
#endif  // PROGRAM4_FLOYDS_ALG_INC_FUNCTIONS_H_
