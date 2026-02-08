# SCC & 2-SAT

## 📌 SCC (Strongly Connected Component)
**강한 연결 요소**: 방향 그래프에서 모든 정점 쌍이 서로 도달 가능한 최대 부분 그래프.

---

## 💻 Kosaraju's Algorithm
```cpp
vector<int> adj[MAX], radj[MAX];  // 정방향, 역방향
bool visited[MAX];
stack<int> stk;
int scc_id[MAX];

void dfs1(int cur) {
    visited[cur] = true;
    for (int next : adj[cur])
        if (!visited[next]) dfs1(next);
    stk.push(cur);
}

void dfs2(int cur, int id) {
    scc_id[cur] = id;
    for (int next : radj[cur])
        if (scc_id[next] == 0) dfs2(next, id);
}

int findSCC(int n) {
    // 1단계: 종료 순서대로 스택에
    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs1(i);
    
    // 2단계: 역방향 그래프에서 DFS
    int scc_count = 0;
    while (!stk.empty()) {
        int cur = stk.top(); stk.pop();
        if (scc_id[cur] == 0)
            dfs2(cur, ++scc_count);
    }
    return scc_count;
}
```

---

## 📌 2-SAT
**불리언 변수**들의 AND/OR 조건을 만족하는 할당 찾기.
- (A OR B) = (¬A → B) AND (¬B → A)

```cpp
// 변수 x: 정점 2x (x=true), 2x+1 (x=false)
void addClause(int i, bool pi, int j, bool pj) {
    // (i=pi OR j=pj)
    // ¬pi → pj, ¬pj → pi
    adj[2*i + !pi].push_back(2*j + pj);
    adj[2*j + !pj].push_back(2*i + pi);
}

bool solve2SAT(int n) {
    int scc_count = findSCC(2*n);  // 변수 n개 → 정점 2n개
    
    for (int i = 0; i < n; i++) {
        if (scc_id[2*i] == scc_id[2*i+1])
            return false;  // x와 ¬x가 같은 SCC → 불가능
    }
    return true;
}
```

---

## 📚 연습 문제
- [BOJ 2150 Strongly Connected Component](https://www.acmicpc.net/problem/2150) ⭐⭐⭐⭐
- [BOJ 4196 도미노](https://www.acmicpc.net/problem/4196) ⭐⭐⭐
- [BOJ 11280 2-SAT - 3](https://www.acmicpc.net/problem/11280) ⭐⭐⭐⭐
- [BOJ 11281 2-SAT - 4](https://www.acmicpc.net/problem/11281) ⭐⭐⭐⭐⭐
