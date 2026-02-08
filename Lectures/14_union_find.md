# 유니온 파인드 (Union-Find / DSU)

## 📌 개념
**서로소 집합(Disjoint Set)**을 관리하는 자료구조.
- **Union**: 두 집합 합치기
- **Find**: 원소가 속한 집합(대표) 찾기

## 🎯 언제 사용하나?
### 문제에서 이렇게 나옵니다
- "**두 원소가 같은 집합**에 속하는지 판별"
- "**동적으로 그룹** 합치기"
- "**연결 요소/친구 관계** 관리"
- "**사이클 판별**" (Kruskal MST)
- "친구 네트워크 크기" → Union-Find + 크기 추적

## ⏱️ 시간복잡도
- 경로 압축 + Union by Rank: 거의 O(1) (정확히는 O(α(N)))

---

## 💻 구현 (경로 압축 + Union by Rank)
```cpp
int parent[MAX], rank_[MAX];

void init(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // 경로 압축
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    
    if (a == b) return;
    
    // Union by Rank
    if (rank_[a] < rank_[b]) swap(a, b);
    parent[b] = a;
    if (rank_[a] == rank_[b]) rank_[a]++;
}

bool isConnected(int a, int b) {
    return find(a) == find(b);
}
```

---

## 💻 간단 버전 (경로 압축만)
```cpp
int parent[MAX];

void init(int n) {
    for (int i = 0; i <= n; i++) parent[i] = i;
}

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int a, int b) {
    parent[find(a)] = find(b);
}
```

---

## 🐍 Python
```python
parent = list(range(n + 1))

def find(x):
    if parent[x] != x:
        parent[x] = find(parent[x])
    return parent[x]

def unite(a, b):
    parent[find(a)] = find(b)
```

---

## 🎯 응용
1. **연결 요소 관리**: 동적으로 간선 추가 시 연결 여부 판별
2. **사이클 판별**: Kruskal MST에서 활용
3. **친구 네트워크**: 집합 크기 관리

### 집합 크기 추적
```cpp
int size_[MAX];

void init(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        size_[i] = 1;
    }
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    
    parent[b] = a;
    size_[a] += size_[b];  // 크기 합치기
}

int getSize(int x) {
    return size_[find(x)];
}
```

---

## 📖 외부 자료
- [Union-Find - CP Algorithms](https://cp-algorithms.com/data_structures/disjoint_set_union.html)
- [DSU 시각화](https://www.cs.usfca.edu/~galles/visualization/DisjointSets.html)

## 📚 연습 문제
- [BOJ 1717 집합의 표현](https://www.acmicpc.net/problem/1717) ⭐⭐ 기본
- [BOJ 1976 여행 가자](https://www.acmicpc.net/problem/1976) ⭐
- [BOJ 4195 친구 네트워크](https://www.acmicpc.net/problem/4195) ⭐⭐ 크기 추적
- [BOJ 20040 사이클 게임](https://www.acmicpc.net/problem/20040) ⭐⭐
- [BOJ 10775 공항](https://www.acmicpc.net/problem/10775) ⭐⭐⭐
