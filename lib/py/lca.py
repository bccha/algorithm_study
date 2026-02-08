import sys
sys.setrecursionlimit(10**6)

LOG = 20
class LCA:
    def __init__(self, n, adj, root=1):
        self.n = n
        self.adj = adj
        self.parent = [[0] * LOG for _ in range(n + 1)]
        self.depth = [0] * (n + 1)
        
        self._dfs(root, 0, 0)
        self._build()
        
    def _dfs(self, cur, p, d):
        self.depth[cur] = d
        self.parent[cur][0] = p
        for nxt in self.adj[cur]:
            if nxt != p:
                self._dfs(nxt, cur, d + 1)
                
    def _build(self):
        for j in range(1, LOG):
            for i in range(1, self.n + 1):
                if self.parent[i][j-1] != 0:
                    self.parent[i][j] = self.parent[self.parent[i][j-1]][j-1]
                    
    def query(self, u, v):
        if self.depth[u] < self.depth[v]:
            u, v = v, u
            
        # 깊이 맞추기
        for j in range(LOG - 1, -1, -1):
            if self.depth[u] - (1 << j) >= self.depth[v]:
                u = self.parent[u][j]
                
        if u == v: return u
        
        # 공통 조상 찾기
        for j in range(LOG - 1, -1, -1):
            if self.parent[u][j] != self.parent[v][j]:
                u = self.parent[u][j]
                v = self.parent[v][j]
                
        return self.parent[u][0]
        
    def dist(self, u, v):
        return self.depth[u] + self.depth[v] - 2 * self.depth[self.query(u, v)]
