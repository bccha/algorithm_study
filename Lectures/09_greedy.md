# 그리디 (Greedy)

## 📌 개념
**매 순간 가장 좋아 보이는 선택**을 하는 알고리즘.
항상 최적해를 보장하지는 않지만, 일부 문제에서는 정답.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**가장 빠른/작은/큰 것부터** 선택"
### 💡 N-Queen 예시
1. (0,0)에 퀸 놓음
2. (1,0) 불가능, (1,1) 불가능, (1,2) 가능 → 놓음
3. (2,0)~(2,3) 모두 불가능 → **가망 없음 (Backtrack!)**
4. (1,2) 취소하고 (1,3) 시도...
→ 이렇게 "안 될 것 같으면 되돌아가는 것"이 핵심!

### 🎓 실전 팁
1. **상태 공간 트리**: 머릿속으로 그려보기
2. **Promising 함수**: 가지치기 조건(`promising` or `isValid`)를 먼저 구현
3. **Visit 배열 관리**: 재귀 **호출 전** 체크, **복귀 후** 해제 (원상복구)
4. **시간복잡도**: 예측 어려움 (최악 지수시간), N이 작을 때만 사용 → 큰 단위부터 (단, 배수 관계일 때만!)
- "최소/최대 만들기" → 정렬 후 양 끝부터

### 💡 그리디 vs DP vs 브루트포스
- **동전 문제**: 
  - 단위: 10, 50, 100 (배수 관계) → **그리디 OK**
  - 단위: 10, 60, 100 (배수 아님) → **DP 사용!** (60+60 < 100+10+10)

### 💡 결정 문제로 변환 (Parametric Search)
"랜선 K개를 만들 수 있는 최대 길이는?"
→ "길이 X로 잘랐을 때 K개 이상 나오는가?" (Yes/No)
- Yes → 길이를 더 늘려봄 (최적해는 오른쪽)
- No → 길이를 줄여야 함 (왼쪽 탐색)
- **O(log(길이))**로 최적값 찾음!

### 🎓 실전 팁
1. **범위 설정**: lo=1, hi=최댓값 (hi 설정 주의)
2. **자료형**: 합계 구할 때 `long long` 필수!
3. **무한 루프**: `lo = mid + 1`, `hi = mid - 1`로 확실히 줄이기
4. **정렬**: 이분탐색 전 정렬되어 있어야 함 (Parametric 제외)크거나 작은, 배수 아닌 등) 넣어보기

## 🔑 그리디가 적용되는 조건
1. **탐욕적 선택 속성**: 현재 최선의 선택이 최종 해에 포함됨
2. **최적 부분 구조**: 부분 문제의 최적해가 전체 문제의 최적해에 포함됨

> 💡 증명이 어려우면 **몇 가지 반례**를 찾아보는 것이 실전적!

## 💻 대표 문제

### 1. 동전 문제 (특수한 경우만 그리디)
```cpp
// 동전이 배수 관계일 때만 그리디 가능!
int coins[] = {500, 100, 50, 10};
int n;  // 목표 금액
int cnt = 0;
for (int coin : coins) {
    cnt += n / coin;
    n %= coin;
}
```

### 2. 회의실 배정 (활동 선택)
```cpp
// 종료 시간이 빠른 순으로 선택
vector<pair<int,int>> meetings; // {end, start}
sort(meetings.begin(), meetings.end());

int cnt = 0, lastEnd = 0;
for (auto& [end, start] : meetings) {
    if (start >= lastEnd) {
        cnt++;
        lastEnd = end;
    }
}
```

### 3. ATM (최소 대기 시간)
```cpp
// 처리 시간이 짧은 순으로 처리
vector<int> times;
sort(times.begin(), times.end());

int total = 0, sum = 0;
for (int t : times) {
    sum += t;
    total += sum;
}
```

### 4. 잃어버린 괄호 (최소값 만들기)
```cpp
// 55-50+40 → 55-(50+40) 형태로
// 첫 번째 마이너스 이후는 모두 빼기
string s;  // "55-50+40"
int result = 0, cur = 0, sign = 1;
bool minus_appeared = false;

for (char c : s + "+") {
    if (c == '+' || c == '-') {
        result += (minus_appeared ? -cur : cur);
        cur = 0;
        if (c == '-') minus_appeared = true;
    } else {
        cur = cur * 10 + (c - '0');
    }
}
```

## 🐍 Python
```python
# 회의실 배정
meetings.sort(key=lambda x: x[1])  # 종료 시간 기준

cnt, last_end = 0, 0
for start, end in meetings:
    if start >= last_end:
        cnt += 1
        last_end = end
```

## 🎯 그리디 vs DP
| 특성 | 그리디 | DP |
|------|--------|-----|
| 결정 시점 | 현재 상황만 고려 | 이전 결과 참조 |
| 복잡도 | 보통 O(N) ~ O(NlogN) | 보통 O(N²) 이상 |
| 정확성 | 증명 필요 | 항상 최적 |

## 📖 외부 자료
- [Greedy Algorithms - GeeksforGeeks](https://www.geeksforgeeks.org/greedy-algorithms/)
- [그리디 vs DP 비교](https://blog.encrypted.gg/974)

## 📚 연습 문제
- [BOJ 11047 동전 0](https://www.acmicpc.net/problem/11047) ⭐
- [BOJ 1931 회의실 배정](https://www.acmicpc.net/problem/1931) ⭐⭐ 필수
- [BOJ 11399 ATM](https://www.acmicpc.net/problem/11399)
- [BOJ 1541 잃어버린 괄호](https://www.acmicpc.net/problem/1541) ⭐
- [BOJ 1744 수 묶기](https://www.acmicpc.net/problem/1744)
