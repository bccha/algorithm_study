from collections import deque

class Dinic:
    def __init__(self, n):
        self.n = n
        self.adj = [[] for _ in range(n + 1)]
        self.level = []
        
    def add_edge(self, u, v, cap):
        # [to, cap, flow, rev_index]
        self.adj[u].append([v, cap, 0, len(self.adj[v])])
        self.adj[v].append([u, 0, 0, len(self.adj[u]) - 1])
        
    def bfs(self, s, t):
        self.level = [-1] * (self.n + 1)
        self.level[s] = 0
        q = deque([s])
        while q:
            cur = q.popleft()
            for v, cap, flow, rev in self.adj[cur]:
                if cap - flow > 0 and self.level[v] == -1:
                    self.level[v] = self.level[cur] + 1
                    q.append(v)
        return self.level[t] != -1
        
    def dfs(self, cur, t, pushed, ptr):
        if pushed == 0 or cur == t:
            return pushed
            
        for i in range(ptr[cur], len(self.adj[cur])):
            ptr[cur] = i
            v, cap, flow, rev = self.adj[cur][i]
            
            if self.level[v] != self.level[cur] + 1 or cap - flow == 0:
                continue
                
            tr = self.dfs(v, t, min(pushed, cap - flow), ptr)
            if tr == 0: continue
            
            self.adj[cur][i][2] += tr # flow update
            self.adj[v][rev][2] -= tr # rev flow update
            return tr
            
        return 0
        
    def max_flow(self, s, t):
        flow = 0
        while self.bfs(s, t):
            ptr = [0] * (self.n + 1)
            while True:
                pushed = self.dfs(s, t, float('inf'), ptr)
                if pushed == 0: break
                flow += pushed
        return flow
