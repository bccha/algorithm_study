#include <algorithm>
#include <cmath>
#include <vector>


using namespace std;

// LCA (Lowest Common Ancestor) - Sparse Table (Binary Lifting)
const int MAX = 100005;
const int LOG = 20; // 2^20 > 100000

vector<int> adj[MAX];
int parent[MAX][LOG];
int depth[MAX];

void dfs(int cur, int p, int d) {
  depth[cur] = d;
  parent[cur][0] = p;
  for (int next : adj[cur]) {
    if (next != p) {
      dfs(next, cur, d + 1);
    }
  }
}

void build_lca(int n, int root) {
  dfs(root, 0, 0); // root의 부모는 0

  for (int j = 1; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
      if (parent[i][j - 1] != 0)
        parent[i][j] = parent[parent[i][j - 1]][j - 1];
    }
  }
}

int lca(int u, int v) {
  if (depth[u] < depth[v])
    swap(u, v);

  // 깊이 맞추기
  for (int j = LOG - 1; j >= 0; j--) {
    if (depth[u] - (1 << j) >= depth[v]) {
      u = parent[u][j];
    }
  }

  if (u == v)
    return u;

  // 공통 조상 찾기
  for (int j = LOG - 1; j >= 0; j--) {
    if (parent[u][j] != parent[v][j]) {
      u = parent[u][j];
      v = parent[v][j];
    }
  }

  return parent[u][0];
}

int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
