# Mo's Algorithm

## 📌 개념
**오프라인 쿼리 처리** 기법.
쿼리를 재정렬하여### 💡 Mo's Algorithm 동작
쿼리들을 **특정 순서로 정렬**하여 처리함으로써 포인터 이동 최소화.
1. 구간 `[s, e]`를 `s / √N` (블록 번호) 기준으로 정렬
2. 블록 같으면 `e` 기준으로 정렬
3. **투 포인터**처럼 `L`, `R` 이동하며 답 갱신

### 🎓 실전 팁
1. **오프라인 쿼리**: 모든 쿼리를 다 받고 나서 재배치해야 함 (실시간 불가)
2. **제곱근 분할법**: 블록 크기 K = √N 또는 N/√Q 로 설정
3. **Add/Remove 함수**: 원소 하나 추가/제거 시 답 갱신을 O(1) 또는 빠르게 처리해야 함
4. **힐베르트 곡선 정렬**: 단순 정렬보다 더 빠를 수 있음 (캐시 효율): O((N + Q) × √N)

---

## ⏱️ 시간복잡도: O((N + Q) × √N)

---

## 💻 구현
```cpp
int BLOCK;  // √N

struct Query {
    int l, r, idx;
    bool operator<(const Query& o) const {
        if (l / BLOCK != o.l / BLOCK) return l < o.l;
        return (l / BLOCK & 1) ? r > o.r : r < o.r;  // 지그재그 정렬
    }
};

int arr[MAX], cnt[MAX], answer[MAX];
int curL = 0, curR = -1, curAns = 0;

void add(int idx) {
    int x = arr[idx];
    if (cnt[x] == 0) curAns++;  // 예: 서로 다른 수 개수
    cnt[x]++;
}

void remove(int idx) {
    int x = arr[idx];
    cnt[x]--;
    if (cnt[x] == 0) curAns--;
}

void solve(vector<Query>& queries) {
    BLOCK = sqrt(n) + 1;
    sort(queries.begin(), queries.end());
    
    for (auto& q : queries) {
        while (curL > q.l) add(--curL);
        while (curR < q.r) add(++curR);
        while (curL < q.l) remove(curL++);
        while (curR > q.r) remove(curR--);
        
        answer[q.idx] = curAns;
    }
}
```

---

## 📚 연습 문제
- [BOJ 13547 수열과 쿼리 5](https://www.acmicpc.net/problem/13547) ⭐⭐⭐⭐
- [BOJ 8462 배열의 힘](https://www.acmicpc.net/problem/8462) ⭐⭐⭐⭐⭐
- [BOJ 13546 수열과 쿼리 4](https://www.acmicpc.net/problem/13546) ⭐⭐⭐⭐⭐
