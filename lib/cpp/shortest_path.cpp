#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>


using namespace std;

const long long INF = 1e18; // long long 사용 권장

struct Edge {
  int to;
  long long weight;
};

// 다익스트라 (우선순위 큐)
// start에서 모든 정점까지의 최단 거리 반환
vector<long long> dijkstra(int start, int n, const vector<vector<Edge>> &adj) {
  vector<long long> dist(n + 1, INF);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>>
      pq;

  dist[start] = 0;
  pq.push({0, start});

  while (!pq.empty()) {
    auto [d, cur] = pq.top();
    pq.pop();

    if (d > dist[cur])
      continue;

    for (const auto &edge : adj[cur]) {
      if (dist[cur] + edge.weight < dist[edge.to]) {
        dist[edge.to] = dist[cur] + edge.weight;
        pq.push({dist[edge.to], edge.to});
      }
    }
  }
  return dist;
}

// 벨만-포드 (음수 가중치 허용, 음수 사이클 판별)
// 반환: {최단거리 벡터, 음수 사이클 여부}
struct EdgeBF {
  int u, v;
  long long w;
};
pair<vector<long long>, bool> bellmanFord(int start, int n, int m,
                                          const vector<EdgeBF> &edges) {
  vector<long long> dist(n + 1, INF);
  dist[start] = 0;

  // N-1번 완화
  for (int i = 0; i < n - 1; i++) {
    for (const auto &edge : edges) {
      if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
        dist[edge.v] = dist[edge.u] + edge.w;
      }
    }
  }

  // 음수 사이클 확인
  bool hasNegativeCycle = false;
  for (const auto &edge : edges) {
    if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
      hasNegativeCycle = true;
      break;
    }
  }

  return {dist, hasNegativeCycle};
}

// 플로이드-워셜 (모든 쌍 최단 거리)
// adj[i][j] 초기화: 연결되면 가중치, 아니면 INF, 자기 자신은 0
void floydWarshall(int n, vector<vector<long long>> &dist) {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
}
