# 이분 탐색 (Binary Search)

## 📌 개념
**정렬된 배열**에서 O(logN)에 원하는 값을 찾는 알고리즘.
"결정 문제" 형태로 바꿔서 **Parametric Search**에도 활용.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "X개 이상 만들 수 있는 **최대/최소** 값"
- "조건을 만족하는 **최적값** 찾기"
- "정렬된 배열에서 검색"
- "X가 가능한가?"를 O(N)에 판별 가능 → Parametric Search

### Parametric Search 패턴
1. **랜선 자르기**: "K개 이상 만들 수 있는 최대 길이"
2. **나무 자르기**: "M미터 이상 얻는 최대 높이"
3. **공유기 설치**: "C개 설치, 최소 거리 최대화"
4. **예산 배분**: "조건 만족하는 최대/최소 예산"

### ⚠️ 주의사항
- **정렬 필수** (기본 이분탐색)
- **단조성 확인** (Parametric Search): X가 가능하면 X-1도 가능한지?
- **오버플로우**: `mid = (lo + hi) / 2` → `mid = lo + (hi - lo) / 2`

## ⏱️ 시간복잡도: O(logN)

## 💻 기본 이분 탐색
```cpp
// target이 있으면 인덱스, 없으면 -1
int binarySearch(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;  // 오버플로우 방지
        
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
```

## 💻 STL 활용
```cpp
// lower_bound: target 이상인 첫 위치
// upper_bound: target 초과인 첫 위치
vector<int> arr = {1, 2, 2, 2, 3, 4};

auto lb = lower_bound(arr.begin(), arr.end(), 2);  // index 1
auto ub = upper_bound(arr.begin(), arr.end(), 2);  // index 4

// 개수 세기
int count = ub - lb;  // 2가 3개
```

## 💻 Parametric Search
**"X가 가능한가?"** 를 판별하는 함수로 최적값 찾기.

```cpp
// 예: 랜선 자르기 - K개 이상 만들 수 있는 최대 길이
bool canMake(vector<int>& cables, int len, int k) {
    long long cnt = 0;
    for (int c : cables) cnt += c / len;
    return cnt >= k;
}

int parametricSearch(vector<int>& cables, int k) {
    long long lo = 1, hi = *max_element(cables.begin(), cables.end());
    long long ans = 0;
    
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        
        if (canMake(cables, mid, k)) {
            ans = mid;      // 가능하면 더 큰 값 시도
            lo = mid + 1;
        } else {
            hi = mid - 1;   // 불가능하면 줄이기
        }
    }
    return ans;
}
```

## 🎯 Parametric Search 패턴
| 조건 | lo/hi 업데이트 |
|------|----------------|
| 최솟값 찾기 (가능하면 줄이기) | `if (ok) hi = mid - 1, ans = mid` |
| 최댓값 찾기 (가능하면 늘리기) | `if (ok) lo = mid + 1, ans = mid` |

## 🐍 Python
```python
from bisect import bisect_left, bisect_right

arr = [1, 2, 2, 2, 3, 4]

lb = bisect_left(arr, 2)   # 1
ub = bisect_right(arr, 2)  # 4
count = ub - lb            # 3

# Parametric Search
def can_make(cables, length, k):
    return sum(c // length for c in cables) >= k

def solve(cables, k):
    lo, hi = 1, max(cables)
    ans = 0
    while lo <= hi:
        mid = (lo + hi) // 2
        if can_make(cables, mid, k):
            ans = mid
            lo = mid + 1
        else:
            hi = mid - 1
    return ans
```

## 📖 외부 자료
- [Binary Search - CP Algorithms](https://cp-algorithms.com/num_methods/binary_search.html)
- [Parametric Search 설명 - Blog](https://blog.encrypted.gg/923)
- [STL Binary Search 함수들](https://en.cppreference.com/w/cpp/algorithm/lower_bound)

## 📚 연습 문제
- [BOJ 1920 수 찾기](https://www.acmicpc.net/problem/1920) ⭐ 기본
- [BOJ 10816 숫자 카드 2](https://www.acmicpc.net/problem/10816) ⭐ lower/upper_bound
- [BOJ 1654 랜선 자르기](https://www.acmicpc.net/problem/1654) ⭐⭐ Parametric
- [BOJ 2805 나무 자르기](https://www.acmicpc.net/problem/2805) ⭐⭐ Parametric
- [BOJ 2110 공유기 설치](https://www.acmicpc.net/problem/2110) ⭐⭐⭐
