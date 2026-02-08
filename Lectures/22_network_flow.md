# 네트워크 플로우 & 이분 매칭

## 📌 개념
- **최대 유량**: 소스 → 싱크로 보낼 수 있는 최대 유량
- **이분 매칭**: 두 그룹을 1:1 매칭하는 최대 쌍 수

---

## 1️⃣ Ford-Fulkerson (DFS 기반)
```cpp
int capacity[MAX][MAX], flow[MAX][MAX];
bool visited[MAX];

int dfs(int cur, int sink, int f) {
    if (cur == sink) return f;
    visited[cur] = true;
    
    for (int next = 0; next < MAX; next++) {
        if (!visited[next] && capacity[cur][next] - flow[cur][next] > 0) {
            int d = dfs(next, sink, min(f, capacity[cur][next] - flow[cur][next]));
            if (d > 0) {
                flow[cur][next] += d;
                flow[next][cur] -= d;  // 역방향
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int source, int sink) {
    int total = 0;
    while (true) {
        memset(visited, false, sizeof(visited));
        int f = dfs(source, sink, INF);
        if (f == 0) break;
        total += f;
    }
    return total;
}
```

---

## 2️⃣ 이분 매칭 (Bipartite Matching)
```cpp
vector<int> adj[MAX];
int match[MAX];  // match[B그룹] = 매칭된 A그룹 원소
bool visited[MAX];

bool dfs(int cur) {
    for (int next : adj[cur]) {
        if (visited[next]) continue;
        visited[next] = true;
        
        // next가 미매칭 OR next를 다른 것과 매칭 가능
        if (match[next] == -1 || dfs(match[next])) {
            match[next] = cur;
            return true;
        }
    }
    return false;
}

int bipartiteMatching(int n) {
    memset(match, -1, sizeof(match));
    int cnt = 0;
    
    for (int i = 1; i <= n; i++) {
        memset(visited, false, sizeof(visited));
        if (dfs(i)) cnt++;
    }
    return cnt;
}
```

---

## 📚 연습 문제
- [BOJ 6086 최대 유량](https://www.acmicpc.net/problem/6086) ⭐⭐⭐⭐
- [BOJ 2188 축사 배정](https://www.acmicpc.net/problem/2188) ⭐⭐⭐ 이분 매칭
- [BOJ 11375 열혈강호](https://www.acmicpc.net/problem/11375) ⭐⭐⭐
- [BOJ 11376 열혈강호 2](https://www.acmicpc.net/problem/11376) ⭐⭐⭐⭐
