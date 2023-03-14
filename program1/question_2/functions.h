#include <iostream>
#include <vector>
using std::string, std::vector;
vector<double> ReadInput(string file_name);
void QuickSort(vector<double>& values, int low, int high);
int Partition(vector<double>& values, int low, int high);
