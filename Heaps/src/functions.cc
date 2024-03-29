/**
 * Copyright 2023 - Function implementations for Heapifying
 * Author - vnagpal
 */
#include "partA/inc/functions.h"
// for readability of code
using std::ifstream, std::ofstream, std::cout, std::cerr, std::endl,
    std::chrono::microseconds, std::chrono::high_resolution_clock;

int* ReadInput(string file_name, int* kSize) {
  // initializes file reader
  ifstream file_in(file_name);

  // error checking
  if (!file_in) {
    cerr << "File could not be opened" << endl;
    exit(errno);
  }

  // first line of file should be heap size
  file_in >> *kSize;

  // initializes heap array of that size
  int* array = new int[*kSize];

  // populates array
  for (int i = 0; i < *kSize; i++) file_in >> array[i];

  // returns array
  return array;
}

void PrintHeap(int* array, int size) {
  // initializes the file writer
  ofstream out_file("output.txt");

  // writes each element of the heap space delimited
  for (int i = 0; i < size; i++) out_file << array[i] << " ";
}

void MaxHeapBottomUp(string file_name) {
  int size;  // size of the heap

  // populates heap array from input.txt
  int* heap = ReadInput("input.txt", &size);

  // for measuring algorithm time
  microseconds elapsed_time;  // run time = end - start
  auto start = high_resolution_clock::now();

  // implement bottom up algorithm
  for (int i = floor(size / 2); i >= 1; i--) {
    // -1 to ensure that heap logic for indexing is obeyed, for a heap the
    // starting index is 1, but in c++ the starting index is 0
    int k = i - 1;

    // keeps track of the parent node
    int v = heap[k];

    // boolean to decide whether the parental dominance or "heap" condition is
    // satisfied or not
    bool is_heap = false;

    // while loop iterates until parental dominance condition is satisfied, or
    // end of heap has been reached(v will be the last child node/node in the
    // heap). If 2k + 1 <= size, this means there are no more child nodes. Again
    // the - 1 is so that the the indexing is properly obeyed
    while (!is_heap && (2 * k + 1 <= size)) {
      // in heap, j = 2k is the index of the first child of an element with
      // index k
      int j = 2 * k + 1;  // basically j - 1  = 2k, because of indexing

      // again, j + 1 instead of j here because of indexing, checking if the
      // element number is less than the size. If yes, that means there is still
      // at least another child on the same level, so we need to compare its
      // value to the first child nodes. if the second child is bigger, need to
      // increment j, so that its value reflects that of the larger child.
      // Ultimately, we need to compare the parent to the largest child to
      // determine a swap. If no, that means it is the last child(last element
      // in the heap).
      if ((j + 1 < size) && (heap[j] < heap[j + 1])) j++;

      if (v >= heap[j]) {
        // this means that the parental dominance condition is true, no need to
        // swap
        is_heap = true;
      } else {
        // if the parental dominance condition is violated (the larger child is
        // bigger than the parent), then we need to swap the parent with its
        // child
        // places the child in the parents node
        heap[k] = heap[j];

        // setting k to j. For the next iteration, it will check the parental
        // dominance condition if the displaced node (with value v) can be
        // placed at new k.
        k = j;
      }
    }
    // this places the child in the parents node if there was a
    // swap, if there was not a swap, it does not change anything (place element
    // back in its own spot). Also if 2k + 1 was >= size, the node that was
    // being continuously displaced, would be placed in this new spot.
    heap[k] = v;
  }

  // stops measuring execution time since heap is constructed
  auto end = high_resolution_clock::now();
  elapsed_time = std::chrono::duration_cast<microseconds>(end - start);
  cout << "Execution time for creating Max Heap: " << elapsed_time.count()
       << " microseconds" << endl;

  // writes heap to output.txt
  PrintHeap(heap, size);
}

void MinHeapBottomUp(string file_name) {
  int size;  // size of the heap

  // populates heap array from input.txt
  int* heap = ReadInput("input.txt", &size);

  // for measuring algorithm time
  microseconds elapsed_time;  // run time = end - start
  auto start = high_resolution_clock::now();

  // implement bottom up algorithm
  for (int i = floor(size / 2); i >= 1; i--) {
    // -1 to ensure that heap logic for indexing is obeyed, for a heap the
    // starting index is 1, but in c++ the starting index is 0
    int k = i - 1;

    // keeps track of the parent node
    int v = heap[k];

    // boolean to decide whether the parental dominance or "heap" condition is
    // satisfied or not
    bool is_heap = false;

    // while loop iterates until parental dominance condition is satisfied, or
    // end of heap has been reached(v will be the last child node/node in the
    // heap). If 2k + 1 <= size, this means there are no more child nodes. Again
    // the - 1 is so that the the indexing is properly obeyed
    while (!is_heap && (2 * k + 1 <= size)) {
      // in heap, j = 2k is the index of the first child of an element with
      // index k
      int j = 2 * k + 1;  // basically j - 1  = 2k, because of indexing

      // again, j + 1 instead of j here because of indexing, checking if the
      // element number is less than the size. If yes, that means there is still
      // at least another child on the same level, so we need to compare its
      // value to the first child nodes. if the second child is smaller, need to
      // increment j, so that its value reflects that of the smaller child.
      // Ultimately, we need to compare the parent to the smaller child to
      // determine a swap. If no, that means it is the last child(last element
      // in the heap).
      if ((j + 1 < size) && (heap[j] > heap[j + 1])) j++;

      if (v <= heap[j]) {
        // this means that the parental dominance condition is true, no need to
        // swap
        is_heap = true;
      } else {
        // if the parental dominance condition is violated (the larger child is
        // bigger than the parent), then we need to swap the parent with its
        // child
        // places the child in the parents node
        heap[k] = heap[j];

        // setting k to j. For the next iteration, it will check the parental
        // dominance condition if the displaced node (with value v) can be
        // placed at new k.
        k = j;
      }
    }
    // this places the child in the parents node if there was a
    // swap, if there was not a swap, it does not change anything (place element
    // back in its own spot). Also if 2k + 1 was >= size, the node that was
    // being continuously displaced, would be placed in this new spot.
    heap[k] = v;
  }

  // stops measuring execution time since heap is constructed
  auto end = high_resolution_clock::now();
  elapsed_time = std::chrono::duration_cast<microseconds>(end - start);
  cout << "Execution time for creating Min Heap: " << elapsed_time.count()
       << " microseconds" << endl;

  // writes heap to output.txt
  PrintHeap(heap, size);
}
