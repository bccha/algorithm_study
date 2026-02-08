# 펜윅 트리 (Fenwick Tree / BIT)

## 📌 개념
**Binary Indexed Tree** - 세그먼트 트리보다 구현이 간단.
구간 합 쿼리에 특화.

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**구간 합** + **업데이트**"
### 💡 에드몬드-카프 (BFS)
1. BFS로 소스→싱크 경로 찾기 (잔여 용량 > 0 인 간선만)
2. 경로 중 최소 용량(flow) 찾기
3. 경로의 간선들에 flow 추가, 역방향 간선에 flow 빼기 (음수 유량)
4. 경로 없을 때까지 반복

### 🎓 실전 팁
1. **이분 매칭**: 최대 유량의 특수한 형태 (용량 모두 1)
2. **Dinic 알고리즘**: 정점이 많으면 에드몬드-카프보다 훨씬 빠름 (레벨 그래프 사용)
3. **최소 컷(Min-Cut)**: 최대 유량 = 최소 컷 (Max-Flow Min-Cut Theorem)
4. **역방향 간선**: 반드시 만들어야 함! (취소 가능성 열어두기)
- "역순 쌍 개수" (Inversion Count)
### 💡 펜윅 트리 동작 원리
- **i번째 값**: 원본 배열 값이 아니라, 특정 구간의 부분합을 저장
- `i & -i`: 마지막 1의 위치 (LSB)를 이용하여 부모/자식 이동
- **Update**: `idx`에 더하고, `idx += (idx & -idx)`로 올라가며 갱신
- **Query**: `idx`까지 합 구하고, `idx -= (idx & -idx)`로 내려가며 누적

### 🎓 실전 팁
1. **1-indexed**: 구현이 훨씬 편함 (0인덱스 쓰면 +1 해줘야 함)
2. **구간 합 구하기**: `query(R) - query(L-1)`
3. **Inversion Counting**: 값의 범위가 크면 **좌표 압축** 후 펜윅 트리 사용
4. **2차원 펜윅**: 2중 for문으로 확장 가능 (구현 간단)
- 업데이트: O(logN)
- 쿼리: O(logN)

---

## 💻 구현
```cpp
int tree[MAX];
int n;

// idx 위치에 delta 더하기
void update(int idx, int delta) {
    for (; idx <= n; idx += idx & (-idx))
        tree[idx] += delta;
}

// 1~idx 구간 합
long long sum(int idx) {
    long long ret = 0;
    for (; idx > 0; idx -= idx & (-idx))
        ret += tree[idx];
    return ret;
}

// [left, right] 구간 합
long long rangeSum(int left, int right) {
    return sum(right) - sum(left - 1);
}
```

---

## 💡 핵심 원리
- `idx & (-idx)` : 가장 낮은 1비트 (LSB)
- 업데이트: LSB를 더하면서 위로 이동
- 쿼리: LSB를 빼면서 아래로 이동

```
예: n = 8
tree[1] = arr[1]
tree[2] = arr[1] + arr[2]
tree[3] = arr[3]
tree[4] = arr[1] + arr[2] + arr[3] + arr[4]
tree[5] = arr[5]
tree[6] = arr[5] + arr[6]
tree[7] = arr[7]
tree[8] = arr[1] + ... + arr[8]
```

---

## 🐍 Python
```python
tree = [0] * (n + 1)

def update(idx, delta):
    while idx <= n:
        tree[idx] += delta
        idx += idx & (-idx)

def prefix_sum(idx):
    ret = 0
    while idx > 0:
        ret += tree[idx]
        idx -= idx & (-idx)
    return ret

def range_sum(left, right):
    return prefix_sum(right) - prefix_sum(left - 1)
```

---

## 🎯 응용: Inversion Count
```cpp
// 역순 쌍 개수 세기
long long countInversions(vector<int>& arr) {
    // 좌표 압축 후 진행
    long long inv = 0;
    for (int i = arr.size() - 1; i >= 0; i--) {
        inv += sum(arr[i] - 1);  // 나보다 작은 수 중 이미 등장한 것
        update(arr[i], 1);
    }
    return inv;
}
```

---

## 📖 외부 자료
- [Fenwick Tree - CP Algorithms](https://cp-algorithms.com/data_structures/fenwick.html)
- [BIT 시각화](https://visualgo.net/en/fenwicktree)

## 📚 연습 문제
- [BOJ 2042 구간 합 구하기](https://www.acmicpc.net/problem/2042) ⭐⭐⭐
- [BOJ 1517 버블 소트](https://www.acmicpc.net/problem/1517) ⭐⭐⭐ Inversion
- [BOJ 12837 가계부](https://www.acmicpc.net/problem/12837) ⭐⭐
- [BOJ 3653 영화 수집](https://www.acmicpc.net/problem/3653) ⭐⭐⭐
