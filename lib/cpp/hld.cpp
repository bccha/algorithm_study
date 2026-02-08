#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

// Heavy-Light Decomposition
const int MAX = 100005;
vector<int> adj[MAX];
int parent[MAX], depth[MAX], heavy[MAX], head[MAX], pos[MAX];
int cur_pos;

// 1. DFS to find heavy edges and subtree sizes
int dfs(int v) {
  int size = 1;
  int max_c_size = 0;
  for (int c : adj[v]) {
    if (c != parent[v]) {
      parent[c] = v;
      depth[c] = depth[v] + 1;
      int c_size = dfs(c);
      size += c_size;
      if (c_size > max_c_size) {
        max_c_size = c_size;
        heavy[v] = c;
      }
    }
  }
  return size;
}

// 2. Decompose chains
void decompose(int v, int h) {
  head[v] = h;
  pos[v] = cur_pos++;
  if (heavy[v] != -1)
    decompose(heavy[v], h);
  for (int c : adj[v]) {
    if (c != parent[v] && c != heavy[v])
      decompose(c, c);
  }
}

// 초기화
void init_hld(int root) {
  fill(heavy, heavy + MAX, -1);
  parent[root] = -1;
  depth[root] = 0;
  cur_pos = 0;
  dfs(root);
  decompose(root, root);
}

// 경로 쿼리 예시 (Segment Tree 필요)
// int query(int a, int b) {
//     int res = 0;
//     for (; head[a] != head[b]; b = parent[head[b]]) {
//         if (depth[head[a]] > depth[head[b]]) swap(a, b);
//         // res += seg.query(pos[head[b]], pos[b]);
//     }
//     if (depth[a] > depth[b]) swap(a, b);
//     // res += seg.query(pos[a], pos[b]);
//     return res;
// }
