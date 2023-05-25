#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

typedef pair<int, pair<int, int>> WeightedEdge;

/*
 * Baseado em Sedgewick, Wayne; Algorithms, 4th Edition, EdgeWeightedGraph.java:
 * https://algs4.cs.princeton.edu/43mst/EdgeWeightedGraph.java.html
 */
class WeightedGraph {
private:
  const int v_;
  int e_;
  vector<vector<WeightedEdge>> adj_;

  void validateVertex(int v) {
    if (v < 0 || v >= v_) {
      throw invalid_argument("vertex " + to_string(v) + " is not between 0 and " + to_string(v_));
    }
  }

public:
  WeightedGraph(int v) : v_(v), e_(0), adj_(v, vector<WeightedEdge>()) {}

  int v(void) { return v_; }
  int e(void) { return e_; }

  void addEdge(int i, int j, int w) {
    validateVertex(i);
    validateVertex(j);

    adj_[i].push_back({w, {i, j}});
    adj_[j].push_back({w, {j, i}});

    e_++;
  }

  vector<WeightedEdge> adj(int v) {
    validateVertex(v);
    return adj_[v];
  }

  int degree(int v) {
    validateVertex(v);
    return adj_[v].size();
  }
};
