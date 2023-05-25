#include <iostream>
#include <stack>
#include <stdexcept>
#include <vector>

using namespace std;

const vector<int> dx = {1, 0, -1, 0};
const vector<int> dy = {0, 1, 0, -1};
int forca;

void dfs(vector<vector<int>> &m, int x, int y) {
  if (m[x][y] > forca || m[x][y] < 0)
    return;
  m[x][y] = -1;
  int n = m.size();

  for (int i = 0; i < 4; i++) {
    if (x < n - 1)
      dfs(m, x + 1, y);

    if (y < n - 1)
      dfs(m, x, y + 1);

    if (x > 0)
      dfs(m, x - 1, y);

    if (y > 0)
      dfs(m, x, y - 1);
  }
}

int main(void) {
  int n, m;
  cin >> n >> m;
  forca = m;

  vector<vector<int>> map(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    vector<int> row;
    string in;
    cin >> in;
    for (int j = 0; j < in.size(); j++) {
      int val = in[j] - '0';
      map[i][j] = val;
    }
  }
  if (map[0][0] <= forca) {
    dfs(map, 0, 0);
  }

  for (auto i : map) {
    for (auto j : i) {
      if (j == -1) {
        cout << "*";
      } else {
        cout << j;
      }
    }
    cout << endl;
  }

  return 0;
}
