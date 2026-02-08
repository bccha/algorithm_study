# 트리 DP (Tree DP)

## 📌 개념
트리 구조에서 **서브트리**를 부분 문제로 다루는 DP.
DFS로 자식 → 부모 순서로 값을 계산.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "트리에서 **선택/배치**하는 최적 방법"
- "**독립집합**/정점 커버"
- "트리의 **지름**"
- "서브트리의 **크기/합/개수**"
- "부모-자식 관계를 이용한 최적화"

---

## 💻 기본 패턴
```cpp
int dp[MAX];

void dfs(int cur, int parent) {
    // 기본값 초기화
    dp[cur] = 1;  // 예: 서브트리 크기
    
    for (int next : adj[cur]) {
        if (next != parent) {
            dfs(next, cur);
            dp[cur] += dp[next];  // 자식 결과 합치기
        }
    }
}
```

---

## 1️⃣ 트리의 독립 집합
인접한 두 정점을 동시에 선택하지 않으면서 최대 가중치 합.

```cpp
int dp[MAX][2];  // dp[i][0] = i 미선택, dp[i][1] = i 선택
int weight[MAX];

void dfs(int cur, int parent) {
    dp[cur][0] = 0;
    dp[cur][1] = weight[cur];
    
    for (int next : adj[cur]) {
        if (next != parent) {
            dfs(next, cur);
            dp[cur][0] += max(dp[next][0], dp[next][1]);  // 자식 선택 가능
            dp[cur][1] += dp[next][0];  // 자식 미선택만
        }
    }
}

// 답: max(dp[root][0], dp[root][1])
```

---

## 2️⃣ 트리의 지름
트리에서 가장 먼 두 정점 사이의 거리.

```cpp
int maxDist = 0;

int dfs(int cur, int parent) {
    int first = 0, second = 0;  // 가장 긴 두 경로
    
    for (auto [next, w] : adj[cur]) {
        if (next != parent) {
            int d = dfs(next, cur) + w;
            
            if (d > first) {
                second = first;
                first = d;
            } else if (d > second) {
                second = d;
            }
        }
    }
    
    maxDist = max(maxDist, first + second);  // 이 노드를 지나는 최장 경로
    return first;  // 부모에게 전달
}
```

---

## 3️⃣ 서브트리 쿼리
각 노드의 서브트리 크기 계산.

```cpp
int subtreeSize[MAX];

void dfs(int cur, int parent) {
    subtreeSize[cur] = 1;
    
    for (int next : adj[cur]) {
        if (next != parent) {
            dfs(next, cur);
            subtreeSize[cur] += subtreeSize[next];
        }
    }
}
```

---

## 📖 외부 자료
- [Tree DP - CP Algorithms](https://cp-algorithms.com/)
- [트리 DP 설명](https://blog.encrypted.gg/1010)

## 📚 연습 문제
- [BOJ 15681 트리와 쿼리](https://www.acmicpc.net/problem/15681) ⭐⭐ 서브트리 크기
- [BOJ 1167 트리의 지름](https://www.acmicpc.net/problem/1167) ⭐⭐⭐
- [BOJ 2213 트리의 독립집합](https://www.acmicpc.net/problem/2213) ⭐⭐⭐
- [BOJ 2533 사회망 서비스(SNS)](https://www.acmicpc.net/problem/2533) ⭐⭐⭐
- [BOJ 1949 우수 마을](https://www.acmicpc.net/problem/1949) ⭐⭐⭐
