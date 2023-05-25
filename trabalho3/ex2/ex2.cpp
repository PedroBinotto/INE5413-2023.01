/*
 * É a (quase) mesma solução que o ex.1 ...?
 */

#include <functional>
#include <iostream>
#include <queue>
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
vector<WeightedEdge>
prim(WeightedGraph *g,
     vector<bool> &mk,
     priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>> &q,
     int s) {

  const auto scan = [&mk, &q](WeightedGraph *_g, int _s) {
    mk[_s].flip();
    for (auto e : _g->adj(_s))
      if (!mk[e.second.second])
        q.push(e);
  };

  vector<WeightedEdge> edges;
  scan(g, s);
  while (!q.empty()) {
    auto e = q.top();
    q.pop();
    int u, v;
    u = e.second.first;
    v = e.second.second;
    if (mk[u] && mk[v])
      continue;
    edges.push_back(e);
    if (!mk[u])
      scan(g, u);
    if (!mk[v])
      scan(g, v);
  }

  return edges;
}

int main(void) {
  int n, m;
  cin >> n >> m;

  auto *g = new WeightedGraph(n);
  for (int i = 0; i < m; i++) {
    int p, q, u;
    cin >> p >> q >> u;
    g->addEdge((p - 1), (q - 1), u);
  }

  vector<bool> mk(g->v());
  const auto cmp = [](WeightedEdge u, WeightedEdge v) { return u.first > v.first; };
  priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>> q(cmp);

  vector<WeightedEdge> edges;

  for (int i = 0; i < g->v(); i++) {
    if (!mk[i]) {
      vector<WeightedEdge> p = prim(g, mk, q, i); // rodar em todos os v para gerar floresta
      edges.insert(edges.end(), p.begin(), p.end());
    }
  }

  int cost = 0;

  for (auto i : edges)
    cost += i.first;

  cout << to_string(cost);
  delete g;

  return 0;
}
