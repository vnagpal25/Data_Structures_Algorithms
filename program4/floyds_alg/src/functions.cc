/**
 * Copyright 2023 - Function implementations for Floyd's Algorithm
 * Author - vnagpal
 */
#include "floyds_alg/inc/functions.h"  // function definitions

// for readability of code
using std::ifstream, std::ofstream, std::cout, std::cerr, std::endl,
    std::chrono::microseconds, std::chrono::high_resolution_clock, std::stod,
    std::min;

vector<vector<double>> ReadInput(string file_name) {
  // opens file for reading
  ifstream file_in(file_name);

  // to return weight 2D matrix
  vector<vector<double>> weight_mat;

  string line;
  while (file_in.good()) {
    getline(file_in, line);
    // line now has a row of the matrix
    vector<double> row;
    while (line.size()) {
      // finds the space
      const int index = static_cast<int>(line.find(" "));
      // npos is -1; index will be -1 if " " isn't found
      if (index != static_cast<int>(string::npos)) {
        // gets the string from beginning to space
        string token = line.substr(0, index);

        // pushes back to vector everything up until delimiter, stod() converts
        // from a string to a float note stod("inf")  = infinity, which is a
        // very cool feature
        row.push_back(stod(token));

        // changes the string to remove the
        // part just pushed to the vector
        line = line.substr(index + 1);
      } else {
        row.push_back(stod(line));  // " " not found, last element
        line = "";                  // exit condition for while loop
      }
    }
    weight_mat.push_back(row);  // pushes back each row to the matrix
  }
  return weight_mat;
}

void WriteOutput(vector<vector<double>> dist_mat) {
  // opens file for writing
  ofstream out_file("output.txt");

  for (size_t i = 0; i < dist_mat.size(); i++) {
    // writes out each row of the weight matrix to one line
    for (size_t j = 0; j < dist_mat.size(); j++)
      out_file << dist_mat[i][j] << " ";
    out_file << endl;
  }
}

void FloydsAlgorithm(string file_name) {
  // reads the weight matrix from the input file
  vector<vector<double>> weight_mat = ReadInput(file_name);

  // D ^ (0) = W
  vector<vector<double>> dist_mat = weight_mat;
  size_t size = dist_mat.size();

  // outer for loop iterates through all possible intermediary nodes, k = 0 can
  // go through node 0, k = 1 can go through nodes 0, 1, k = n can go through
  // nodes 0, 1, ..., n
  for (size_t k = 0; k < size; k++) {
    // this for loop iterates through all possible source nodes i
    for (size_t i = 0; i < size; i++) {
      // this for loop iterates through all possible destination nodes j.
      // Element at [i][j] or equivalently [i,j] will shortest path length from
      // i to j.
      for (size_t j = 0; j < size; j++)
        dist_mat[i][j] = min(dist_mat[i][j], dist_mat[i][k] + dist_mat[k][j]);
    }
  }

  // writes the output distance matrix to the output.txt file
  WriteOutput(dist_mat);

  // lets user know program is completed
  cout << "Algorithm complete! Final Distance Matrix has been written in "
          "output.txt"
       << endl;
}
