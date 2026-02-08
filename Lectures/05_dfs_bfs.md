# DFS & BFS (깊이/너비 우선 탐색)

## 📌 개념
- **DFS (Depth-First Search)**: 깊이 우선 - 스택/재귀 사용
- **BFS (Breadth-First Search)**: 너비 우선 - 큐 사용

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "그래프/트리 **탐색**" → DFS 또는 BFS
- "**최단 거리**/최소 이동" (가중치 동일) → **BFS 필수!**
- "**모든 경로** 탐색" → DFS
- "**연결 요소** 개수" → DFS/BFS 모두 OK
- "미로 탐색" → BFS (최단거리)
- "섬의 개수" → DFS/BFS
- "위상 정렬" → DFS 또는 BFS Kahn

## ⏱️ 시간복잡도
- 인접 리스트: O(V + E) ← **대부분의 경우 사용**
- 인접 행렬: O(V²)

### 🔍 그래프 표현 선택 기준
| 상황 | 추천 |
|------|------|
| E가 작음 (희소 그래프) | **인접 리스트** |
| E가 큼 (밀집 그래프) | 인접 행렬 |
| "u와 v가 연결?" 쿼리 많음 | 인접 행렬 (O(1)) |
| 메모리 제한 | 인접 리스트 |

## 💻 그래프 표현
```cpp
// 인접 리스트 (권장)
vector<int> adj[MAX];
adj[u].push_back(v);
adj[v].push_back(u);  // 무방향 그래프

// 인접 행렬
int graph[MAX][MAX];
graph[u][v] = graph[v][u] = 1;
```

## 💻 DFS (재귀)
```cpp
bool visited[MAX];

void dfs(int node) {
    visited[node] = true;
    // node 처리
    
    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
}
```

## 💻 BFS (큐)
```cpp
void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        for (int next : adj[cur]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}
```

## 💻 2D 그리드 탐색
```cpp
int dx[] = {-1, 1, 0, 0};  // 상하좌우
int dy[] = {0, 0, -1, 1};

void bfs_grid(int sx, int sy) {
    queue<pair<int,int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (visited[nx][ny]) continue;
            if (grid[nx][ny] == '#') continue;  // 벽
            
            visited[nx][ny] = true;
            q.push({nx, ny});
        }
    }
}
```

## 🐍 Python
```python
from collections import deque

def bfs(start):
    q = deque([start])
    visited[start] = True
    
    while q:
        cur = q.popleft()
        for nxt in adj[cur]:
            if not visited[nxt]:
                visited[nxt] = True
                q.append(nxt)

def dfs(node):
    visited[node] = True
    for nxt in adj[node]:
        if not visited[nxt]:
            dfs(node)
```

## 🎯 언제 DFS? 언제 BFS?
| 상황 | 추천 |
|------|------|
| **최단 거리** (가중치 동일) | BFS ✅ |
| 모든 경로 탐색 | DFS |
| 연결 요소 개수 | 둘 다 OK |
| 사이클 판별 | DFS |
| 위상 정렬 | DFS (또는 BFS Kahn) |

---

## 💡 구체적 예시: 미로 탈출
```
미로 (S=시작, E=끝, #=벽):
S . . #
# . # .
. . . E
```

**BFS 동작:**
```
1. queue에 S(0,0) 삽입, 거리 = 0
2. S에서 (0,1)로 이동, 거리 = 1
3. (0,1)에서 (1,1), (0,2)로 이동, 거리 = 2
4. ...
5. E(2,3)에 도착, 거리 = 5
```
→ **BFS는 가중치가 모두 1일 때 최단거리 보장!**

### 🎓 실전 팁
1. **BFS 최단거리**: `dist[next] = dist[cur] + 1` 패턴
2. **DFS 스택 오버플로우**: 깊이 깊으면 `sys.setrecursionlimit()` (Python)
3. **visited 배열**: 꼭 필요! 안 쓰면 무한 루프
4. **2D 그리드**: dx, dy 배열로 4방향/8방향 탐색
5. **디버깅**: 탐색 순서 출력해서 확인

---

## 📖 외부 자료
- [Graph Traversal - VisuAlgo](https://visualgo.net/en/dfsbfs)
- [DFS/BFS - CP Algorithms](https://cp-algorithms.com/graph/depth-first-search.html)

## 📚 연습 문제
- [BOJ 1260 DFS와 BFS](https://www.acmicpc.net/problem/1260) ⭐ 필수
- [BOJ 2667 단지번호붙이기](https://www.acmicpc.net/problem/2667) ⭐
- [BOJ 2178 미로 탐색](https://www.acmicpc.net/problem/2178) ⭐ BFS 최단거리
- [BOJ 7576 토마토](https://www.acmicpc.net/problem/7576) ⭐⭐ 다중 시작점 BFS
- [BOJ 11724 연결 요소의 개수](https://www.acmicpc.net/problem/11724)
