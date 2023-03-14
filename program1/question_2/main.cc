#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "functions.h"
using std::cout, std::endl, std::string, std::vector, std::ofstream;
int main() {
  string file_name = "input.txt";
  vector<double> values = ReadInput("input.txt");
  for (int i = 0; i < values.size(); i++) cout << values[i] << " ";
  cout << "unsorted nums.size() - 1 = " << values.size() - 1 << endl;
  QuickSort(values, 0, values.size() - 1);
  ofstream out_file("output.txt");
  for (int i = 0; i < values.size(); i++) out_file << values[i] << " ";
  out_file << endl;
  return 0;
}