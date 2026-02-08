# Disjoint Set Union (Union-Find)
class DSU:
    def __init__(self, n):
        self.parent = list(range(n + 1))
        self.size = [1] * (n + 1)
        
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x]) # 경로 압축
        return self.parent[x]
    
    def unite(self, a, b):
        root_a = self.find(a)
        root_b = self.find(b)
        
        if root_a == root_b:
            return False
        
        # Union by Size
        if self.size[root_a] < self.size[root_b]:
            root_a, root_b = root_b, root_a
            
        self.parent[root_b] = root_a
        self.size[root_a] += self.size[root_b]
        return True
    
    def same(self, a, b):
        return self.find(a) == self.find(b)
        
    def get_size(self, x):
        return self.size[self.find(x)]
