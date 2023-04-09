/**
 * Copyright 2023 - Function implementations for Horspool's Algorithm
 * Author - vnagpal
 */
#include "bonus/inc/functions.h"
using std::ifstream, std::ofstream, std::tolower, std::cout, std::cerr,
    std::endl, std::chrono::microseconds, std::chrono::high_resolution_clock,
    std::max;
void ReadInput(string file_name, string* search_pattern, string* search_text) {
  // initializes file reader
  ifstream file_in(file_name);

  // error checking
  if (!file_in) {
    cerr << "File could not be opened" << endl;
    exit(errno);
  }

  // first line of the file is going to the be the pattern to be searched for
  getline(file_in, *search_pattern);

  // second line of the file is going to be be the text to be searched through
  getline(file_in, *search_text);
}

void BadSymbolShiftTable(int* shift_table, int table_size,
                         string search_pattern) {
  // size of the pattern
  int pattern_size = search_pattern.size();

  // all of the entries are given the size of the pattern at first
  for (int i = 0; i < table_size; i++) shift_table[i] = pattern_size;

  // then the entries are changed for the characters that are in the pattern, -1
  // because no need to calculate shift for last letter in the pattern, because
  // the last character is the one that is going to be compared first in
  // horspool's
  for (int j = 0; j < pattern_size - 1; j++) {
    // gets the index of a, b, c, d ... in
    // terms of          0, 1, 2, 3, 4, ...
    int index = CharIndex(search_pattern[j]);

    // subtracts 1 for indexing, then subtracts j to get the number of letters
    // away from the end
    shift_table[index] = pattern_size - 1 - j;
  }
}

int findShift(string search_pattern, string substring, string mismatch) {
  int pattern_len(search_pattern.length()), sublen(substring.length());
  int suff_index = pattern_len - sublen;
  string search_mismatch = mismatch;
  while (search_mismatch == mismatch) {
    int index = search_pattern.find(substring);
    search_mismatch.substr();
  }
}

void GoodSuffixShiftTable(int* shift_table, string search_pattern) {
  int pattern_size = search_pattern.size();
  for (int i = 1; i < pattern_size - 1; i++) {
    // consider substring of length i from right side,
    // find the distance from the end of the string to the closest
    // substring(same as one of length i), with a different preceding character
  }
  shift_table[0] = 1;
  shift_table[pattern_size - 1] = pattern_size;
}

int CharIndex(char c) {
  // space is the last 'letter' of the alphabet
  if (c == ' ') return 26;

  // to lowercase for safety/uniformity
  c = static_cast<char>(tolower(c));

  // returns relative position away from the letter a
  return c - 'a';
}

void WriteIndex(int i) {
  // initializes file writer
  ofstream file_out("output.txt");

  // writes the index to file
  file_out << i << endl;

  // closes file writer
  file_out.close();
}

void BoyerMoore(string file_name) {
  // relevant strings for string searching
  string search_pattern, search_text;

  // populate those strings based on the input file
  ReadInput(file_name, &search_pattern, &search_text);

  // for measuring algorithm time
  microseconds elapsed_time;  // run time = end - start
  auto start = high_resolution_clock::now();

  // size of each string
  int pattern_size(search_pattern.size()), text_size(search_text.size());

  // 26 in alphabet plus the space
  const int kTableSize = 27;
  int bad_shift_table[kTableSize];

  // populates bad shift table
  BadSymbolShiftTable(bad_shift_table, kTableSize, search_pattern);

  int good_shift_table[pattern_size];
  GoodSuffixShiftTable(good_shift_table, search_pattern);

  for (int i = 0; i < pattern_size - 1; i++) cout << good_shift_table[i] << " ";
  cout << endl;
  // starts the search, by aligning the first character of the pattern with the
  // first character of the text. 'i' keeps track of the right most index of the
  // pattern as it being compared to the text.
  int i = pattern_size - 1;

  // until the rightmost letter of the pattern aligns with the right most letter
  // of the text
  // while (i <= text_size - 1) {
  //   // k keeps track of how many letters match from the right side of the
  //   string int k = 0;

  //   // Stops when pattern is completely checked or when one letter is found
  //   that
  //   // doesn't match. Otherwise increments k (letters are being matched)
  //   while ((k <= pattern_size - 1) &&
  //          (search_pattern[pattern_size - 1 - k] == search_text[i - k]))
  //     k++;

  //   if (k == pattern_size) {
  //     // The pattern was found!, writes the index of the pattern which will
  //     be:
  //     //  the index of the last letter of the pattern when it is lined up
  //     //  against the text(i) minus the length of the pattern to get the
  //     //  beginning of the pattern's index, and then a + 1 to account for off
  //     by
  //     //  1 error

  //     // stop measuring execution time since algorithm is finished
  //     auto end = high_resolution_clock::now();
  //     elapsed_time = std::chrono::duration_cast<microseconds>(end - start);
  //     cout << "Execution time for executing Boyer Moore's Algorithm: "
  //          << elapsed_time.count() << " microseconds" << endl;

  //     // writing index to ouput file
  //     WriteIndex(i - pattern_size + 1);
  //     return;
  //   } else {
  //     // it was not found ... :(
  //     //  gets the character index 0, 1, 2, ... 26 in the alphabet for the
  //     //  current character in the text
  //     int char_index = CharIndex(search_text[i]);

  //     // shifts over by predetermined amount to avoid useless checks; matches
  //     // the right most letter of the pattern with the next occurrence of
  //     that
  //     // character
  //     int d1, d2, d;
  //     // bad symbol shift
  //     d1 = max(bad_shift_table[char_index] - k, 1);
  //     // good suffix shift
  //     // d2
  //     d = (k > 0) ? max(d1, d2) : d1;
  //     i += d;
  //   }
  //}

  // stop measuring execution time since algorithm is finished
  auto end = high_resolution_clock::now();
  elapsed_time = std::chrono::duration_cast<microseconds>(end - start);
  cout << "Execution time for executing Boyer Moore's Algorithm: "
       << elapsed_time.count() << " microseconds" << endl;

  // wasn't found, so returns an index of -1
  WriteIndex(-1);
}
