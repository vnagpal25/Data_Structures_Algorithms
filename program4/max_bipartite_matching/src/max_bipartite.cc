/**
 * Copyright 2023 - CSCE350
 * Main Entry point for the Maximum Bipartite Matching Algorithm
 * @author vnagpal
 */
#include "max_bipartite_matching/inc/functions.h"  // class header
int main(int argc, char** argv) {
  // Runs algorithm
  MaxBipartiteMatching max_bipartite_matching;
  max_bipartite_matching.MaxBipartiteMatch("input.txt");
  return 0;
}
