// Copyright 2023 CSCE350
// Author vnagpal
// all function definitions
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include <time.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using std::string;

/**
 * method determines if a graph is a mesh using the adjacency matrix
 * @param adjacency_mat 2d character array representing the adjacency matrix of
 * the graph
 * @param size n for nxn adjacency matrix
 * @return true if a mesh, false if not
 */
bool IsMesh(char** adjacency_mat, int size);

/**
 * method determines if a graph is a star using the adjacency matrix
 * @param adjacency_mat 2d character array representing the adjacency matrix of
 * the graph
 * @param size n for nxn adjacency matrix
 * @return true if a star, false if not
 */
bool IsStar(char** adjacency_mat, int size);

/**
 * method determines if a graph is a ring using the adjacency matrix
 * @param adjacency_mat 2d character array representing the adjacency matrix of
 * the graph
 * @param size n for nxn adjacency matrix
 * @return true if a ring, false if not
 */
bool IsRing(char** adjacency_mat, int size);

/**
 * method prints out the adjacency matrix to the console
 * @param adjacency_mat 2d character array representing the adjacency matrix of
 * the graph
 * @param size n for nxn adjacency matrix
 */
void PrintMatrix(char** adjacency_mat, int size);

/**
 * method reads the input.txt file and populates a 2d char array representing it
 * @param file_name file name
 * @param size pass by reference pointer to the size n of the adjacency matrix
 * @return a 2d char array that is populated with 1s and 0s representing the
 * adjacency matrix
 */
char** ReadInput(string file_name, int* size);

/**
 * method checks if a binary string has all 1s
 * @param row a row of the adjacency matrix that is a binary string
 * @return true if all 1s are in the row, false if not
 */
bool allCharactersOne(string row);

/**
 * method checks if a row of the adjacency matrix has a leading one and the rest
 * of the bits are 0
 * @param row a row of the adjacency matrix that is a binary string
 * @return true if row is like 10000..., false otherwise
 */
bool leadingOneRow(string row);

/**
 * method checks if a row of the adjacency matrix contains only a single one
 * @param row a row of the adjacency matrix that is a binary string
 * @return true if row is like 1000, 0100, 0010, or 0001, false otherwise
 */
bool ContainsSingleOne(string row);

/**
 * method converts a row to its One's Complement(flips all the bits)
 * @param row a row of the adjacency matrix that is a binary string
 * @return a binary string representing the one's complement of the inputted row
 */
const char* OnesComplement(string row);

/**
 * method flips bits, helper to OnesComplement()
 * @param c 0 or 1
 * @return 1 if c is 0, 0 if c is 1
 */
char flip(char c);

/**
 * method sums all the bits in a row
 * @param row a row of the adjacency matrix that is a binary string
 * @param size length of the row
 * @return the sum of the row (1010 returns 2)
 */
int sum(char* row, int size);
#endif  // _FUNCTIONS_H_
