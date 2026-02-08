import sys
sys.setrecursionlimit(10**6)

class LazySegmentTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (4 * n)
        self.lazy = [0] * (4 * n)
        
    def propagate(self, node, start, end):
        if self.lazy[node] != 0:
            self.tree[node] += (end - start + 1) * self.lazy[node]
            if start != end:
                self.lazy[node * 2] += self.lazy[node]
                self.lazy[node * 2 + 1] += self.lazy[node]
            self.lazy[node] = 0
            
    def update(self, node, start, end, left, right, val):
        self.propagate(node, start, end)
        
        if left > end or right < start:
            return
            
        if left <= start and end <= right:
            self.lazy[node] += val
            self.propagate(node, start, end)
            return
            
        mid = (start + end) // 2
        self.update(node * 2, start, mid, left, right, val)
        self.update(node * 2 + 1, mid + 1, end, left, right, val)
        self.tree[node] = self.tree[node * 2] + self.tree[node * 2 + 1]
        
    def query(self, node, start, end, left, right):
        self.propagate(node, start, end)
        
        if left > end or right < start:
            return 0
        
        if left <= start and end <= right:
            return self.tree[node]
            
        mid = (start + end) // 2
        return self.query(node * 2, start, mid, left, right) + \
               self.query(node * 2 + 1, mid + 1, end, left, right)
