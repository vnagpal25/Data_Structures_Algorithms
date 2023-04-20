/**
 * Copyright 2023 - Function implementations for Floyd's Algorithm
 * Author - vnagpal
 */
#include "max_bipartite_matching/inc/functions.h"  // function definitions

// for readability of code
using std::ifstream, std::ofstream, std::cout, std::cerr, std::endl,
    std::chrono::microseconds, std::chrono::high_resolution_clock, std::stod,
    std::min, std::find;

void MaxBipartiteMatching::PrintResults() {
  for (size_t i = 0; i < M.size(); i++)
    cout << "(" << M[i].first.node_num_ << ", " << M[i].second.node_num_ << ")"
         << endl;
}

void MaxBipartiteMatching::ModifyInMatching(Node v, int label) {
  for (size_t i = 0; i < M.size(); i++) {
    if (M[i].first.node_num_ == v.node_num_) M[i].first.label = label;
    if (M[i].second.node_num_ == v.node_num_) M[i].second.label = label;
  }
}

void MaxBipartiteMatching::ModifyInQueue(Node v, int label) {
  queue<Node> temp_queue;
  while (!Q.empty()) {
    Node x = Q.front();
    Q.pop();
    if (x.node_num_ == v.node_num_) x.label = label;
    temp_queue.push(x);  // add the struct to the temporary queue, whether or
                         // not it was modified
  }
  Q.swap(temp_queue);  // swap the original queue with the temporary queue
}

void MaxBipartiteMatching::SetNodeLabel(Node v, int label) {
  // first find the node in (V or U), Q, and M then set its value
  if (Contains(V, v)) {
    for (size_t i = 0; i < V.size(); i++)
      if (v.node_num_ == V[i].node_num_) V[i].label = label;
  } else if (Contains(U, v)) {
    for (size_t i = 0; i < U.size(); i++)
      if (v.node_num_ == U[i].node_num_) U[i].label = label;
  }
  // find+modify the node in Q
  ModifyInQueue(v, label);

  // find/modify the node in M
  ModifyInMatching(v, label);
}

MaxBipartiteMatching::Node MaxBipartiteMatching::LabelMate(Node w) {
  // Find the mate of w in M, then label that node with w.node_num_
  for (size_t i = 0; i < M.size(); i++) {
    if (M[i].first.node_num_ == w.node_num_) {
      SetNodeLabel(M[i].second, w.node_num_);
      return M[i].second;
    } else if (M[i].second.node_num_ == w.node_num_) {
      SetNodeLabel(M[i].first, w.node_num_);
      return M[i].first;
    }
  }
}

void MaxBipartiteMatching::UpdateFreedoms() {
  // iterate through M,
  for (size_t i = 0; i < M.size(); i++) {
    M[i].first;
    // now that we have which elements are not "free", let us update their
    // freedoms in V and U
    // find M[i].first in V or U and change .is_free = false
    M[i].second;
    for (size_t j = 0; j < V.size(); j++)
      if ((M[i].first.node_num_ == V[j].node_num_) ||
          (M[i].second.node_num_ == V[j].node_num_))
        V[j].is_free_ = false;

    for (size_t k = 0; k < U.size(); k++)
      if ((M[i].first.node_num_ == U[k].node_num_) ||
          (M[i].second.node_num_ == U[k].node_num_))
        U[k].is_free_ = false;
  }
}

void MaxBipartiteMatching::ReinitializeQueue() {
  // find all free vertices in V?
  for (Node v : V)
    if (v.is_free_) Q.push(v);
}

void MaxBipartiteMatching::RemoveLabels() {
  for (size_t i = 0; i < V.size(); i++) V[i].label = 0;

  for (size_t j = 0; j < U.size(); j++) U[j].label = 0;
}

void MaxBipartiteMatching::Add(pair<Node, Node> toAdd) { M.push_back(toAdd); }

void MaxBipartiteMatching::Remove(pair<Node, Node> toRemove) {
  for (auto it = M.begin(); it != M.end(); ++it) {
    if ((it->first.node_num_ == toRemove.first.node_num_) &&
        (it->second.node_num_ == toRemove.second.node_num_)) {
      M.erase(it);
      break;
    }
  }
}

MaxBipartiteMatching::Node MaxBipartiteMatching::GetNodeByValue(int node_val) {
  for (size_t i = 0; i < V.size(); i++)
    if (V[i].node_num_ == node_val) return V[i];

  for (size_t j = 0; j < U.size(); j++)
    if (U[j].node_num_ == node_val) return U[j];

  return {NULL, NULL, NULL};
}

bool MaxBipartiteMatching::Contains(vector<pair<Node, Node>> pairs,
                                    pair<Node, Node> pair) {
  for (size_t i = 0; i < pairs.size(); i++)
    if ((pairs[i].first.node_num_ == pair.first.node_num_) &&
        (pairs[i].second.node_num_ == pair.second.node_num_))
      return true;
  return false;
}

bool MaxBipartiteMatching::Contains(vector<Node> nodes, Node node) {
  // return find(nodes.begin(), nodes.end(), node) != nodes.end();
  for (size_t i = 0; i < nodes.size(); i++)
    if (node.node_num_ == nodes[i].node_num_) return true;
  return false;
}

bool MaxBipartiteMatching::IsAdjacent(int first_node_val, int second_node_val,
                                      int** adj_mat) {
  return (adj_mat[first_node_val - 1][second_node_val - 1] == 1);
}

void MaxBipartiteMatching::ParseLine(vector<Node>* V, string line) {
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
      // true at the beginning
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
  ifstream in_file(file_name);
  string line;
  getline(in_file, line);
  ParseLine(&V, line);

  getline(in_file, line);
  ParseLine(&U, line);

  size_ = V.size() + U.size();

  adj_mat = new int*[size_];

  for (int i = 0; i < size_; i++) adj_mat[i] = new int[size_];

  int count = 0;
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      in_file >> adj_mat[i][j];
      count++;
    }
  }
}

void MaxBipartiteMatching::MaxBipartiteMatch(string file_name) {
  // populates graph adjacency matrix, V, and U
  ReadInput(file_name);

  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      cout << adj_mat[i][j] << " ";
    }
    cout << endl;
  }

  // Q will contain 1, 2 ,3, 4, 5 or whatever else is in V
  ReinitializeQueue();

  while (!Q.empty()) {
    Node w = Q.front();  // w ← Front(Q)
    Q.pop();             // Dequeue(Q)

    // if w in V
    if (Contains(V, w)) {
      // for every vertex u adjacent to w do
      // iterate through all vertices then inside that add an if statement
      // checking adjacency using the adj_mat. How to iterate over vertices?
      for (int i = 0; i < size_; i++) {
        if (IsAdjacent(w.node_num_, i + 1, adj_mat)) {
          // node specified by u is adjacent to w
          Node u = GetNodeByValue(i + 1);
          if (u.is_free_) {
            // augment
            Add({w, u});
            Node v = w;
            // while v is labeled
            while (v.label != 0) {
              // u ← vertex indicated by v’s label; M ← M − (v, u)
              u = GetNodeByValue(v.label);
              Remove({v, u});

              // v ← vertex indicated by u’s label; M ← M ∪ (v, u)
              v = GetNodeByValue(u.label);
              Add({v, u});
            }
            // remove all vertex labels (make them zero)
            RemoveLabels();

            // update all vertices freedom
            UpdateFreedoms();

            // reinitialize Q with all free vertices in V
            ReinitializeQueue();

            break;
          } else {
            // u is matched
            if (Contains(M, {w, u}) && (u.label == 0)) {
              u.label = w.node_num_;
              Q.push(u);
            }
          }
        }
      }
    } else {
      // w is in U (and matched)
      /**
       * label the mate v of w with w
       *Enqueue(Q, v)
       */
      Node v = LabelMate(w);  // Label w's mate v
      Q.push(v);
    }
  }

  // Print results, praying it works haha
  PrintResults();
}