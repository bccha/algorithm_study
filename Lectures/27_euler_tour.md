# 오일러 투어 테크닉 (Euler Tour Technique)

## 📌 개념
트리를 DFS 순서로 펼쳐서 **서브트리를### 💡 오일러 경로 테크닉 (ETT)
DFS 방문 순서(진입/진출)를 기록하여 트리를 **1차원 배열**로 펼침.
- `in[u]`: 서브트리 시작 인덱스
- `out[u]`: 서브트리 끝 인덱스
- → **u의 서브트리** = 배열의 구간 `[in[u], out[u]]`

### 🎓 실전 팁
1. **서브트리 쿼리**: 트리를 배열 구간으로 바꾸면 세그먼트/펜윅 트리 사용 가능!
2. **경로 쿼리**: LCA와 결합하여 경로 처리 가능
3. **LCA 구현**: ETT + RMQ(Range Minimum Query)로 O(1) LCA 가능
4. **배열 크기**: DFS 방문 시 카운트 증가시키며 기록

## 💻 구현
```cpp
int in_[MAX], out_[MAX];  // 진입/탈출 시간
int order[MAX];  // 오일러 투어 순서대로 정점
int timer;

void euler_tour(int cur, int parent) {
    in_[cur] = ++timer;
    order[timer] = cur;
    
    for (int next : adj[cur]) {
        if (next != parent) {
            euler_tour(next, cur);
        }
    }
    out_[cur] = timer - 1;
}

// 정점 v의 서브트리 = 구간 [in_[v], out_[v]]
// 세그먼트 트리로 구간 합/업데이트 가능
```

---

## 🎯 활용 예시
```cpp
// 서브트리 v의 모든 값에 x 더하기
void addSubtree(int v, int x) {
    segUpdate(in_[v], out_[v], x);  // 구간 업데이트
}

// 정점 v의 값 조회
int getValue(int v) {
    return segQuery(in_[v]);  // 점 쿼리
}
```

---

## 📚 연습 문제
- [BOJ 14268 회사 문화 2](https://www.acmicpc.net/problem/14268) ⭐⭐⭐⭐
- [BOJ 18437 회사 문화 5](https://www.acmicpc.net/problem/18437) ⭐⭐⭐⭐
- [BOJ 2820 자동차 공장](https://www.acmicpc.net/problem/2820) ⭐⭐⭐⭐⭐
