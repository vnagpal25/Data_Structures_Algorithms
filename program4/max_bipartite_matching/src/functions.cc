/**
 * Copyright 2023 - Class Implementation for Maximum Bipartite Matching
 * @author vnagpal
 */
#include "max_bipartite_matching/inc/functions.h"  // class header

// for readability of code
using std::ifstream, std::ofstream, std::cout, std::endl, std::stod, std::find;

void MaxBipartiteMatching::PrintResults() {
  // for writing to a file
  ofstream out_file("output.txt");

  // writes all the pairs in the Matching to file
  for (size_t i = 0; i < M.size(); i++)
    out_file << "(" << M[i].first.node_num_ << ", " << M[i].second.node_num_
             << ")" << endl;
}

void MaxBipartiteMatching::ModifyInMatching(Node v, int label) {
  // goes through all the node pairs in M, and updates their labels
  for (size_t i = 0; i < M.size(); i++) {
    if (M[i].first.node_num_ == v.node_num_) M[i].first.label_ = label;
    if (M[i].second.node_num_ == v.node_num_) M[i].second.label_ = label;
  }
}

void MaxBipartiteMatching::ModifyInQueue(Node v, int label) {
  // temp queue which will contain all modified and unmodified vertices
  queue<Node> temp_queue;

  // "iterates" through whole queue
  while (!Q.empty()) {
    Node x = Q.front();
    Q.pop();

    // updates label
    if (x == v) x.label_ = label;
    temp_queue.push(x);  // queues node regardless of modification
  }
  Q.swap(temp_queue);  // swap the original queue with the temporary queue
}

void MaxBipartiteMatching::SetNodeLabel(Node v, int label) {
  // modifies node's label in U, V, Q, and M

  // iterates through V or Q and updates the label for the node
  if (Contains(V, v)) {
    for (size_t i = 0; i < V.size(); i++)
      if (v == V[i]) V[i].label_ = label;
  } else if (Contains(U, v)) {
    for (size_t i = 0; i < U.size(); i++)
      if (v == U[i]) U[i].label_ = label;
  }
  // find + modify the node's label in Q
  ModifyInQueue(v, label);

  // find/modify the node's label in M
  ModifyInMatching(v, label);
}

MaxBipartiteMatching::Node MaxBipartiteMatching::LabelMate(Node w) {
  // iterates through the matching M, and label's w's mate with w's node num,
  // then returns the mate
  for (size_t i = 0; i < M.size(); i++) {
    if (M[i].first == w) {
      SetNodeLabel(M[i].second, w.node_num_);
      return M[i].second;
    } else if (M[i].second == w) {
      SetNodeLabel(M[i].first, w.node_num_);
      return M[i].first;
    }
  }
  // safety/warning prevention
  return {0, 0, 0};
}

void MaxBipartiteMatching::UpdateFreedoms() {
  // iterate through M,
  for (size_t i = 0; i < M.size(); i++) {
    // now that we have which elements are not "free", let us update their
    // freedoms in V
    for (size_t j = 0; j < V.size(); j++)
      if ((M[i].first == V[j]) || (M[i].second == V[j])) V[j].free_ = false;
    // updates freedom in U
    for (size_t k = 0; k < U.size(); k++)
      if ((M[i].first == U[k]) || (M[i].second == U[k])) U[k].free_ = false;
  }
}

void MaxBipartiteMatching::ReinitializeQueue() {
  // empties Q if already has elements
  while (!Q.empty()) Q.pop();

  // find all free vertices in V, and queue them
  for (Node v : V)
    if (v.free_) Q.push(v);
}

void MaxBipartiteMatching::RemoveLabels() {
  // resets all labels to zero, after an augmenting path has been augmented with
  // M
  for (size_t i = 0; i < V.size(); i++) V[i].label_ = 0;
  for (size_t j = 0; j < U.size(); j++) U[j].label_ = 0;
}

void MaxBipartiteMatching::Add(NodePair toAdd) {  // adds pair to matching
  M.push_back(toAdd);
}

void MaxBipartiteMatching::Remove(NodePair toRemove) {
  // iterates through M to find a particular pair and removes it from M
  for (auto it = M.begin(); it != M.end(); ++it) {
    if ((it->first == toRemove.first) && (it->second == toRemove.second)) {
      M.erase(it);
      return;
    }
  }
}

MaxBipartiteMatching::Node MaxBipartiteMatching::GetNodeByValue(int node_val) {
  // returns if the node is in V
  for (size_t i = 0; i < V.size(); i++)
    if (V[i].node_num_ == node_val) return V[i];

  // returns if the node is in U
  for (size_t j = 0; j < U.size(); j++)
    if (U[j].node_num_ == node_val) return U[j];

  // sanity/safety check to prevent warnings
  return {0, 0, 0};
}

template <class T>
bool MaxBipartiteMatching::Contains(vector<T> set, T element) {
  // iterates through set to see if element is contained in set
  for (size_t i = 0; i < set.size(); i++)
    if (set[i] == element) return true;
  return false;
}

bool MaxBipartiteMatching::IsAdjacent(int first_node, int second_node) {
  // checks if a link exists between first_node and second_node
  return (adj_mat[first_node - 1][second_node - 1] == 1);
}

void MaxBipartiteMatching::ParseLine(vector<Node>* V, string line) {
  // while the line exists
  while (line.size()) {
    // finds the space
    const int index = static_cast<int>(line.find(" "));

    // npos is -1; index will be -1 if " " isn't found
    if (index != static_cast<int>(string::npos)) {
      // gets the string from beginning to space
      string token = line.substr(0, index);

      // pushes back to vector everything up until delimiter, stoi() converts
      // from a string to an integer

      // this is pushing back a struct of type Node, first part of struct is the
      // value of the node(i.e. 1,...,n), the second value defines if it is
      // free/unmatched
      // since we are starting with them all as unmatched, this will default to
      // true at the beginning, third value is the label of the node(which is
      // important for augmenting paths)
      V->push_back({(stoi(token)), true, 0});

      // changes the string to remove the
      // part just pushed to the vector
      line = line.substr(index + 1);
    } else {
      V->push_back({(stoi(line)), true, 0});  // " " not found, last element
      line = "";                              // exit condition for while loop
    }
  }
}

void MaxBipartiteMatching::ReadInput(string file_name) {
  // opens file for reading
  ifstream in_file(file_name);

  string line;  // to be read

  // reads first line and pushes contents to V
  getline(in_file, line);
  ParseLine(&V, line);

  // reads second line and pushes contents to U
  getline(in_file, line);
  ParseLine(&U, line);

  // calculates size of Graph Adjacency Matrix
  size_ = V.size() + U.size();

  // allocates memory for 2D array in C++
  adj_mat = new int*[size_];
  for (int i = 0; i < size_; i++) adj_mat[i] = new int[size_];

  // populates 2D array from file, element by element
  for (int i = 0; i < size_; i++)
    for (int j = 0; j < size_; j++) in_file >> adj_mat[i][j];
}

void MaxBipartiteMatching::MaxBipartiteMatch(string file_name) {
  // populates graph adjacency matrix, V, and U
  ReadInput(file_name);

  // Start of Algorithm, initializes traversal queue of free nodes
  ReinitializeQueue();

  // BFS type traversal, iterates through queue of free nodes
  while (!Q.empty()) {
    Node w = Q.front();  // w ← Front(Q)
    Q.pop();             // Dequeue(Q)

    // if w ϵ V
    if (Contains(V, w)) {
      // for loop iterates through all of the vertices in the Graph
      for (int i = 0; i < size_; i++) {
        // checks if w is connected to a particular vertex
        if (IsAdjacent(w.node_num_, i + 1)) {
          // node specified by u is adjacent to w
          Node u = GetNodeByValue(i + 1);

          // if u is free and unmatched
          if (u.free_) {
            // augment pair to matching
            Add({w, u});

            // start of backtracking/augmenting path, deletes pairs that were in
            // the matching, and adds alternating pairs to the matching to
            // accommodate for the new pair in the matching
            Node v = w;
            // while v is labeled (1, 2, 3, ..., n)
            while (v.label_ != 0) {
              // deletes previously existing adjacent pair(edge [v, u] was in
              // |M|, but now is in |E|-|M|)
              //  u ← vertex indicated by v’s label
              u = GetNodeByValue(v.label_);
              // M ← M − (v, u)
              Remove({v, u});

              // adds new edge to the matching to preserve alternating property
              // of augmenting paths(edge [v, u] was in |E-M|, but now is in
              // |M|)
              //  v ← vertex indicated by u’s label
              v = GetNodeByValue(u.label_);
              // M ← M ∪ (v, u)
              Add({v, u});
            }
            // remove all vertex labels (make them zero), since a new matching
            // has been achieved
            RemoveLabels();

            // update all vertices freedom, based on the matching M
            UpdateFreedoms();

            // reinitialize Q with all free vertices in V
            ReinitializeQueue();
            break;
          } else {
            // u is matched, labels u if it's unlabeled and not in the matching,
            // and enqueues it.
            // will be used for augmenting a path
            if (!Contains(M, {w, u}) && (u.label_ == 0)) {
              SetNodeLabel(u, w.node_num_);
              Q.push(u);
            }
          }
        }
      }
    } else {
      // w ∈ U(and matched)
      Node v = LabelMate(w);  // label the mate v of w with w
      Q.push(v);              // Enqueue(Q, v)
    }
  }

  // Print results to output file
  PrintResults();
}

MaxBipartiteMatching::~MaxBipartiteMatching() {
  // deallocating the memory for each row of the matrix, then the matrix itself
  for (int i = 0; i < size_; i++) delete[] adj_mat[i];
  delete[] adj_mat;

  // avoids usage after deallocation, for safety
  adj_mat = nullptr;
}
