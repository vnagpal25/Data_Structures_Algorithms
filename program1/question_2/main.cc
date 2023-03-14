#include <iostream>
#include <string>
#include <vector>

#include "functions.h"
using std::cout, std::endl, std::string, std::vector;
int main() {
  string file_name = "input.txt";
  vector<double> unsorted_nums = ReadInput("input.txt");
  for (int i = 0; i < unsorted_nums.size(); i++)
    cout << unsorted_nums[i] << " ";
  cout << "unsorted nums.size() - 1 = " << unsorted_nums.size() - 1 << endl;
  QuickSort(unsorted_nums, 0, unsorted_nums.size() - 1);
  for (int i = 0; i < unsorted_nums.size(); i++)
    cout << unsorted_nums[i] << " ";
  cout << endl;
  return 0;
}