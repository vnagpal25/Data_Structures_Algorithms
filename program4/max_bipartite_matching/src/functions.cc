/**
 * Copyright 2023 - Function implementations for Floyd's Algorithm
 * Author - vnagpal
 */
#include "max_bipartite_matching/inc/functions.h"  // function definitions

// for readability of code
using std::ifstream, std::ofstream, std::cout, std::cerr, std::endl,
    std::chrono::microseconds, std::chrono::high_resolution_clock, std::stod,
    std::min, std::find;

bool Contains(vector<Node> nodes, Node node) {
  // return find(nodes.begin(), nodes.end(), node) != nodes.end();
  for (size_t i = 0; i < nodes.size(); i++)
    if (node.node_num_ == nodes[i].node_num_) return true;
  return false;
}

bool IsAdjacent(int first_node_val, int second_node_val, int** adj_mat) {
  return (adj_mat[first_node_val - 1][second_node_val - 1] == 1);
}

void ParseLine(vector<Node>* V, string line) {
  while (line.size()) {
    // finds the space
    const int index = static_cast<int>(line.find(" "));
    // npos is -1; index will be -1 if " " isn't found
    if (index != static_cast<int>(string::npos)) {
      // gets the string from beginning to space
      string token = line.substr(0, index);

      // pushes back to vector everything up until delimiter, stoi() converts
      // from a string to an integer

      // this is pushing back a struct of type Node, first part of struct is the
      // value of the node(i.e. 1,...,n), the second value defines if it is
      // free/unmatched
      // since we are starting with them all as unmatched, this will default to
      // true at the beginning
      V->push_back({(stoi(token)), true});

      // changes the string to remove the
      // part just pushed to the vector
      line = line.substr(index + 1);
    } else {
      V->push_back({(stoi(line)), true});  // " " not found, last element
      line = "";                           // exit condition for while loop
    }
  }
}

int** ReadInput(string file_name, vector<Node>* V, vector<Node>* U, int* size) {
  ifstream in_file(file_name);
  string line;
  getline(in_file, line);
  ParseLine(V, line);

  getline(in_file, line);
  ParseLine(U, line);

  *size = (*V).size() + ((*U).size());
  int** adj_mat = new int*[*size];

  for (int i = 0; i < *size; i++) adj_mat[i] = new int[*size];

  int count = 0;
  for (int i = 0; i < *size; i++) {
    for (int j = 0; j < *size; j++) {
      in_file >> adj_mat[i][j];
      count++;
    }
  }
  return adj_mat;
}

void MaxBipartiteMatch(string file_name) {
  vector<Node> V, U;
  int size;
  int** adj_mat = ReadInput(file_name, &V, &U, &size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << adj_mat[i][j] << " ";
    }
    cout << endl;
  }

  // Q will contain 1, 2 ,3, 4, 5 or whatever else is in V
  queue<Node> Q;
  for (size_t i = 0; i < V.size(); i++) Q.push(V[i]);

  while (!Q.empty()) {
    Node w = Q.front();  // .head()
    Q.pop();             // .dequeue()

    // if w in V
    if (Contains(V, w)) {
      // for every vertex u adjacent to w do
      // iterate through all vertices then inside that add an if statement
      // checking adjacency using the adj_mat. How to iterate over vertices?
      for (int i = 0; i < size; i++) {
        
        if (IsAdjacent(w.node_num_, i + 1, adj_mat))
          ;
      }
    } else {
      // w is in U (and matched)
    }
  }
}