# Heavy-Light Decomposition

### 💡 HLD 아이디어 (Heavy-Light Decomposition)
트리를 **여러 개의 체인(일직선 경로)**으로 분해.
- **Heavy 간선**: 서브트리 크기가 가장 큰 자식으로 가는 간선
- **Light 간선**: 나머지 간선
- → 어떤 경로든 Light 간선은 O(logN)번만 만남!
- 각 체인을 **세그먼트 트리**로 관리하여 경로 쿼리 처리
- 경로 쿼리를 O(log²N)에 처리.

### 🎓 실전 팁
1. **구현 난이도**: 매우 높음. 템플릿 정확히 작성해두고 복사해서 쓰기
2. **LCA와 결합**: 두 노드 사이 경로는 `u -> LCA -> v`
3. **정점 번호 재할당**: DFS 순서(Euler Tour)대로 번호 매겨서 세그먼트 트리에 매핑
4. **쿼리 처리**: `top[u]`와 `top[v]` 비교하며 깊은 쪽을 위로 올리면서 구간 쿼리

---

## 💻 구현
```cpp
int parent[MAX], depth[MAX], sz[MAX];
int chain[MAX], chainHead[MAX], chainPos[MAX];
int chainCnt = 0, pos = 0;

// 1단계: 서브트리 크기 계산
void dfs1(int cur, int par, int d) {
    parent[cur] = par;
    depth[cur] = d;
    sz[cur] = 1;
    
    for (int next : adj[cur]) {
        if (next != par) {
            dfs1(next, cur, d + 1);
            sz[cur] += sz[next];
        }
    }
}

// 2단계: Heavy-Light 분해
void dfs2(int cur, int par, int head) {
    chain[cur] = chainCnt;
    chainHead[cur] = head;
    chainPos[cur] = pos++;
    
    int heavyChild = -1, maxSz = 0;
    for (int next : adj[cur]) {
        if (next != par && sz[next] > maxSz) {
            maxSz = sz[next];
            heavyChild = next;
        }
    }
    
    if (heavyChild != -1)
        dfs2(heavyChild, cur, head);  // Heavy edge 연장
    
    for (int next : adj[cur]) {
        if (next != par && next != heavyChild) {
            chainCnt++;
            dfs2(next, cur, next);  // 새 체인 시작
        }
    }
}

// 경로 쿼리 (세그먼트 트리와 결합)
int queryPath(int u, int v) {
    int result = 0;
    while (chain[u] != chain[v]) {
        if (depth[chainHead[u]] < depth[chainHead[v]]) swap(u, v);
        result += segQuery(chainPos[chainHead[u]], chainPos[u]);
        u = parent[chainHead[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    result += segQuery(chainPos[u], chainPos[v]);
    return result;
}
```

---

## 📚 연습 문제
- [BOJ 13510 트리와 쿼리 1](https://www.acmicpc.net/problem/13510) ⭐⭐⭐⭐⭐
- [BOJ 13511 트리와 쿼리 2](https://www.acmicpc.net/problem/13511) ⭐⭐⭐⭐⭐
