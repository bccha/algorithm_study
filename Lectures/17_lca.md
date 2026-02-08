# LCA (최소 공통 조상)

## 📌 개념
트리에서 두 노드의 **가장 가까운 공통 조상**을 찾는 알고리즘.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "두 정점의 **공통 조상** 찾기"
- "트리에서 두 정점 사이 **거리** 계산"
- "경로 상의 정점/간선 쿼리"
- "트리 경로 문제" (거리, 가중치 합 등)

---

## 1️⃣ 기본 LCA - O(N)
```cpp
int parent[MAX], depth[MAX];

void dfs(int cur, int par, int d) {
    parent[cur] = par;
    depth[cur] = d;
    for (int next : adj[cur]) {
        if (next != par) dfs(next, cur, d + 1);
    }
}

int lca(int a, int b) {
    // 깊이 맞추기
    while (depth[a] > depth[b]) a = parent[a];
    while (depth[b] > depth[a]) b = parent[b];
    
    // 동시에 올라가기
    while (a != b) {
        a = parent[a];
        b = parent[b];
    }
    return a;
}
```

---

## 2️⃣ 희소 배열 LCA - O(logN)
```cpp
const int LOG = 20;  // log2(MAX)
int parent[MAX][LOG];  // parent[i][j] = i의 2^j번째 조상
int depth[MAX];

void dfs(int cur, int par, int d) {
    parent[cur][0] = par;
    depth[cur] = d;
    for (int next : adj[cur]) {
        if (next != par) dfs(next, cur, d + 1);
    }
}

void buildSparseTable(int n) {
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (parent[i][j-1] != -1) {
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    
    // 깊이 맞추기 (2^k씩 점프)
    int diff = depth[a] - depth[b];
    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            a = parent[a][j];
        }
    }
    
    if (a == b) return a;
    
    // 동시에 올라가기
    for (int j = LOG - 1; j >= 0; j--) {
        if (parent[a][j] != parent[b][j]) {
            a = parent[a][j];
            b = parent[b][j];
        }
    }
    return parent[a][0];
}
```

---

## 🎯 응용: 두 정점 사이 거리
```cpp
int dist[MAX];  // 루트로부터의 거리

// 미리 계산
void dfs(int cur, int par, int d) {
    depth[cur] = d;
    for (auto [next, w] : adj[cur]) {
        if (next != par) {
            dist[next] = dist[cur] + w;
            dfs(next, cur, d + 1);
        }
    }
}

int distance(int a, int b) {
    return dist[a] + dist[b] - 2 * dist[lca(a, b)];
}
```

---

## 📖 외부 자료
- [LCA - CP Algorithms](https://cp-algorithms.com/graph/lca.html)
- [Binary Lifting 설명](https://blog.encrypted.gg/1164)

## 📚 연습 문제
- [BOJ 11437 LCA](https://www.acmicpc.net/problem/11437) ⭐⭐ 기본
- [BOJ 11438 LCA 2](https://www.acmicpc.net/problem/11438) ⭐⭐⭐ 희소 배열
- [BOJ 1761 정점들의 거리](https://www.acmicpc.net/problem/1761) ⭐⭐⭐
- [BOJ 3176 도로 네트워크](https://www.acmicpc.net/problem/3176) ⭐⭐⭐⭐
