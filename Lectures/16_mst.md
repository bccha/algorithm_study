# 최소 스패닝 트리 (MST)

## 📌 개념
**모든 정점을 연결**하면서 **간선 가중치 합 최소**인 트리.
- 정점 V개 → 간선 V-1개
- 사이클 없음

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**모든 정점을 연결**하는 **최소 비용**"
- "**네트워크 구축** 최소 비용" (도로, 통신망)
- "**섬 연결하기**" with 최소 비용
### 💡 트리 DP 예시: 트리의 독립집합(MIS)
`dp[node][include]`
- `dp[node][1]` (나 포함): 자식들은 모두 포함 X
  - `sum(dp[child][0]) + weight[node]`
- `dp[node][0]` (나 미포함): 자식은 포함되거나 안 되거나 (더 큰 쪽)
  - `sum(max(dp[child][0], dp[child][1]))`

### 🎓 실전 팁
1. **DFS 후위 순회**: 자식들의 결과를 먼저 계산하고 부모로 올라옴
2. **메모이제이션**: `visited` 배열 대신 `dp` 배열 값이 갱신되었는지 확인
3. **트리의 지름**: 가장 긴 경로 찾기 (특정 정점 x에서 가장 먼 y 찾고, y에서 가장 먼 z 찾기)
4. **배낭 문제(Knapsack) 응용**: 트리 위에서 배낭 문제 풀기 (Tree Knapsack)
### 💡 Kruskal 알고리즘 동작 (탐욕법)
1. 간선들을 가중치 오름차순 정렬
2. 가중치 작은 간선부터 선택
3. **만약 두 정점이 이미 연결되어 있다면? (Cycle)** → 스킵 (Union-Find 사용)
4. 연결 안 되어 있으면? → 선택하고 Union
5. 간선 V-1개 선택하면 종료

### 🎓 실전 팁
1. **Union-Find 필수**: Kruskal 구현 시 없으면 안됨
2. **Prim vs Kruskal**: 
   - 간선이 적으면(희소) → Kruskal (O(ElogE))
   - 간선이 많으면(밀집) → Prim (O(ElogV) or O(V^2))
3. **최대 스패닝 트리**: 간선 부호를 반대로 하거나 내림차순 정렬
4. **유일성**: 간선 가중치가 모두 다르면 MST는 유일함

## 1️⃣ Kruskal (크루스칼)
**간선 정렬 + Union-Find**
- 간선 가중치 오름차순 정렬
- 사이클 안 만들면 추가

```cpp
struct Edge {
    int u, v, w;
    bool operator<(const Edge& o) const { return w < o.w; }
};

int parent[MAX];
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void unite(int a, int b) { parent[find(a)] = find(b); }

long long kruskal(int n, vector<Edge>& edges) {
    for (int i = 0; i <= n; i++) parent[i] = i;
    sort(edges.begin(), edges.end());
    
    long long mstCost = 0;
    int edgeCount = 0;
    
    for (auto& [u, v, w] : edges) {
        if (find(u) != find(v)) {
            unite(u, v);
            mstCost += w;
            edgeCount++;
            if (edgeCount == n - 1) break;
        }
    }
    return mstCost;
}
```

> ⏱️ O(E log E)

---

>### 💡 LCA 동작 원리 (최소 공통 조상)
트리의 두 노드 u, v가 주어졌을 때:
1. **깊이 맞추기**: 더 깊은 노드를 올려서 깊이를 같게 만듦
2. **함께 올리기**: 두 노드가 다르면, 같아질 때까지 동시에 부모로 이동
3. 만난 지점이 LCA!
**(희소 배열 사용 시 O(logN)으로 점프 가능)**

### 🎓 실전 팁
1. **희소 배열(Sparse Table)**: `parent[node][k]` = node의 2^k번째 조상
2. **DFS로 깊이/부모 미리 계산**: 초기화 (`build`) 필수
3. **LCA로 거리 구하기**: `dist(u, v) = depth[u] + depth[v] - 2*depth[lca(u,v)]`
4. **트리 1개 아닐 수도**: 숲(Forest) 형태면 모든 루트에서 DFS 돌려야 함

## 2️⃣ Prim (프림)
**정점 기준 확장** (Dijkstra와 유사)

```cpp
#include <queue>
using namespace std;

vector<pair<int,int>> adj[MAX];  // {next, weight}
bool visited[MAX];

long long prim(int n, int start) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, start});  // {가중치, 노드}
    
    long long mstCost = 0;
    int cnt = 0;
    
    while (!pq.empty() && cnt < n) {
        auto [w, cur] = pq.top();
        pq.pop();
        
        if (visited[cur]) continue;
        visited[cur] = true;
        mstCost += w;
        cnt++;
        
        for (auto [next, weight] : adj[cur]) {
            if (!visited[next]) {
                pq.push({weight, next});
            }
        }
    }
    return mstCost;
}
```

> ⏱️ O(E log V)

---

## 🐍 Python (Kruskal)
```python
parent = list(range(n + 1))

def find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]

def kruskal(n, edges):
    edges.sort(key=lambda x: x[2])  # 가중치 기준
    mst_cost = 0
    
    for u, v, w in edges:
        if find(u) != find(v):
            parent[find(u)] = find(v)
            mst_cost += w
    
    return mst_cost
```

---

## 📖 외부 자료
- [MST - CP Algorithms](https://cp-algorithms.com/graph/mst_kruskal.html)
- [MST 시각화](https://visualgo.net/en/mst)

## 📚 연습 문제
- [BOJ 1197 최소 스패닝 트리](https://www.acmicpc.net/problem/1197) ⭐⭐ 기본
- [BOJ 1922 네트워크 연결](https://www.acmicpc.net/problem/1922) ⭐⭐
- [BOJ 1647 도시 분할 계획](https://www.acmicpc.net/problem/1647) ⭐⭐
- [BOJ 4386 별자리 만들기](https://www.acmicpc.net/problem/4386) ⭐⭐ 좌표계
- [BOJ 17472 다리 만들기 2](https://www.acmicpc.net/problem/17472) ⭐⭐⭐ BFS + MST
