# 최단 경로 (Shortest Path)

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**최단 거리/최소 비용** 경로" → 최단 경로 알고리즘
- "**단일 출발점** + 양수 가중치" → **Dijkstra**
- "**음수 간선** 있음" → **Bellman-Ford**
### 💡 플로이드-워셜 이해
- `dist[i][j]`를 갱신할 때 `k`를 거쳐가는지 확인
- **3중 for문 순서 중요!**: `k` (경유) → `i` (시작) → `j` (도착)
- "모든 정점 쌍" 사이 최단 거리 구할 때 유일한 해법 (N <= 500)

### 🎓 실전 팁
1. **INF 값**: 더했을 때 오버플로우 안 나게 `1e9` (int), `1e15` (long long) 정도 사용
2. **음수 사이클**: 벨만포드에서 N번째 완화 발생 시 존재
   - 플로이드는 `dist[i][i] < 0`이면 음수 사이클
3. **Dijkstra 구현**: `priority_queue` 기본은 Max Heap → `greater<>` 써서 Min Heap 만들기!
4. **경로 추적**: `parent[i]` 배열로 어디서 왔는지 저장

## 📌 알고리즘 비교
|----------|------------|-------------|------|
| BFS | O(V+E) | ❌ | 가중치 1 |
| 0-1 BFS | O(V+E) | ❌ | 가중치 0/1 |
| **Dijkstra** | O(ElogV) | ❌ | 단일 출발점 |
| **Bellman-Ford** | O(VE) | ✅ | 음수 사이클 판별 |
| **Floyd-Warshall** | O(V³) | ✅ | 모든 쌍 |

---

## 1️⃣ Dijkstra (다익스트라)
**양수 가중치** 그래프에서 단일 출발점 최단 경로.

```cpp
#include <queue>
using namespace std;

const int INF = 1e9;
vector<pair<int,int>> adj[MAX];  // {next, weight}
int dist[MAX];

void dijkstra(int start) {
    fill(dist, dist + MAX, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    
    dist[start] = 0;
    pq.push({0, start});  // {거리, 노드}
    
    while (!pq.empty()) {
        auto [d, cur] = pq.top();
        pq.pop();
        
        if (d > dist[cur]) continue;  // 이미 처리된 노드
        
        for (auto [next, w] : adj[cur]) {
            if (dist[cur] + w < dist[next]) {
                dist[next] = dist[cur] + w;
                pq.push({dist[next], next});
            }
        }
    }
}
```

---

## 2️⃣ Bellman-Ford (벨만-포드)
**음수 가중치** 허용, **음수 사이클** 판별 가능.

```cpp
struct Edge { int u, v, w; };
vector<Edge> edges;
int dist[MAX];

bool bellmanFord(int start, int n) {
    fill(dist, dist + MAX, INF);
    dist[start] = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (auto& [u, v, w] : edges) {
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // 음수 사이클 판별 (N번째에도 갱신되면 사이클)
    for (auto& [u, v, w] : edges) {
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            return true;  // 음수 사이클 존재
        }
    }
    return false;
}
```

---

## 3️⃣ Floyd-Warshall (플로이드-워셜)
**모든 쌍** 최단 경로.

```cpp
int dist[500][500];

void floyd(int n) {
    // 초기화: dist[i][j] = 직접 연결 가중치 (없으면 INF)
    
    for (int k = 0; k < n; k++) {           // 경유지
        for (int i = 0; i < n; i++) {       // 출발
            for (int j = 0; j < n; j++) {   // 도착
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}
```

---

## 🐍 Python
```python
import heapq
INF = float('inf')

def dijkstra(start):
    dist = [INF] * n
    dist[start] = 0
    pq = [(0, start)]
    
    while pq:
        d, cur = heapq.heappop(pq)
        if d > dist[cur]:
            continue
        for nxt, w in adj[cur]:
            if dist[cur] + w < dist[nxt]:
                dist[nxt] = dist[cur] + w
                heapq.heappush(pq, (dist[nxt], nxt))
    
    return dist
```

---

## 📖 외부 자료
- [Dijkstra - CP Algorithms](https://cp-algorithms.com/graph/dijkstra.html)
- [Bellman-Ford - CP Algorithms](https://cp-algorithms.com/graph/bellman_ford.html)
- [VisuAlgo - Shortest Path](https://visualgo.net/en/sssp)

## 📚 연습 문제
- [BOJ 1753 최단경로](https://www.acmicpc.net/problem/1753) ⭐⭐ Dijkstra 기본
- [BOJ 1916 최소비용 구하기](https://www.acmicpc.net/problem/1916) ⭐⭐
- [BOJ 11657 타임머신](https://www.acmicpc.net/problem/11657) ⭐⭐ Bellman-Ford
- [BOJ 11404 플로이드](https://www.acmicpc.net/problem/11404) ⭐⭐ Floyd-Warshall
- [BOJ 1504 특정한 최단 경로](https://www.acmicpc.net/problem/1504) ⭐⭐⭐
