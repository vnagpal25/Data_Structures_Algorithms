#include "functions.h"
using std::ifstream, std::cout, std::endl;
int* ReadInput(string file_name, int* kSize) {
  ifstream file_in(file_name);

  if (!file_in) {
    std::cerr << "File could not be opened" << endl;
    exit(errno);
  }

  file_in >> *kSize;
  cout << *kSize << endl;
  int* array = new int[*kSize];

  for (int i = 0; i < *kSize; i++) {
    file_in >> array[i];
  }

  for (int i = 0; i < *kSize; i++) {
    cout << array[i] << " ";
  }
  cout << endl;

  return array;
}

void PrintHeap(int* array, int size) {
  for (int i = 0; i < size; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

void MinHeapBottomUp(string file_name) {
  // int* array = ReadInput("input.txt");
  //  implement bottom up algorithm
}

void MaxHeapBottomUp(string file_name) {
  int size;
  int* heap = ReadInput("input.txt", &size);

  // implement bottom up algorithm
  for (int i = floor(size / 2); i >= 1; i--) {
    int k = i-1;

    int v = heap[k];

    bool isHeap = false;
    while (!isHeap && 2 * k <= size) {
      int j = 2 * k;
      if (j < size + 1) {
        cout << "There are two children" << endl;
        if (heap[j] < heap[j+1]) {
          cout << "heap[" << j << "] < "
               << "heap[" << j+1 << "]" << endl;

          j++;
        } else {
          cout << "heap[" << j << "] > "
               << "heap[" << j+1 << "]" << endl;

          cout << "heap[" << j << "] = " << heap[j] << endl;
          cout << "heap[" << j+1 << "] = " << heap[j+1] << endl;
        }
      }
      if (v >= heap[j]) {
        isHeap = true;
      } else {
        heap[k] = heap[j];
        k = j;
      }
    }
    heap[k] = v;
  }

  PrintHeap(heap, size);
  /**
   * for i ← n/2 downto 1 do
k ← i; v ← H[k]
heap ← false
while not heap and 2 ∗ k ≤ n do
j ← 2 ∗ k
if j<n //there are two children
if H[j ] < H[j + 1] j ← j + 1
if v ≥ H[j ]
heap ← true
else H[k]← H[j ]; k ← j
H[k]← v
  */
}
