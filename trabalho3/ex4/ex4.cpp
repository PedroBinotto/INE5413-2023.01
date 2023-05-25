#include <algorithm>
#include <iomanip>
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

vector<int> bfs(DirectedGraph *g, int s) {
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
        mk[w] = true;
        q.push(w);
      }
    }
  }

  return distTo;
}

int main(void) {
  int n, m;
  cin >> n >> m;

  vector<int> pais;
  set<int> presentes;

  for (int i = 0; i < n; i++) {
    int j;
    cin >> j;
    pais.push_back(j);
  }

  for (int i = 0; i < m; i++) {
    int j;
    cin >> j;
    presentes.insert(j);
  }

  DirectedGraph *g = new DirectedGraph(n + 1);

  for (int i = 0; i < n; i++)
    g->addEdge(pais[i], i + 1);

  auto distTo = bfs(g, 0);

  map<int, set<int>> generations;

  for (int i = 1; i < distTo.size(); i++)
    generations[distTo[i]].insert(i);

  cout << fixed;
  cout << setprecision(2);

  for (auto it = generations.begin(); it != generations.end(); it++) {
    set<int> intersect;
    set_intersection(it->second.begin(), it->second.end(), presentes.begin(), presentes.end(),
                     inserter(intersect, intersect.begin()));
    float percentage = (((float)intersect.size() / (float)it->second.size()) * 100);
    cout << percentage << " ";
  }
  cout << endl;

  return 0;
}
