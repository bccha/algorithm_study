import heapq

# DSU 클래스 필요
class DSU:
    def __init__(self, n):
        self.parent = list(range(n + 1))
    def find(self, x):
        if self.parent[x] != x: self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    def unite(self, a, b):
        root_a, root_b = self.find(a), self.find(b)
        if root_a == root_b: return False
        self.parent[root_b] = root_a
        return True

# Kruskal 알고리즘 edges = [(u, v, w), ...]
def kruskal(n, edges):
    edges.sort(key=lambda x: x[2]) # 가중치 기준 정렬
    dsu = DSU(n)
    total_weight = 0
    count = 0
    
    for u, v, w in edges:
        if dsu.unite(u, v):
            total_weight += w
            count += 1
            
    if count < n - 1: return -1 # 연결 안됨
    return total_weight

# Prim 알고리즘
def prim(n, start, adj):
    visited = [False] * (n + 1)
    pq = [(0, start)]
    total_weight = 0
    count = 0
    
    while pq:
        w, cur = heapq.heappop(pq)
        
        if visited[cur]: continue
        visited[cur] = True
        total_weight += w
        count += 1
        
        for nxt, weight in adj[cur]:
            if not visited[nxt]:
                heapq.heappush(pq, (weight, nxt))
                
    if count < n: return -1
    return total_weight
