# 다이나믹 프로그래밍 기초 (DP Basic)

## 📌 개념
**큰 문제를 작은 부분 문제로 나누어 해결**하고, 결과를 저장(메모이제이션)하여 중복 계산 방지.

### 🔍 왜 필요한가?
피보나치를 재귀로 구현하면:
```cpp
fib(5) = fib(4) + fib(3)
       = (fib(3) + fib(2)) + (fib(2) + fib(1))
       = ...
```
→ fib(2), fib(3) 등이 **여러 번 중복 계산**됨!
→ 시간복잡도 O(2^N) 💣

**DP로 해결:**
- 한 번 계산한 값은 **저장(memoization)**
- 다시 필요하면 저장된 값 사용
→ 시간복잡도 O(N) ✅

## 🔑 DP 적용 조건
1. **최적 부분 구조**: 큰 문제의 최적해가 작은 문제의 최적해로 구성됨
2. **중복 부분 문제**: 같은 작은 문제가 여러 번 등장

### 💡 DP vs 분할정복(Divide & Conquer)
| 특징 | DP | 분할정복 |
|------|-----|----------|
| 부분 문제 | **중복됨** | 독립적 |
| 저장 | 메모이제이션 | 필요없음 |
| 예시 | 피보나치 | 병합정렬 |

## 💡 접근법
1. **점화식 세우기**: dp[i] = ???
2. **기저 조건 설정**: dp[0], dp[1] 등
3. **탐색 순서 결정**: Bottom-up (반복문) vs Top-down (재귀+메모)

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**최소/최대** 비용/횟수/길이" → DP 가능성 높음
- "경우의 수를 세어라" → DP
- "N번째 값을 구하라" (N이 큼) → DP
- "부분 문제로 쪼갤 수 있고, 겹치는 계산이 많다" → DP

### DP 키워드
- "N로 만들 수 있는 최소/최대"
- "가장 긴 증가하는/감소하는"
- "N개를 선택하는 경우의 수"
- "배낭 문제" (무게 제한)
- "동전 문제" (최소 개수)
- "타일링" (경우의 수)

## 💻 예시: 피보나치 수열

### Top-down (재귀 + 메모이제이션)
```cpp
int memo[100];
int fib(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib(n-1) + fib(n-2);
}
```

### Bottom-up (반복문)
```cpp
int dp[100];
dp[0] = 0; dp[1] = 1;
for (int i = 2; i <= n; i++)
    dp[i] = dp[i-1] + dp[i-2];
```

## 📐 대표 유형

### 1. 1차원 DP
```cpp
// BOJ 1463: 1로 만들기
// dp[i] = i를 1로 만드는 최소 연산 횟수
dp[1] = 0;
for (int i = 2; i <= n; i++) {
    dp[i] = dp[i-1] + 1;  // -1
    if (i % 2 == 0) dp[i] = min(dp[i], dp[i/2] + 1);
    if (i % 3 == 0) dp[i] = min(dp[i], dp[i/3] + 1);
}
```

### 2. 2차원 DP (격자)
```cpp
// BOJ 1932: 정수 삼각형
// dp[i][j] = (i,j)까지 오는 최대 합
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
        dp[i][j] = arr[i][j] + max(dp[i-1][j-1], dp[i-1][j]);
    }
}
```

### 3. LIS (최장 증가 부분 수열)
```cpp
// O(N²) 풀이
// dp[i] = arr[i]로 끝나는 LIS 길이
for (int i = 0; i < n; i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
        if (arr[j] < arr[i])
            dp[i] = max(dp[i], dp[j] + 1);
    }
}
int ans = *max_element(dp, dp + n);
```

### 4. 배낭 문제 (Knapsack)
```cpp
// 0-1 배낭: 각 물건을 한 번만 선택
// dp[i][w] = i번째 물건까지 고려, 무게 w일 때 최대 가치
for (int i = 1; i <= n; i++) {
    for (int w = 0; w <= W; w++) {
        if (weight[i] <= w)
            dp[i][w] = max(dp[i-1][w], dp[i-1][w-weight[i]] + value[i]);
        else
            dp[i][w] = dp[i-1][w];
    }
}

// 공간 최적화 (1차원)
for (int i = 1; i <= n; i++)
    for (int w = W; w >= weight[i]; w--)  // 역순!
        dp[w] = max(dp[w], dp[w-weight[i]] + value[i]);
```

## 🐍 Python
```python
# 1로 만들기
dp = [0] * (n + 1)
for i in range(2, n + 1):
    dp[i] = dp[i-1] + 1
    if i % 2 == 0: dp[i] = min(dp[i], dp[i//2] + 1)
    if i % 3 == 0: dp[i] = min(dp[i], dp[i//3] + 1)
```

---

## 💡 구체적 예시: 1로 만들기
```
N = 10을 1로 만드는 최소 연산 횟수?

가능한 연산:
1. -1
2. /2 (짝수일 때)
3. /3 (3의 배수일 때)
```

**DP 테이블 계산:**
```
dp[1] = 0
dp[2] = dp[1] + 1 = 1  (2/2)
dp[3] = dp[1] + 1 = 1  (3/3)
dp[4] = min(dp[3]+1, dp[2]+1) = 2  (4-1→3, 또는 4/2→2)
...
dp[10] = min(dp[9]+1, dp[5]+1) = 3
       = 10 → 9 → 3 → 1
```

### 🎓 실전 팁
1. **점화식이 핵심**: dp[i]를 dp[i-1], dp[i-2] 등으로 표현  
2. **기저 조건 먼저**: dp[0], dp[1] 등 먼저 설정
3. **Top-down vs Bottom-up**: 
   - Top-down: 재귀+메모, 직관적, 필요한 것만 계산
   - Bottom-up: 반복문, 빠름, 공간 최적화 가능
4. **배열 크기 주의**: 범위 초과하지 않게!

---

## 📖 외부 자료
- [Dynamic Programming - CP Algorithms](https://cp-algorithms.com/dynamic_programming/intro-to-dp.html)
- [TopCoder DP 튜토리얼](https://www.topcoder.com/thrive/articles/Dynamic%20Programming:%20From%20Novice%20to%20Advanced)
- [DP 유형별 정리 - Blog](https://blog.encrypted.gg/category/강좌/실전%20알고리즘)

## 📚 연습 문제
- [BOJ 1463 1로 만들기](https://www.acmicpc.net/problem/1463) ⭐ 필수
- [BOJ 11726 2×n 타일링](https://www.acmicpc.net/problem/11726) ⭐
- [BOJ 11053 가장 긴 증가하는 부분 수열](https://www.acmicpc.net/problem/11053) ⭐⭐
- [BOJ 1932 정수 삼각형](https://www.acmicpc.net/problem/1932)
- [BOJ 12865 평범한 배낭](https://www.acmicpc.net/problem/12865) ⭐⭐ 배낭
