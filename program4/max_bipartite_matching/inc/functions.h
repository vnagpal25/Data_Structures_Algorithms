#ifndef PROGRAM4_MAX_BIPARTITE_MATCHING_ALG_INC_FUNCTIONS_H_
#define PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_
#include <unistd.h>

#include <algorithm>
#include <chrono>    // for execution times
#include <cmath>     // floor()
#include <fstream>   // I/O to files
#include <iostream>  // I/O
#include <queue>
#include <string>  // string functionality
#include <utility>
#include <vector>                                       // vector functionality
using std::string, std::vector, std::queue, std::pair;  // readability
class MaxBipartiteMatching {
 public:
  struct Node {
    int node_num_;
    bool is_free_;
    int label = 0;
  };

  void PrintResults();

  void ModifyInMatching(Node v, int label);

  void ModifyInQueue(Node v, int label);

  void SetNodeLabel(Node v, int label);

  Node LabelMate(Node w);

  void UpdateFreedoms();

  void ReinitializeQueue();

  void RemoveLabels();

  void Add(pair<Node, Node> toAdd);

  void Remove(pair<Node, Node> toRemove);

  Node GetNodeByValue(int node_val);

  bool Contains(vector<pair<Node, Node>> pairs, pair<Node, Node> pair);

  bool Contains(vector<Node> nodes, Node node);

  bool IsAdjacent(int first_node_val, int second_node_val, int** adj_mat);

  void ParseLine(vector<Node>* V, string line);

  void ReadInput(string file_name);

  void MaxBipartiteMatch(string file_name);

 private:
  vector<Node> V, U;
  int size_;
  int** adj_mat;
  vector<pair<Node, Node>> M;  // M contains all of the matched pairs
  queue<Node> Q;
};
#endif  // PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_