/**
 * Copyright 2023 - Class Declaration for Maximum Bipartite Matching
 * @author vnagpal
*/
#ifndef PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_
#define PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_
#include <unistd.h>  // sleep() for debugging

#include <algorithm>  // std::find()
#include <cmath>      // floor()
#include <fstream>    // I/O to files
#include <iostream>   // I/O
#include <queue>      // queue functionality
#include <string>     // string functionality
#include <utility>    // pair data structure functionality
#include <vector>     // vector functionality
using std::string, std::vector, std::queue, std::pair,
    std::ostream;  // readability
// MaxBipartiteMatching Class for organization/housekeeping
class MaxBipartiteMatching {
 public:
  // struct to represent a Node in the graph
  struct Node {
    // identifier of node (1,2,3..., n)
    int node_num_;

    // defines node's match status
    bool free_;

    // label for augmenting paths, points to node_num of other node
    int label_ = 0;

    /**
     * Overloading == operator for a Node
     * @param node node being compared to
     * @return true if both nodes have the same identifier, false otherwise
     */
    bool operator==(const Node& node) const {
      return (node.node_num_ == node_num_);
    }
  };

  // redefining pair of two Nodes as NodePair
  typedef pair<Node, Node> NodePair;

  /**
   * Implements the Maximum Bipartite Matching Algorithm defined in textbook
   * @param file_name name of file which contains the sets V, U, and the
   * adjacency matrix of the bipartite graph G
   */
  void MaxBipartiteMatch(string file_name);

  ~MaxBipartiteMatching();

 private:
  /**
   * Overloading == operator for a pair of Nodes
   * @param left_pair lhs pair
   * @param right_pair rhs pair
   * @return true if both pairs have equivalent nodes, false otherwise
   */
  friend bool operator==(const NodePair& left_pair,
                         const NodePair& right_pair) {
    return (left_pair.first == right_pair.first &&
            left_pair.second == right_pair.second) ||
           (left_pair.first == right_pair.second &&
            left_pair.second == right_pair.first);
  }

  /**
   * Prints the results of the Maximum Bipartite Matching Algorithm to output
   * file
   */
  void PrintResults();

  /**
   * Modifies the label of a particular node in the matching set
   * @param v node who's label needs to be modified
   * @param label number of the node with which v needs to be labeled with, used
   * for augmenting paths
   */
  void ModifyInMatching(Node v, int label);

  /**
   * Modifies the label of a particular node in the queue
   * @param v node who's label needs to be modified
   * @param label number of the node with which v needs to be labeled with, used
   * for augmenting paths
   */
  void ModifyInQueue(Node v, int label);

  /**
   * Modifies the label of a particular node in V, U, Q, and M
   * @param v node who's label needs to be modified
   * @param label number of the node with which v needs to be labeled with, used
   * for augmenting paths
   */
  void SetNodeLabel(Node v, int label);

  /**
   * Given a matched node, label its mate with its identifier and return the
   * labeled mate
   * @param w matched node whose mate needs to be labeled with its identifier
   * @return the labeled mate of w
   */
  Node LabelMate(Node w);

  /**
   * Updates the .free_ member of each node in V and U based on the matching M
   */
  void UpdateFreedoms();

  /**
   * Empties and initializes Q with free vertices in V
   */
  void ReinitializeQueue();

  /**
   * Removes the labels of each node in V and U
   */
  void RemoveLabels();

  /**
   * Adds a pair to the matching
   * @param to_add pair of Nodes in V and U that need to be added to the
   * matching M
   */
  void Add(NodePair to_add);

  /**
   * Removes a pair from the matching
   * @param to_remove pair of Nodes in V and U that need to be removed from the
   * matching
   */
  void Remove(NodePair to_remove);

  /**
   * returns a node specified by node_val from U or V
   * @param node_val identifier of desired node
   * @return Node from V or U
   */
  Node GetNodeByValue(int node_val);

  /**
   * Checks if a set of values contain a particular element
   * @param element element whose existence in the set is being checked
   * @param set set of elements
   * @return true if element ϵ set, false if not
   */
  template <class T>
  bool Contains(vector<T> set, T element);

  /**
   * Checks if two nodes are adjacent in the Graph specified by the adjacency
   * matrix
   * @param first_node identifier of the first node
   * @param second_node identifier of the second node
   * @return true if both nodes are adjacent, false if not
   */
  bool IsAdjacent(int first_node, int second_node);

  /**
   * Takes a string of numbers and populates a vector with its contents
   * @param V pass by pointer variable, will contain nodes based on integers in
   * line
   * @param line line that contains integers (1,... n)
   */
  void ParseLine(vector<Node>* V, string line);

  /**
   * Reads an input file and populates V, U, and adj_mat
   * @param file_name name of input file
   */
  void ReadInput(string file_name);

  vector<Node> V, U;   // bipartite vertex sets
  vector<NodePair> M;  // M contains all of the matched pairs
  queue<Node> Q;       // bfs queue of nodes being explored

  int size_;      // number of nodes in graph
  int** adj_mat;  // adjacency matrix of graph
};
#endif  // PROGRAM4_MAX_BIPARTITE_MATCHING_INC_FUNCTIONS_H_
