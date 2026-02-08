# 백트래킹 (Backtracking)

## 📌 개념
**모든 경우를 탐색**하되, **가지치기(pruning)**로 불필요한 탐색을 줄이는 기법.
DFS 기반으로 구현.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**N과 M** 시리즈" → 순열/조합 생성
- "**N-Queen** 문제" → 충돌 조건 체크
- "**스도쿠**" → 숫자 배치 + 조건 검사
- "가능한 모든 배치/선택을 시도하되, **조건 위반 시 즉시 중단**"
- "브루트포스지만 **가지치기 최적화** 필요"

## 🔑 핵심 패턴
1. 선택 (Choose)
2. 탐색 (Explore)
3. 복구 (Unchoose)

## 💻 순열/조합

### 순열 (N과 M 시리즈)
```cpp
int n, m;
int arr[10];
bool used[10];

void permutation(int depth) {
    if (depth == m) {
        for (int i = 0; i < m; i++) cout << arr[i] << ' ';
        cout << '\n';
        return;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;        // 선택
            arr[depth] = i;
            permutation(depth + 1); // 탐색
            used[i] = false;       // 복구
        }
    }
}
```

### 조합
```cpp
void combination(int start, int depth) {
    if (depth == m) {
        for (int i = 0; i < m; i++) cout << arr[i] << ' ';
        cout << '\n';
        return;
    }
    
    for (int i = start; i <= n; i++) {
        arr[depth] = i;
        combination(i + 1, depth + 1);  // i+1부터 시작 (중복 X)
    }
}
```

### 중복 순열
```cpp
void permutation_with_rep(int depth) {
    if (depth == m) { /* 출력 */ return; }
    for (int i = 1; i <= n; i++) {
        arr[depth] = i;
        permutation_with_rep(depth + 1);  // used 체크 안함
    }
}
```

### 중복 조합
```cpp
void combination_with_rep(int start, int depth) {
    if (depth == m) { /* 출력 */ return; }
    for (int i = start; i <= n; i++) {
        arr[depth] = i;
        combination_with_rep(i, depth + 1);  // i부터 시작 (중복 O)
    }
}
```

## 💻 N-Queen
```cpp
int n, cnt = 0;
int col[15];  // col[row] = 퀸이 놓인 열

bool isValid(int row) {
    for (int i = 0; i < row; i++) {
        if (col[i] == col[row]) return false;  // 같은 열
        if (abs(col[i] - col[row]) == row - i) return false;  // 대각선
    }
    return true;
}

void solve(int row) {
    if (row == n) {
        cnt++;
        return;
    }
    
    for (int c = 0; c < n; c++) {
        col[row] = c;
        if (isValid(row)) {
            solve(row + 1);
        }
    }
}
```

## 🐍 Python
```python
def permutation(depth, arr, used):
    if depth == m:
        print(*arr)
        return
    for i in range(1, n+1):
        if not used[i]:
            used[i] = True
            arr.append(i)
            permutation(depth + 1, arr, used)
            arr.pop()
            used[i] = False
```

## 📖 외부 자료
- [Backtracking - GeeksforGeeks](https://www.geeksforgeeks.org/backtracking-algorithms/)
- [N-Queen 시각화](https://www.youtube.com/watch?v=xouin83ebxE)

## 📚 연습 문제
- [BOJ 15649 N과 M (1)](https://www.acmicpc.net/problem/15649) ⭐ 순열
- [BOJ 15650 N과 M (2)](https://www.acmicpc.net/problem/15650) ⭐ 조합
- [BOJ 9663 N-Queen](https://www.acmicpc.net/problem/9663) ⭐⭐ 필수
- [BOJ 14888 연산자 끼워넣기](https://www.acmicpc.net/problem/14888)
- [BOJ 2580 스도쿠](https://www.acmicpc.net/problem/2580) ⭐⭐
