/**
 * Copyright 2023 - Function implementations for Floyd's Algorithm
 * Author - vnagpal
 */
#include "floyds_alg/inc/functions.h"
// for readability of code
using std::ifstream, std::ofstream, std::cout, std::cerr, std::endl,
    std::chrono::microseconds, std::chrono::high_resolution_clock;

double** ReadInput(string file_name, int* kSize) {
  string line;                  // a singe line that is read from the file
  int char_count = 0;           // number of characters
  ifstream in_file(file_name);  // ifstream for input.txt

  // reads until there is nothing else to read
  while (!in_file.eof()) {
    getline(in_file, line);  // reads a single line from the file

    int num_chars = line.length();  // counts the number of characters per line
    for (int n = 0; n < static_cast<int>(line.length()); n++)
      if (line.at(n) == ' ') num_chars--;  // subtracts the spaces

    char_count += num_chars;
  }

  // checks if number of characters is a perfect square(thus proper adjacency
  // matrix)
  if (sqrt(char_count) == floor(sqrt(char_count))) {
    ifstream input_file2(
        file_name);  // separate ifstream for populating char array

    *kSize = static_cast<int>(sqrt(char_count));     // sets size n of matrix
    double** adjacency_mat = new double*[(*kSize)];  // creates a row
    for (int i = 0; i < (*kSize); i++)
      adjacency_mat[i] =
          new double[(*kSize)];  // gives each element of the row a column

    for (int row = 0; row < (*kSize); row++)
      for (int col = 0; col < (*kSize); col++)
        input_file2 >> adjacency_mat[row][col];  // populates the matrix
    return adjacency_mat;                        // returns the matrix
  }
  return nullptr;
}

void FloydsAlgorithm(string file_name) {
  int size = 0;
  double** weight_mat = ReadInput(file_name, &size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) cout << weight_mat[i][j] << " ";
    cout << endl;
  }
}