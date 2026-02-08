# 세그먼트 트리 (Segment Tree)

## 📌 개념
**구간 쿼리**를 O(logN)에 처리하는 자료구조.
- 구간 합, 최솟값, 최댓값, GCD 등
- Binary Indexed Tree(Fenwick)보다 범용적

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**구간 [L, R]의 합/최소/최대**를 Q번 질의"
- "값을 **변경**하면서 구간 쿼리"
- "동적으로 업데이트되는 배열의 구간 정보"

### Segment Tree vs Fenwick Tree
| 특성 | Segment Tree | Fenwick Tree |
|------|--------------|-------------|
| 구간 합 | ✅ | ✅ (더 빠름) |
| 구간 min/max/gcd | ✅ | ❌ |
| 구간 업데이트 | ✅ (Lazy) | 어려움 |
| 구현 난이도 | 중 | 쉬움 |

### 주의사항
- 트리 크기: `4 * n` (여유있게)
- 1-indexed vs 0-indexed 주의
- merge 연산 정의 (합? min? max? gcd?)

## ⏱️ 시간복잡도
- 빌드: O(N)
- 쿼리: O(logN)
- 업데이트: O(logN)

---

## 💻 구간 합 세그먼트 트리
```cpp
int tree[4 * MAX];
int arr[MAX];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

// [left, right] 구간 합
long long query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return 0;  // 범위 밖
    if (left <= start && end <= right) return tree[node];  // 완전 포함
    
    int mid = (start + end) / 2;
    return query(2*node, start, mid, left, right) +
           query(2*node+1, mid+1, end, left, right);
}

// idx 위치를 diff만큼 변경
void update(int node, int start, int end, int idx, long long diff) {
    if (idx < start || end < idx) return;
    
    tree[node] += diff;
    
    if (start != end) {
        int mid = (start + end) / 2;
        update(2*node, start, mid, idx, diff);
        update(2*node+1, mid+1, end, idx, diff);
    }
}
```

---

## 💻 구간 최솟값
```cpp
int tree[4 * MAX];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }
}

int query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) return INF;
    if (left <= start && end <= right) return tree[node];
    
    int mid = (start + end) / 2;
    return min(query(2*node, start, mid, left, right),
               query(2*node+1, mid+1, end, left, right));
}
```

---

## 🐍 Python
```python
tree = [0] * (4 * n)

def build(node, start, end):
    if start == end:
        tree[node] = arr[start]
    else:
        mid = (start + end) // 2
        build(2*node, start, mid)
        build(2*node+1, mid+1, end)
        tree[node] = tree[2*node] + tree[2*node+1]

def query(node, start, end, left, right):
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]
    mid = (start + end) // 2
    return query(2*node, start, mid, left, right) + \
           query(2*node+1, mid+1, end, left, right)
```

---

## 💡 구체적 예시: 구간 합 세그먼트 트리
```
배열: [1, 3, 5, 7, 9, 11]
구간 합 트리:

          tree[1] = 36 (전체 합)
         /                    \
    tree[2]=9            tree[3]=27
     /    \               /      \
 tree[4]=1  tree[5]=8  tree[6]=16  tree[7]=11
             /    \       /    \
           3      5     7      9
```

**쿼리 [1,4]의 합? (3+5+7+9 = 24)**
1. node 1: 구간 [0,5], 부분 교집합 → 자식 탐색
2. node 2: 구간 [0,2], [1,4]와 [1,2] 교집합 → tree[5] = 8 사용
3. node 3: 구간 [3,5], [1,4]와 [3,4] 교집합 → 16에서 일부만...
4. 최종: 8 + 7 + 9 = 24

### 🎓 실전 팁
1. **트리 크기 4*N**: 안전하게 넉넉히 잡기
2. **1-indexed vs 0-indexed**: 함수 호출 시 주의!
3. **merge 함수 정의**: 합? min? max? 명확히
4. **init 안 하면**: 쓰레기 값 나옴, memset 또는 fill 필수
5. **디버깅**: 트리 전체 출력해서 구조 확인

---

## 📖 외부 자료
- [Segment Tree - CP Algorithms](https://cp-algorithms.com/data_structures/segment_tree.html)
- [세그먼트 트리 강의 - Blog](https://blog.encrypted.gg/category/강좌/자료구조)
- [VisuAlgo - Segment Tree 시각화](https://visualgo.net/en/segmenttree)

## 📚 연습 문제
- [BOJ 2042 구간 합 구하기](https://www.acmicpc.net/problem/2042) ⭐⭐⭐ 기본
- [BOJ 10868 최솟값](https://www.acmicpc.net/problem/10868) ⭐⭐⭐
- [BOJ 2357 최솟값과 최댓값](https://www.acmicpc.net/problem/2357) ⭐⭐⭐
- [BOJ 11505 구간 곱 구하기](https://www.acmicpc.net/problem/11505) ⭐⭐⭐
- [BOJ 2243 사탕상자](https://www.acmicpc.net/problem/2243) ⭐⭐⭐⭐
