# BFS 심화 (0-1 BFS, 다차원 상태)

## 📌 개념
기본 BFS를 확장하여 **가중치가 0/1인 그래프** 또는 **추가 상태**를 다루는 기법.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다

**0-1 BFS:**
- "벽 부수는데 비용 1, 빈칸 이동은 비용 0"
- "텔레포트(0) vs 걷기(1)"
- "일부 간선만 가중치가 있는 최단 경로"

**다차원 상태 BFS:**
- "벽을 K개까지 부술 수 있음" → visited[x][y][벽부순횟수]
- "아이템을 가진 상태/없는 상태" → visited[x][y][아이템보유]
- "밤/낮 구분" → visited[x][y][시간대]
- "말의 이동(특수) + 일반 이동" → visited[x][y][특수이동횟수]

### ⚠️ Dijkstra vs 0-1 BFS
| 조건 | 추천 |
|------|------|
| 가중치 0/1만 | **0-1 BFS** (더 빠름) |
| 가중치 양의 정수 | **Dijkstra** |
| 가중치 0/1/2... | Dijkstra |

## 1️⃣ 0-1 BFS
가중치가 0 또는 1인 경우, **덱(Deque)**을 사용하여 Dijkstra 없이 O(V+E)로 최단 경로.

### 아이디어
- 가중치 0: **앞**에 push (우선 처리)
- 가중치 1: **뒤**에 push (나중 처리)

```cpp
#include <deque>

int dist[MAX];
memset(dist, -1, sizeof(dist));

deque<int> dq;
dq.push_back(start);
dist[start] = 0;

while (!dq.empty()) {
    int cur = dq.front();
    dq.pop_front();
    
    for (auto& [next, weight] : adj[cur]) {
        if (dist[next] == -1 || dist[cur] + weight < dist[next]) {
            dist[next] = dist[cur] + weight;
            
            if (weight == 0)
                dq.push_front(next);  // 앞에
            else
                dq.push_back(next);   // 뒤에
        }
    }
}
```

### 대표 문제: 알고스팟
```cpp
// 벽 부수기: 0 = 빈 칸, 1 = 벽
// 벽을 부수면 비용 1, 안 부수면 비용 0
int n, m;
char grid[MAX][MAX];
int dist[MAX][MAX];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs() {
    memset(dist, -1, sizeof(dist));
    deque<pair<int,int>> dq;
    dq.push_back({0, 0});
    dist[0][0] = 0;
    
    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            
            int cost = (grid[nx][ny] == '1') ? 1 : 0;
            
            if (dist[nx][ny] == -1 || dist[x][y] + cost < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + cost;
                if (cost == 0) dq.push_front({nx, ny});
                else dq.push_back({nx, ny});
            }
        }
    }
}
```

## 2️⃣ 다차원 상태 BFS
**위치 + 추가 정보**를 상태로 관리.

### 예: 벽 부수고 이동하기
```cpp
// visited[x][y][k] = (x,y)에서 k개의 벽을 부순 상태
int visited[MAX][MAX][2];  // 0: 안 부숨, 1: 부숨

struct State {
    int x, y, broken, dist;
};

int bfs() {
    queue<State> q;
    q.push({0, 0, 0, 1});
    visited[0][0][0] = true;
    
    while (!q.empty()) {
        auto [x, y, broken, d] = q.front();
        q.pop();
        
        if (x == n-1 && y == m-1) return d;
        
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            
            // 빈 칸
            if (grid[nx][ny] == 0 && !visited[nx][ny][broken]) {
                visited[nx][ny][broken] = true;
                q.push({nx, ny, broken, d + 1});
            }
            
            // 벽 + 아직 부수지 않음
            if (grid[nx][ny] == 1 && broken == 0 && !visited[nx][ny][1]) {
                visited[nx][ny][1] = true;
                q.push({nx, ny, 1, d + 1});
            }
        }
    }
    return -1;
}
```

## 📖 외부 자료
- [0-1 BFS 설명 - CP Algorithms](https://cp-algorithms.com/graph/01_bfs.html)
- [다차원 BFS 예제 모음](https://blog.encrypted.gg/1011)

## 📚 연습 문제
- [BOJ 1261 알고스팟](https://www.acmicpc.net/problem/1261) ⭐⭐ 0-1 BFS
- [BOJ 13549 숨바꼭질 3](https://www.acmicpc.net/problem/13549) ⭐⭐ 0-1 BFS
- [BOJ 2206 벽 부수고 이동하기](https://www.acmicpc.net/problem/2206) ⭐⭐⭐ 상태 BFS
- [BOJ 14226 이모티콘](https://www.acmicpc.net/problem/14226) ⭐⭐
- [BOJ 9019 DSLR](https://www.acmicpc.net/problem/9019)
