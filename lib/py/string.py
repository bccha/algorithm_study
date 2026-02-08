# KMP Failure Function
def get_pi(p):
    m = len(p)
    pi = [0] * m
    j = 0
    for i in range(1, m):
        while j > 0 and p[i] != p[j]:
            j = pi[j - 1]
        if p[i] == p[j]:
            j += 1
            pi[i] = j
    return pi

# KMP Search
def kmp(s, p):
    ans = []
    pi = get_pi(p)
    n, m = len(s), len(p)
    j = 0
    for i in range(n):
        while j > 0 and s[i] != p[j]:
            j = pi[j - 1]
        if s[i] == p[j]:
            if j == m - 1:
                ans.append(i - m + 1)
                j = pi[j]
            else:
                j += 1
    return ans

# Trie
class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
        
    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end = True
        
    def search(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end
