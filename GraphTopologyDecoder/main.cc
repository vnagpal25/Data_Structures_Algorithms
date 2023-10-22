// Copyright 2023 CSCE350
// Author vnagpal
// main method for checking topology type of input file
#include <time.h>

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "functions.h"
using std::cout, std::endl, std::cin, std::ifstream, std::ofstream, std::string;
int main() {
  int size = 0;
  string file_name = "input.txt";

  std::chrono::microseconds elapsed_time;

  char** adjacency_mat = ReadInput(file_name, &size);

  cout << "square adjacency matrix of size n = " << size << endl;
  PrintMatrix(adjacency_mat, size);

  string message = "The given adjacency matrix represents a graph with ";

  auto start = std::chrono::high_resolution_clock::now();
  if (IsMesh(adjacency_mat, size)) {
    message += "a fully connected mesh topology";
    auto end = std::chrono::high_resolution_clock::now();
    elapsed_time =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << endl;
    ofstream out_file("output.txt");
    out_file << message << endl;
    out_file.close();
    return 0;
  }

  start = std::chrono::high_resolution_clock::now();
  if (IsStar(adjacency_mat, size)) {
    message += "a star topology";
    auto end = std::chrono::high_resolution_clock::now();
    elapsed_time =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << endl;
    ofstream out_file("output.txt");
    out_file << message << endl;
    out_file.close();
    return 0;
  }

  start = std::chrono::high_resolution_clock::now();
  if (IsRing(adjacency_mat, size)) {
    message += "a ring topology";
    auto end = std::chrono::high_resolution_clock::now();
    elapsed_time =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << endl;
    ofstream out_file("output.txt");
    out_file << message << endl;
    out_file.close();
    return 0;
  }

  message += "neither of the 3 expected topologies";
  cout << "Elapsed time: " << 0 << " milliseconds" << endl;
  ofstream out_file("output.txt");
  out_file << message << endl;
  out_file.close();
  return 0;
}
