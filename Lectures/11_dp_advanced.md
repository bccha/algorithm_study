# DP 심화 (Bitmask DP, 구간 DP)

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다

**Bitmask DP:**
- "N개의 도시를 **모두 방문**" (TSP)
- "집합의 상태를 관리" (N ≤ 20)
- "각 원소를 포함/제외하는 모든 경우"
- "작업 배정" → 사람-작업 매칭

**구간 DP:**
- "**구간을 합치는 비용**" (행렬 곱셈 순서, 파일 합치기)
- "회문 판별/만들기"
- "점화식이 dp[i][j] = f(dp[i][k], dp[k+1][j]) 형태"

## 1️⃣ Bitmask DP
**집합의 상태**를 비트마스크로 표현하여 DP.

### 핵심 개념
- N개의 원소 → 2^N 가지 상태
- i번째 비트가 1이면 i번째 원소 사용

### 외판원 순회 (TSP)
```cpp
// dp[mask][i] = mask 상태에서 현재 i에 있을 때 최소 비용
int dp[1 << 16][16];
int dist[16][16];  // 거리 행렬
int n;

int tsp(int mask, int cur) {
    if (mask == (1 << n) - 1) {
        return dist[cur][0] ? dist[cur][0] : INF;  // 시작점으로 복귀
    }
    
    if (dp[mask][cur] != -1) return dp[mask][cur];
    
    int ret = INF;
    for (int next = 0; next < n; next++) {
        if (mask & (1 << next)) continue;  // 이미 방문
        if (dist[cur][next] == 0) continue;  // 연결 없음
        
        ret = min(ret, tsp(mask | (1 << next), next) + dist[cur][next]);
    }
    
    return dp[mask][cur] = ret;
}

// 호출: tsp(1, 0) - 0번에서 시작
```

### 작업 배정 (Assignment Problem)
```cpp
// dp[mask] = mask 집합의 작업을 처리하는 최소 비용
// i번 사람이 j번 작업을 할 때 비용 cost[i][j]
int dp[1 << 20];

int solve() {
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int person = __builtin_popcount(mask);  // 몇 번째 사람인지
        
        for (int job = 0; job < n; job++) {
            if (mask & (1 << job)) continue;
            dp[mask | (1 << job)] = min(dp[mask | (1 << job)], 
                                        dp[mask] + cost[person][job]);
        }
    }
    return dp[(1 << n) - 1];
}
```

## 2️⃣ 구간 DP
**구간 [i, j]**를 상태로 두고, 작은 구간에서 큰 구간으로 확장.

### 행렬 곱셈 순서
```cpp
// dp[i][j] = i~j번 행렬을 곱하는 최소 연산 수
// 행렬 크기: matrix[i] = (r[i], c[i]), c[i] = r[i+1]
int dp[500][500];
int r[500], c[500];

int solve(int n) {
    // 길이 1인 구간: 비용 0
    for (int i = 0; i < n; i++) dp[i][i] = 0;
    
    // 구간 길이 2부터
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            
            for (int k = i; k < j; k++) {
                // [i,k]와 [k+1,j]를 곱하는 비용
                dp[i][j] = min(dp[i][j], 
                    dp[i][k] + dp[k+1][j] + r[i] * c[k] * c[j]);
            }
        }
    }
    return dp[0][n-1];
}
```

### 파일 합치기
```cpp
// dp[i][j] = i~j번 파일을 하나로 합치는 최소 비용
// prefix[i] = 0~i-1번 파일 크기의 합
int dp[500][500];
int prefix[501];

int solve(int n) {
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], 
                    dp[i][k] + dp[k+1][j] + (prefix[j+1] - prefix[i]));
            }
        }
    }
    return dp[0][n-1];
}
```

## 📖 외부 자료
- [Bitmask DP - CP Algorithms](https://cp-algorithms.com/dynamic_programming/bitmasks.html)
- [구간 DP 설명](https://blog.encrypted.gg/1006)

## 📚 연습 문제
- [BOJ 2098 외판원 순회](https://www.acmicpc.net/problem/2098) ⭐⭐⭐ Bitmask DP
- [BOJ 1311 할 일 정하기 1](https://www.acmicpc.net/problem/1311) ⭐⭐ Bitmask DP
- [BOJ 11066 파일 합치기](https://www.acmicpc.net/problem/11066) ⭐⭐⭐ 구간 DP
- [BOJ 11049 행렬 곱셈 순서](https://www.acmicpc.net/problem/11049) ⭐⭐⭐ 구간 DP
- [BOJ 10942 팰린드롬?](https://www.acmicpc.net/problem/10942) ⭐⭐
