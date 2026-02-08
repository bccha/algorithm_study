#include <algorithm>
#include <queue>
#include <vector>


using namespace std;

const int INF = 1e9;

struct Edge {
  int to, cap, flow, rev;
};

vector<vector<Edge>> adj;
vector<int> level, ptr;

void add_edge(int from, int to, int cap) {
  adj[from].push_back({to, cap, 0, (int)adj[to].size()});
  adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
}

// BFS: 레벨 그래프 생성
bool bfs(int s, int t) {
  fill(level.begin(), level.end(), -1);
  level[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (const auto &edge : adj[cur]) {
      if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
        level[edge.to] = level[cur] + 1;
        q.push(edge.to);
      }
    }
  }
  return level[t] != -1;
}

// DFS: 증가 경로 찾기
int dfs(int cur, int t, int pushed) {
  if (pushed == 0 || cur == t)
    return pushed;
  for (int &cid = ptr[cur]; cid < adj[cur].size(); cid++) {
    auto &edge = adj[cur][cid];
    if (level[cur] + 1 != level[edge.to] || edge.cap - edge.flow == 0)
      continue;
    int tr = dfs(edge.to, t, min(pushed, edge.cap - edge.flow));
    if (tr == 0)
      continue;
    edge.flow += tr;
    adj[edge.to][edge.rev].flow -= tr;
    return tr;
  }
  return 0;
}

// Dinic Algorithm
int dinic(int s, int t) {
  int flow = 0;
  while (bfs(s, t)) {
    fill(ptr.begin(), ptr.end(), 0);
    while (int pushed = dfs(s, t, INF)) {
      flow += pushed;
    }
  }
  return flow;
}

// 초기화: adj.assign(n + 1, vector<Edge>()); level.resize(n + 1); ptr.resize(n
// + 1);
