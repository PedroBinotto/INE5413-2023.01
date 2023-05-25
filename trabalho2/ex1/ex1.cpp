#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

/*
 * Baseado em Sedgewick, Wayne; Algorithms, 4th Edition, Graph.java:
 * https://algs4.cs.princeton.edu/41graph/Graph.java.html
 */
class Graph { //
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
  Graph(int v) : v_(v), e_(0), adj_(v, std::vector<int>(v)) {}

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
    return adj_.size();
  }
};

void dfs(Graph *g, int s, vector<bool> &m) {
  m[s] = true;
  for (auto i : (g->adj(s))) {
    if (!m[i]) {
      dfs(g, i, m);
    }
  }
}

int countConnectedComponents(Graph *g) {
  vector<bool> m(g->v());
  vector<int> id(g->v());
  int c = 0;
  for (int v = 0; v < g->v(); v++) {
    if (!m[v]) {
      dfs(g, v, m);
      c++;
    }
  }

  return c;
}

int main(void) {
  int i = 1;
  while (true) {
    int v, e;
    cin >> v >> e;
    if (v == 0 && e == 0)
      break;

    Graph *g = new Graph(v);
    for (int i = 0; i < e; i++) {
      int u, v;
      cin >> u >> v;
      u--;
      v--; // facilitar a indexacao base-0
      g->addEdge(u, v);
    }

    int componentCount = countConnectedComponents(g);
    string message = componentCount == 1 ? "normal" : "falha";

    std::cout << "Teste " << i << std::endl;
    std::cout << message << std::endl;
    cout << endl;

    delete g;
    i++;
  }

  return 0;
}
