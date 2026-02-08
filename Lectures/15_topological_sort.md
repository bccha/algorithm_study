# 위상 정렬 (Topological Sort)

## 📌 개념
**DAG (Directed Acyclic Graph)**에서 선후 관계를 지키며 정렬.
## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**선행 조건**이 있는 작업 순서"
- "**의존 관계** 있는 과목/건물"
- "방향 그래프에서 **순서 결정**"
- "사이클 판별" (위상정렬 불가 → 사이클 존재)
- 문제에 "**prerequisite, dependency**" 키워드

### 대표 문제 패턴
- "커리큘럼 (선수과목)"
- "건물 짓기" (선행 건물)
- "줄 세우기" (키 순서)

### 💡 동작 과정 (위상정렬)
1. 진입차수 0인 노드 큐에 넣기
2. 큐에서 A 꺼냄 → A는 순서 결정됨!
3. A와 연결된 간선 제거 (B의 진입차수 감소)
4. B의 진입차수 0 되면 큐에 넣기

### 🎓 실전 팁
1. **사이클**: 큐가 비었는데 방문 안 한 노드가 남으면 사이클 존재!
2. **진입차수(Indegree)**: 미리 배열에 카운팅 해둬야 함
3. **답이 여러 개**: 큐에 2개 이상 들어있으면 여러 순서 가능
4. **우선순위**: "가능하면 작은 번호부터" → `priority_queue` 사용

## ⏱️ 시간복잡도: O(V + E)

---

## 💻 Kahn's Algorithm (BFS 기반)
```cpp
#include <queue>
using namespace std;

vector<int> adj[MAX];
int indegree[MAX];  // 진입 차수

vector<int> topologicalSort(int n) {
    queue<int> q;
    vector<int> result;
    
    // 진입 차수 0인 노드 먼저 처리
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        result.push_back(cur);
        
        for (int next : adj[cur]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    // 사이클 존재 시 모든 노드가 포함되지 않음
    if (result.size() != n) return {};  // 사이클!
    
    return result;
}
```

---

## 💻 DFS 기반
```cpp
vector<int> adj[MAX];
bool visited[MAX];
stack<int> stk;

void dfs(int cur) {
    visited[cur] = true;
    for (int next : adj[cur]) {
        if (!visited[next]) {
            dfs(next);
        }
    }
    stk.push(cur);  // 후위 순서로 스택에 삽입
}

vector<int> topologicalSort(int n) {
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i);
    }
    
    vector<int> result;
    while (!stk.empty()) {
        result.push_back(stk.top());
        stk.pop();
    }
    return result;
}
```

---

## 🐍 Python
```python
from collections import deque

def topological_sort(n, adj, indegree):
    q = deque([i for i in range(1, n+1) if indegree[i] == 0])
    result = []
    
    while q:
        cur = q.popleft()
        result.append(cur)
        
        for nxt in adj[cur]:
            indegree[nxt] -= 1
            if indegree[nxt] == 0:
                q.append(nxt)
    
    return result if len(result) == n else []
```

---

## 🎯 응용: 위상정렬 + DP
```cpp
// ACM Craft: 건물 짓기 (선행 건물 완료 후 시작)
// dp[i] = i번 건물을 짓기까지 걸리는 최소 시간
int dp[MAX], buildTime[MAX];

void solve(int n) {
    queue<int> q;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = buildTime[i];
        if (indegree[i] == 0) q.push(i);
    }
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        for (int next : adj[cur]) {
            dp[next] = max(dp[next], dp[cur] + buildTime[next]);
            indegree[next]--;
            if (indegree[next] == 0) q.push(next);
        }
    }
}
```

---

## 📖 외부 자료
- [Topological Sort - CP Algorithms](https://cp-algorithms.com/graph/topological-sort.html)
- [위상정렬 시각화](https://visualgo.net/en/dfsbfs)

## 📚 연습 문제
- [BOJ 2252 줄 세우기](https://www.acmicpc.net/problem/2252) ⭐⭐ 기본
- [BOJ 1766 문제집](https://www.acmicpc.net/problem/1766) ⭐⭐⭐ 우선순위 큐 조합
- [BOJ 1005 ACM Craft](https://www.acmicpc.net/problem/1005) ⭐⭐⭐ 위상정렬 + DP
- [BOJ 2056 작업](https://www.acmicpc.net/problem/2056) ⭐⭐
- [BOJ 3665 최종 순위](https://www.acmicpc.net/problem/3665) ⭐⭐⭐
