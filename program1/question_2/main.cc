#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "functions.h"
using std::cout, std::endl, std::string, std::vector, std::ofstream;
int main() {
  string file_name = "input.txt";
  vector<double> values = ReadInput("input.txt");

  std::chrono::microseconds elapsed_time;
  auto start = std::chrono::high_resolution_clock::now();

  QuickSort(values, 0, values.size() - 1);
  
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << endl;

  ofstream out_file("output.txt");
  for (int i = 0; i < static_cast<int>(values.size()); i++)
    out_file << values[i] << " ";
  out_file << endl;
  return 0;
}