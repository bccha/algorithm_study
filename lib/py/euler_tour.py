import sys
sys.setrecursionlimit(10**6)

class EulerTour:
    def __init__(self, n, adj, root=1):
        self.in_time = [0] * (n + 1)
        self.out_time = [0] * (n + 1)
        self.timer = 0
        self.adj = adj
        self._dfs(root, 0)
        
    def _dfs(self, cur, p):
        self.timer += 1
        self.in_time[cur] = self.timer
        for nxt in self.adj[cur]:
            if nxt != p:
                self._dfs(nxt, cur)
        self.out_time[cur] = self.timer
        
    def is_ancestor(self, u, v):
        return self.in_time[u] <= self.in_time[v] and \
               self.out_time[v] <= self.out_time[u]
