// Copyright 2023 CSCE350
// Author vnagpal
// all function implementations
#include "functions.h"

#include <algorithm>
#include <bitset>
#include <numeric>
#include <string>
#include <vector>
using std::cout, std::endl, std::cin, std::ifstream, std::ofstream, std::string,
    std::stoi, std::bitset, std::vector, std::accumulate;

bool IsMesh(char** adjacency_mat, int size) {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      /**
       * Two things must be satisfied here:
       * 1. Either the element is along the diagonal (row = col), then the
       * element must be 0.
       * 2. Or its not along the diagonal (row!=col), then the element
       * must be 1
       */
      bool diagonal_condition =
          (col == row) && (adjacency_mat[row][col] == '0');
      bool non_diagonal_condition =
          (col != row) && (adjacency_mat[row][col] == '1');
      if (!diagonal_condition && !non_diagonal_condition) return false;
    }
  }
  return true;
}

bool IsStar(char** adjacency_mat, int size) {
  for (int i = 0; i < size; i++)  // checks if the graph has no loops
    if (adjacency_mat[i][i] != '0') return false;

  char* cur_row = adjacency_mat[0];
  // following if-block handles if matrix is of the form:
  /**
   * 0111
   * 1000
   * 1000
   * 1000
   */
  if (cur_row[0] == '0' && allCharactersOne(string(cur_row).substr(1))) {
    for (int row = 1; row < size; row++)
      if (!leadingOneRow(string(adjacency_mat[row]))) return false;
    return true;
  } else if (ContainsSingleOne(string(cur_row))) {
    // if statement checked if the first row was of form: 01000, 00100, 00010,
    // or 00001(for 5x5). NOW CHECK REST OF THE ROWS FOR IF THEY ARE THE SAME,
    // OR IF THEY ARE THE ALL ONES ROW:
    // conditions to be satisfied:
    //- (size - 2) other rows must be the same as the
    // first row(size total rows, 1 row already checked, 1 all 1s row)
    //- whichever column is 1 in the first row, that row must be all ones with 1
    // '0'
    int main_row_index =
        string(cur_row).find('1');  // finds which column contains the one(which
                                    // node is the center of the star)

    // checks if the row of the center node is of the proper form(one's
    // complement of other rows)
    string ones_comp = string(OnesComplement(string(cur_row)));
    if (main_row_index == static_cast<int>(string::npos) ||
        string(adjacency_mat[main_row_index]) != ones_comp)
      return false;

    int count = 0;                  // count of edge nodes
    for (int i = 1; i < size; i++)  // start after first row
      if (string(adjacency_mat[i]) == string(cur_row)) count++;
    if (count != (size - 2)) return false;
    return true;
  }
  return false;
}

bool IsRing(char** adjacency_mat, int size) {
  // true for visited, false for not. initializes all as false because all are
  // unvisited
  vector<bool> visited(size, false);

  // j1 is the index of the first occurrence of a 1 in the first row, jn_1 is
  // the second occurrence, initialize as -1 initially
  // j1 will also be the "current row"
  int j1 = -1, jn_1 = -1;

  // Scan row 0 to find j1 and jn-1
  for (int i = 0; i < size; i++) {
    if (adjacency_mat[0][i] == '1') {
      if (j1 == -1)
        j1 = i;  // sets j1 first
      else if (jn_1 == -1)
        jn_1 = i;  // sets jn_1 next
      else
        return false;  // if there are more than 2 1s in the row, its not a ring
    }
    if (sum(adjacency_mat[i], size) != 2)
      return false;  // checks if the sum of each row is 2
  }

  // returns false if two ones were not found in the first row
  if (j1 == -1 || jn_1 == -1) return false;

  visited[0] = true;  // marks first row as visited

  // embark on the cycle of the ring
  while (true) {
    int j2 = -1;  // next column/vertex
    // starts at i = 1 because already dealt with first row
    for (int i = 1; i < size; i++) {
      // checks if it is a 1 and its unvisited, if it was visited it would not
      // be a ring
      if (adjacency_mat[j1][i] == '1' && !visited[i]) {
        if (j2 == -1)
          j2 = i;
        else
          return false;  // More than one unvisited column with 1 in current
                         // row, not a ring
      }
    }

    // checks if a j2 was found, and then marks the current row as visited
    if (j2 == -1) return false;  // No unmarked column with 1 in current row
    visited[j1] = true;          // marks it as visited

    // Check if we've reached the last unmarked vertex and it has the correct
    // edges(to previous traversed(j1, redundant) and beginning edge(0))
    // count checks if there is only one false value in the visited vector
    if (count(visited.begin(), visited.end(), false) == 1) {
      return (adjacency_mat[jn_1][0] == '1' && adjacency_mat[jn_1][j1] == '1');
    }

    // Proceed to the next row, update current
    j1 = j2;
  }
}

char** ReadInput(string file_name, int* kSize) {
  string line;                 // a singe line that is read from the file
  int char_count = 0;          // number of characters
  ifstream inData(file_name);  // ifstream for input.txt

  // reads until there is nothing else to read
  while (!inData.eof()) {
    getline(inData, line);  // reads a single line from the file

    int num_chars = line.length();  // counts the number of characters per line
    for (unsigned int n = 0; n < line.length(); n++) {
      if (line.at(n) == ' ') num_chars--;  // subtracts the spaces
    }
    char_count += num_chars;
  }

  // checks if number of characters is a perfect square(thus proper adjacency
  // matrix)
  if (sqrt(char_count) == floor(sqrt(char_count))) {
    ifstream input_file2(
        file_name);  // separate ifstream for populating char array

    *kSize = static_cast<int>(sqrt(char_count));  // sets size n of matrix
    char** adjacency_mat = new char*[(*kSize)];   // creates a row
    for (int i = 0; i < (*kSize); i++)
      adjacency_mat[i] =
          new char[(*kSize)];  // gives each element of the row a column

    for (int row = 0; row < (*kSize); row++)
      for (int col = 0; col < (*kSize); col++)
        input_file2 >> adjacency_mat[row][col];  // populates the matrix
    return adjacency_mat;                        // returns the matrix
  }
  return nullptr;
}

void PrintMatrix(char** adjacency_mat, int size) {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      cout << adjacency_mat[row][col] << " ";
    }
    cout << endl;
  }
}

bool allCharactersOne(string row) {
  // using logic that a binary string of length n that has all ones has a
  // decimal value of (2^n) - 1
  bitset<32> binary(row);  // makes it a binary string bitset
  int decimal =
      binary.to_ulong();  // converts the bitset to a decimal unsigned long
  return (decimal == (pow(2, row.length())) - 1);  // (2^n) - 1
}

bool leadingOneRow(string row) {
  return (row[0] == '1' && stoi(row.substr(1)) == 0);
}

bool ContainsSingleOne(string row) {
  int row_int =
      stoi(row.substr(1));  // removes first bit, and converts it to an int
  if (row_int == 1)
    return true;
  else if (row_int == 0)
    return false;
  // if a number contains a single one and the
  // rest are zeros, it should be a power of 10
  return log10(row_int) == floor(log10(row_int));
}

const char* OnesComplement(string row) {
  int len = row.length();  // length of the row
  string ones_comp = "";   // string to which a flipped bit will be concatenated
  for (int i = 0; i < len; i++) ones_comp += flip(row[i]);
  return ones_comp.c_str();
}

char flip(char c) { return (c == '0') ? '1' : '0'; }

int sum(char* row, int size) {
  int sum = 0;  // sum of the row

  // have to subtract the ASCII value of '0'
  for (int i = 0; i < size; i++) sum += (row[i] - '0');
  return sum;
}
