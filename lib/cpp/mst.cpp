#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>


using namespace std;

// Union-Find 구조체 필요 (여기서는 간단히 포함)
struct DSU {
  vector<int> parent;
  DSU(int n) {
    parent.resize(n + 1);
    for (int i = 0; i <= n; ++i)
      parent[i] = i;
  }
  int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return false;
    parent[b] = a;
    return true;
  }
};

struct Edge {
  int u, v;
  long long weight;
  bool operator<(const Edge &other) const { return weight < other.weight; }
};

// Kruskal 알고리즘
// 반환: {MST 가중치 합, 간선 수}
pair<long long, int> kruskal(int n, vector<Edge> &edges) {
  sort(edges.begin(), edges.end());
  DSU dsu(n);
  long long sum = 0;
  int count = 0;

  for (const auto &edge : edges) {
    if (dsu.unite(edge.u, edge.v)) {
      sum += edge.weight;
      count++;
    }
  }
  return {sum, count};
}

// Prim 알고리즘
const long long INF = 1e18;
long long prim(int n, int start,
               const vector<vector<pair<int, long long>>> &adj) {
  long long sum = 0;
  vector<bool> visited(n + 1, false);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>>
      pq;

  pq.push({0, start});
  int count = 0;

  while (!pq.empty()) {
    auto [w, cur] = pq.top();
    pq.pop();

    if (visited[cur])
      continue;
    visited[cur] = true;
    sum += w;
    count++;

    for (auto &[next, weight] : adj[cur]) {
      if (!visited[next]) {
        pq.push({weight, next});
      }
    }
  }

  if (count < n)
    return -1; // 연결 그래프 아님
  return sum;
}
