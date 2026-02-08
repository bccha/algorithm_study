# Fenwick Tree (Binary Indexed Tree)
# 1-indexed
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
        
    def update(self, idx, val):
        while idx <= self.n:
            self.tree[idx] += val
            idx += (idx & -idx)
            
    def query(self, idx):
        sum_val = 0
        while idx > 0:
            sum_val += self.tree[idx]
            idx -= (idx & -idx)
        return sum_val
        
    def query_range(self, left, right):
        return self.query(right) - self.query(left - 1)
