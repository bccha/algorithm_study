# 브루트포스 (Brute Force)

## 📌 개념
#### 💡 구체적 예시: 최대공약수 (GCD)
- 12, 18의 GCD?
  - `gcd(12, 18) = gcd(18, 12%18) = gcd(18, 12)`
  - `gcd(18, 12) = gcd(12, 18%12) = gcd(12, 6)`
  - `gcd(12, 6) = gcd(6, 12%6) = gcd(6, 0) = 6`

### 🎓 실전 팁
1. **오버플로우**: LCM 계산 시 `(a * b) / c` 하면 `a*b`에서 터짐! → `(a/c) * b`
2. **시간복잡도**: 소수 판별 O(N) 절대 안됨! O(√N) 사용
3. **실수 오차**: `double` 말고 `long long` 정수 연산 지향
4. **모듈러 연산**: 뺄셈은 `(a - b + MOD) % MOD` (음수 방지)
**모든 경우의 수를 다 시도**해서 정답을 찾는 방법.
시간복잡도만 허용되면 가장 확실한 방법!

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**모든 경우**를 확인" → 브루트포스
- "N이 작다" (N ≤ 10~20) → 가능성 높음
### 💡 완전탐색 접근법
1. **무식하게 다 해보기**: for문 중첩
2. **순열/조합**: `next_permutation`, 재귀
3. **비트마스크**: 부분집합 상태 표현
4. **백트래킹**: 가지치기로 최적화

### 🎓 실전 팁
1. **입력 크기 확인**: N이 작으면(<=20) 일단 의심!
2. **1억 연산 ≈ 1초**: O(N!)은 N=10, O(2^N)은 N=20까지 안전
3. **재귀함수 파라미터**: 필요한 상태값만 넘기기 (무거운 객체 복사 금지)
4. **초기화**: TC 여러 개일 때 전역변수 초기화 필수

## ⏱️ 시간복잡도 계산
- N개에서 순서 있게 R개 선택 (순열): N!/(N-R)!
- N개에서 순서 없이 R개 선택 (조합): nCr
- 2^N: 부분집합의 개수

> 💡 **1초에 약 10^8 연산** 가능하다고 가정!
> - N ≤ 10: O(N!) 가능
> - N ≤ 20: O(2^N) 가능
> - N ≤ 100: O(N^3) 가능
> - N ≤ 10^6: O(NlogN) 가능

## 💻 패턴별 코드

### 1. 반복문 (N중 for문)
```cpp
// N개 중 2개 고르기 O(N²)
for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
        // (i, j) 처리
```

### 2. 재귀 (순열/조합 생성)
```cpp
// 순열: N개에서 R개 뽑아 순서있게 나열
vector<int> arr, perm;
vector<bool> used;
void permutation(int depth, int r) {
    if (depth == r) {
        // perm 사용
        return;
    }
    for (int i = 0; i < arr.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            perm.push_back(arr[i]);
            permutation(depth + 1, r);
            perm.pop_back();
            used[i] = false;
        }
    }
}

// 조합: N개에서 R개 뽑기 (순서 무시)
void combination(int start, int depth, int r) {
    if (depth == r) {
        // perm 사용
        return;
    }
    for (int i = start; i < arr.size(); i++) {
        perm.push_back(arr[i]);
        combination(i + 1, depth + 1, r);
        perm.pop_back();
    }
}
```

### 3. 비트마스크 (부분집합)
```cpp
// 모든 부분집합 O(2^N)
for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            // i번째 원소 포함
        }
    }
}
```

### 4. STL next_permutation
```cpp
vector<int> arr = {1, 2, 3};
sort(arr.begin(), arr.end());  // 정렬 필수!
do {
    // arr 순열 처리
} while (next_permutation(arr.begin(), arr.end()));
```

## 🐍 Python
```python
from itertools import permutations, combinations

arr = [1, 2, 3]

# 순열
for p in permutations(arr, 2):  # 2개 뽑아 순서있게
    print(p)

# 조합
for c in combinations(arr, 2):  # 2개 뽑기
    print(c)

# 부분집합
for mask in range(1 << len(arr)):
    subset = [arr[i] for i in range(len(arr)) if mask & (1 << i)]
```

## 📖 외부 자료
- [Brute Force - GeeksforGeeks](https://www.geeksforgeeks.org/brute-force-algorithms/)
- [순열/조합 시각화](https://www.mathsisfun.com/combinatorics/combinations-permutations.html)

## 📚 연습 문제
- [BOJ 2309 일곱 난쟁이](https://www.acmicpc.net/problem/2309) ⭐
- [BOJ 1107 리모컨](https://www.acmicpc.net/problem/1107) ⭐⭐
- [BOJ 14500 테트로미노](https://www.acmicpc.net/problem/14500)
- [BOJ 1182 부분수열의 합](https://www.acmicpc.net/problem/1182) ⭐
