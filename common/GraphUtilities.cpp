#include <functional>
#include <queue>
#include <vector>

#include "DirectedGraph.hpp"
#include "Graph.hpp"
#include "WeightedGraph.hpp"

namespace GraphUtilities {
void dfs(Graph *g, int s, vector<bool> &m) {
  m[s] = true;
  for (auto i : (*g->adj(s))) {
    if (!m[i]) {
      dfs(g, i, m);
    }
  }
}

void dfs(WeightedGraph *g, int s, vector<bool> &m) {
  m[s] = true;
  for (auto i : (g->adj(s))) {
    auto other = i.second.second;
    if (!m[other]) {
      dfs(g, other, m);
    }
  }
}

void dfs(DirectedGraph *g, int s, vector<bool> &m) {} // TODO

vector<WeightedEdge>
prim(WeightedGraph *g,
     vector<bool> &mk,
     priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>> *q,
     int s) {

  const auto scan = [&mk, &q](WeightedGraph *_g, int _s) {
    mk[_s].flip();
    for (auto e : _g->adj(_s))
      if (!mk[e.second.second])
        q->push(e);
  };

  vector<WeightedEdge> edges;
  scan(g, s);
  while (!q->empty()) {
    auto e = q->top();
    q->pop();
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

WeightedGraph *getPrimMST(WeightedGraph *g) {
  auto *mst = new WeightedGraph(g->v());
  vector<bool> mk(g->v());
  const auto cmp = [](WeightedEdge u, WeightedEdge v) { return u.first > v.first; };
  priority_queue<WeightedEdge, vector<WeightedEdge>, function<bool(WeightedEdge, WeightedEdge)>> q(cmp);

  vector<WeightedEdge> edges;

  for (int i = 0; i < g->v(); i++) {
    if (!mk[i]) {
      vector<WeightedEdge> p = prim(g, mk, &q, i); // rodar em todos os v para gerar floresta
      edges.insert(edges.end(), p.begin(), p.end());
    }
  }

  for (auto i : edges)
    mst->addEdge(i.second.first, i.second.second, i.first);

  return mst;
}
} // namespace GraphUtilities
