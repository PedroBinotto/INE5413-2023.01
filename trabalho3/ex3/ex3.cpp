#include <algorithm>
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
  vector<vector<int>> adj_;

  void validateVertex(int v) {
    if (v < 0 || v >= v_) {
      throw invalid_argument("vertex " + to_string(v) + " is not between 0 and " + to_string(v_));
    }
  }

public:
  WeightedGraph(int v) : v_(v), e_(0), adj_(v, vector<int>(v_)) {}

  int v(void) { return v_; }
  int e(void) { return e_; }

  void addEdge(int i, int j, int w) {
    validateVertex(i);
    validateVertex(j);

    adj_[i][j] = w;
    adj_[j][i] = w;

    e_++;
  }

  vector<pair<int, int>> adj(int v) {
    validateVertex(v);
    vector<pair<int, int>> adjs;
    for (int i = 0; i < v_; i++) {
      if (adj_[v][i] != 0) {
        adjs.push_back({adj_[v][i], i});
      }
    }
    return adjs;
  }

  int degree(int v) {
    validateVertex(v);
    return adj(v).size();
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
      if (!mk[e.second])
        q.push({e.first, {_s, e.second}});
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
  int n, m, o;
  cin >> n >> m >> o;

  WeightedGraph *g = new WeightedGraph(n);

  vector<WeightedEdge> ferrovias;
  vector<WeightedEdge> rodovias;

  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;

    ferrovias.push_back({w, {a - 1, b - 1}});
  }

  for (int i = 0; i < o; i++) {
    int a, b, w;
    cin >> a >> b >> w;

    rodovias.push_back({w, {a - 1, b - 1}});
  }

  for (auto e : rodovias)
    g->addEdge(e.second.first, e.second.second, e.first);

  for (auto e : ferrovias)
    g->addEdge(e.second.first, e.second.second, e.first);

  vector<bool> mk(g->v());
  const auto cmp = [](WeightedEdge u, WeightedEdge v) { return u.first > v.first; };
  priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>> q(cmp);

  auto mst = prim(g, mk, q, 0);
  int cnt = 0;

  for (auto e : mst) {
    cnt += e.first;
  }

  cout << cnt << endl;

  return 0;
}
