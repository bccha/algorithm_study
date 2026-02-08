import sys
sys.setrecursionlimit(10**6)

class HLD:
    def __init__(self, n, adj, root=1):
        self.n = n
        self.adj = adj
        self.parent = [0] * (n + 1)
        self.depth = [0] * (n + 1)
        self.heavy = [0] * (n + 1)
        self.head = [0] * (n + 1)
        self.pos = [0] * (n + 1)
        self.cur_pos = 0
        
        self.parent[root] = 0
        self.depth[root] = 0
        self._dfs(root)
        self._decompose(root, root)
        
    def _dfs(self, v):
        size = 1
        max_c_size = 0
        for c in self.adj[v]:
            if c != self.parent[v]:
                self.parent[c] = v
                self.depth[c] = self.depth[v] + 1
                c_size = self._dfs(c)
                size += c_size
                if c_size > max_c_size:
                    max_c_size = c_size
                    self.heavy[v] = c
        return size
    
    def _decompose(self, v, h):
        self.head[v] = h
        self.pos[v] = self.cur_pos
        self.cur_pos += 1
        
        if self.heavy[v] != 0:
            self._decompose(self.heavy[v], h)
            
        for c in self.adj[v]:
            if c != self.parent[v] and c != self.heavy[v]:
                self._decompose(c, c)
                
    # 경로 쿼리 템플릿
    # def query(self, u, v):
    #     res = 0
    #     while self.head[u] != self.head[v]:
    #         if self.depth[self.head[u]] > self.depth[self.head[v]]:
    #             u, v = v, u
    #         # res += seg.query(self.pos[self.head[v]], self.pos[v])
    #         v = self.parent[self.head[v]]
    #     if self.depth[u] > self.depth[v]:
    #         u, v = v, u
    #     # res += seg.query(self.pos[u], self.pos[v])
    #     return res
