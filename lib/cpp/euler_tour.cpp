#include <iostream>
#include <vector>


using namespace std;

const int MAX = 100005;
vector<int> adj[MAX];
int in_time[MAX], out_time[MAX];
int timer;

void dfs_euler(int cur, int p) {
  in_time[cur] = ++timer;
  for (int next : adj[cur]) {
    if (next != p) {
      dfs_euler(next, cur);
    }
  }
  out_time[cur] = timer;
}

// 쿼리: u가 v의 조상인가? (in[u] <= in[v] && out[v] <= out[u])
bool is_ancestor(int u, int v) {
  return in_time[u] <= in_time[v] && out_time[v] <= out_time[u];
}

// 서브트리 쿼리: [in[u], out[u]] 구간 쿼리로 변환
