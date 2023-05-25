#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

/*
 * Baseado em Sedgewick, Wayne; Algorithms, 4th Edition, Digraph.java:
 * https://algs4.cs.princeton.edu/42digraph/Digraph.java.html
 */
class DirectedGraph {
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
  DirectedGraph(int v) : v_(v), e_(0), adj_(v, std::vector<int>()) {}

  int v(void) { return v_; }
  int e(void) { return e_; }

  void addEdge(int v, int w) {
    validateVertex(v);
    validateVertex(w);
    e_++;
    adj_[v].push_back(w);
  }

  vector<int> adj(int v) {
    validateVertex(v);
    return adj_[v];
  }

  int outDegree(int v) {
    validateVertex(v);
    return adj_[v].size();
  }

  DirectedGraph *reverse(void) {
    DirectedGraph *g = new DirectedGraph(v_);

    for (int i = 0; i < v_; i++) {
      for (auto j : adj(i)) {
        g->addEdge(j, i);
      }
    }

    return g;
  }
};
