# Lazy Propagation

## 📌 개념
세그먼트 트리에서 **구간 업데이트**를 O(logN)에 처리.
갱신을 미루고(lazy) 필요할 때만 전파.

### 🔍 왜 필요한가?
기본 세그먼트 트리로 구간 [L, R]에 값을 더하려면:
- 각 원소마다 update() 호출 → O((R-L+1) × logN)
- 구간이 크면 **너무 느림!**

**Lazy Propagation 해결책:**
- 구간 업데이트를 **한 번에** 처리 → O(logN)
- "나중에 처리할게~" 메모(lazy)를 남기고 필요할 때 전파

### 💡 핵심 아이디어
1. **Lazy 배열**: 아직 자식에게 전파되지 않은 업데이트 저장
2. **지연 전파**: 노드 방문 시 lazy 값을 자식에게 전파
3. **구간 완전 포함 시**: lazy만 표시하고 더 내려가지 않음 (핵심!)

---

## 💻 구간 덧셈 + 구간 합
```cpp
long long tree[4 * MAX], lazy[4 * MAX];

void propagate(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// [left, right] 구간에 val 더하기
void update(int node, int start, int end, int left, int right, long long val) {
    propagate(node, start, end);
    
    if (right < start || end < left) return;
    
    if (left <= start && end <= right) {
        lazy[node] += val;
        propagate(node, start, end);
        return;
    }
    
    int mid = (start + end) / 2;
    update(2*node, start, mid, left, right, val);
    update(2*node+1, mid+1, end, left, right, val);
    tree[node] = tree[2*node] + tree[2*node+1];
}

// [left, right] 구간 합
long long query(int node, int start, int end, int left, int right) {
    propagate(node, start, end);
    
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return tree[node];
    
    int mid = (start + end) / 2;
    return query(2*node, start, mid, left, right) +
           query(2*node+1, mid+1, end, left, right);
}
```

---

## 💻 구간 대입 (Range Assign)
```cpp
// lazy[node] = 해당 구간에 대입할 값 (0이면 없음으로 처리 시 주의)
const long long NONE = LLONG_MIN;  // 대입 없음 표시

void propagate(int node, int start, int end) {
    if (lazy[node] != NONE) {
        tree[node] = (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[2*node] = lazy[node];
            lazy[2*node+1] = lazy[node];
        }
        lazy[node] = NONE;
    }
}
```

---

## 🎯 핵심 아이디어
1. **Lazy 배열**: 아직 전파되지 않은 업데이트 저장
2. **Propagate**: 노드 방문 시 자식에게 전파
3. **호출 순서**: propagate → 실제 작업

---

---

## 💡 구체적 예시
```
배열: [1, 2, 3, 4, 5]
쿼리 1: 구간 [1, 3]에 +10 (결과: [1, 12, 13, 14, 5])
쿼리 2: 구간 [2, 4]의 합? (답: 13+14+5 = 32)
```

**Lazy Propagation 동작:**
1. `update(0, 0, 4, 1, 3, 10)` 호출
2. 구간 [1,3]을 커버하는 노드들의 lazy에 +10 표시
3. 나중에 `query(0, 0, 4, 2, 4)` 호출 시 lazy 전파하여 정확한 값 계산

### ⚠️ 주의사항
1. **propagate() 필수**: 모든 함수 시작에서 호출!
2. **lazy 초기화**: build() 시 lazy를 0으로 초기화
3. **구간 대입 vs 구간 덧셈**: lazy 의미가 다름 (덧셈: 누적, 대입: 덮어쓰기)
4. **오버플로우**: long long 사용

### 🎓 실전 팁
- **처음엔 구간 덧셈**만 구현 (BOJ 10999)
- 구간 대입은 NONE 값으로 "아직 안함" 표시
- 디버깅: propagate()가 잘 작동하는지 먼저 확인

---

## 📚 연습 문제
- [BOJ 10999 구간 합 구하기 2](https://www.acmicpc.net/problem/10999) ⭐⭐⭐⭐ 기본
- [BOJ 12844 XOR](https://www.acmicpc.net/problem/12844) ⭐⭐⭐⭐
- [BOJ 1395 스위치](https://www.acmicpc.net/problem/1395) ⭐⭐⭐⭐
- [BOJ 16404 주식회사 승범이네](https://www.acmicpc.net/problem/16404) ⭐⭐⭐⭐
