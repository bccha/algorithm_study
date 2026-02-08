import sys
sys.setrecursionlimit(10**6)

class SegmentTree:
    def __init__(self, n, arr):
        self.n = n
        self.tree = [0] * (4 * n)
        self.init(arr, 1, 1, n)
        
    def init(self, arr, node, start, end):
        if start == end:
            self.tree[node] = arr[start] # arr should be 1-indexed usually
            return
        
        mid = (start + end) // 2
        self.init(arr, node * 2, start, mid)
        self.init(arr, node * 2 + 1, mid + 1, end)
        self.tree[node] = self.tree[node * 2] + self.tree[node * 2 + 1]
        
    def query(self, node, start, end, left, right):
        if left > end or right < start:
            return 0
        
        if left <= start and end <= right:
            return self.tree[node]
            
        mid = (start + end) // 2
        return self.query(node * 2, start, mid, left, right) + \
               self.query(node * 2 + 1, mid + 1, end, left, right)
               
    def update(self, node, start, end, idx, diff):
        if idx < start or idx > end:
            return
            
        self.tree[node] += diff
        
        if start != end:
            mid = (start + end) // 2
            self.update(node * 2, start, mid, idx, diff)
            self.update(node * 2 + 1, mid + 1, end, idx, diff)
