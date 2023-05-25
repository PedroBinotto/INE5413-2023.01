#include <iostream>
#include <map>
#include <queue>
#include <set>
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

int distTo(DirectedGraph *g, int s, int d) {
  queue<int> q;
  vector<bool> mk(g->v());
  vector<int> distTo(g->v());

  mk[s] = true;
  distTo[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int w : g->adj(v)) {
      if (!mk[w]) {
        distTo[w] = distTo[v] + 1;
        if (w == d) {
          return distTo[w];
        }
        mk[w] = true;
        q.push(w);
      }
    }
  }

  return -1;
}

int main(void) {
  int n;
  cin >> n;

  map<string, int> index;
  vector<pair<int, int>> edges;
  set<string> elements;

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    string p, q;
    cin >> p >> q;
    elements.insert(p);
    elements.insert(q);
    if (index.find(p) == index.end()) {
      index[p] = cnt;
      cnt++;
    }
    if (index.find(q) == index.end()) {
      index[q] = cnt;
      cnt++;
    }
    pair<int, int> e = {index[p], index[q]};
    edges.push_back(e);
  }

  DirectedGraph *g = new DirectedGraph(elements.size());

  for (auto e : edges)
    g->addEdge(e.first, e.second);

  int prev;
  for (auto it = index.begin(); it != index.end(); it++) {
    if (prev) {
      g->addEdge(prev, it->second);
      g->addEdge(it->second, prev);
    }
    prev = it->second;
  }

  string origin, dest;
  cin >> origin >> dest;

  int dist = distTo(g, index[origin], index[dest]);
  cout << to_string(dist) << endl;

  delete g;
  return 0;
}
