#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>


using namespace std;

const int MAX = 100005;
vector<int> adj[MAX];
bool visited[MAX];

// DFS (재귀)
void dfs(int cur) {
  visited[cur] = true;
  cout << cur << " ";
  for (int next : adj[cur]) {
    if (!visited[next]) {
      dfs(next);
    }
  }
}

// BFS (큐)
void bfs(int start) {
  queue<int> q;
  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    cout << cur << " ";

    for (int next : adj[cur]) {
      if (!visited[next]) {
        visited[next] = true;
        q.push(next);
      }
    }
  }
}

// 위상 정렬 (Kahn's Algorithm)
vector<int> topologicalSort(int n, vector<int> &indegree) {
  queue<int> q;
  vector<int> result;

  for (int i = 1; i <= n; i++) {
    if (indegree[i] == 0)
      q.push(i);
  }

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    result.push_back(cur);

    for (int next : adj[cur]) {
      indegree[next]--;
      if (indegree[next] == 0)
        q.push(next);
    }
  }

  if (result.size() != n)
    return {}; // 사이클 존재
  return result;
}
