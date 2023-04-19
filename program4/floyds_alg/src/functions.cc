/**
 * Copyright 2023 - Function implementations for Floyd's Algorithm
 * Author - vnagpal
 */
#include "floyds_alg/inc/functions.h"
// for readability of code
using std::ifstream, std::ofstream, std::cout, std::cerr, std::endl,
    std::chrono::microseconds, std::chrono::high_resolution_clock, std::stod,
    std::min;

vector<vector<double>> ReadInput(string file_name, int* kSize) {
  ifstream file_in(file_name);
  vector<vector<double>> weight_mat;

  string line;
  while (file_in.good()) {
    getline(file_in, line);
    // line now has a row of the matrix
    vector<double> row;
    while (line.size()) {
      // finds the space
      const int index = static_cast<int>(line.find(" "));
      // npos is -1; index will be -1 if kUS isn't found
      if (index != static_cast<int>(string::npos)) {
        // gets the string from beginning to space
        string token = line.substr(0, index);

        // pushes back to vector everything up until delimiter
        row.push_back(stod(token));

        // changes the string to remove the
        // part just pushed to the vector
        line = line.substr(index + 1);
      } else {
        row.push_back(stod(line));  // " " not found, last element
        line = "";                  // exit condition for while loop
      }
    }
    weight_mat.push_back(row);
  }
  return weight_mat;
}

void FloydsAlgorithm(string file_name) {
  int size = 0;
  vector<vector<double>> weight_mat = ReadInput(file_name, &size);

  for (int i = 0; i < static_cast<int>(weight_mat.size()); i++) {
    for (int j = 0; j < static_cast<int>(weight_mat[i].size()); j++) {
      if ((i != j) && weight_mat[i][j] == 0) {
        cout << "shouldn't print" << endl;
        weight_mat[i][j] = std::numeric_limits<double>::infinity();
      }
      cout << weight_mat[i][j] << "\t";
    }
    cout << endl;
  }
  cout << endl;
  vector<vector<double>> dist_mat = weight_mat;
  for (size_t k = 0; k < dist_mat.size(); k++) {
    for (size_t i = 0; i < dist_mat.size(); i++) {
      for (size_t j = 0; j < dist_mat.size(); j++) {
        dist_mat[i][j] = min(dist_mat[i][j], dist_mat[i][k] + dist_mat[k][j]);
      }
    }
  }
  for (size_t i = 0; i < dist_mat.size(); i++) {
    for (size_t j = 0; j < dist_mat.size(); j++) {
      cout << dist_mat[i][j] << "\t";
    }
    cout << endl;
  }
}