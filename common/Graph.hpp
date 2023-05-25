#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

/*
 * Baseado em Sedgewick, Wayne; Algorithms, 4th Edition, Graph.java:
 * https://algs4.cs.princeton.edu/41graph/Graph.java.html
 */
class Graph {
private:
  const int v_;
  int e_;
  vector<vector<int>> adj_;

  void validateVertex(int v) {
    if (v < 0 || v >= v_) {
      throw invalid_argument("vertex " + to_string(v) + " is not between 0 and " + to_string(v_));
    }
  }

public:
  Graph(int v) : v_(v), e_(0), adj_(v, std::vector<int>()) {}

  int v(void) { return v_; }
  int e(void) { return e_; }

  void addEdge(int v, int w) {
    validateVertex(v);
    validateVertex(w);
    e_++;
    adj_[v].push_back(w);
    adj_[w].push_back(v);
  }

  vector<int> adj(int v) {
    validateVertex(v);
    return adj_[v];
  }

  int degree(int v) {
    validateVertex(v);
    return adj_[v].size();
  }
};
