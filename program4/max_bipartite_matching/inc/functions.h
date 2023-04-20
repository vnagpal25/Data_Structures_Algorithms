/**
 * Copyright 2023 - Function definitions for Floyd's Algorithm for all pairs
 * shortest paths Author - vnagpal
 */
#ifndef PROGRAM4_MAX_BIPARTITE_MATCHING_ALG_INC_FUNCTIONS_H_
#define PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_
#include <algorithm>
#include <chrono>    // for execution times
#include <cmath>     // floor()
#include <fstream>   // I/O to files
#include <iostream>  // I/O
#include <queue>
#include <string>                            // string functionality
#include <vector>                            // vector functionality
using std::string, std::vector, std::queue;  // readability

bool Contains(vector<Node> nodes, Node node);

bool IsAdjacent(int first_node_val, int second_node_val, int** adj_mat);

void ParseLine(vector<Node>* V, string line);

int** ReadInput(string file_name, vector<Node>* V, vector<Node>* U, int* size);

void MaxBipartiteMatch(string file_name);

struct Node {
  int node_num_;
  bool is_free_;
};
#endif  // PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_