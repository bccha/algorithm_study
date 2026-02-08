# Suffix Array (O(Nlog^2N))
def get_suffix_array(s):
    n = len(s)
    sa = list(range(n))
    rank = [ord(c) for c in s]
    d = 1
    
    while d < n:
        # key function for sort
        def key_func(i):
            first = rank[i]
            second = rank[i + d] if i + d < n else -1
            return (first, second)
            
        sa.sort(key=key_func)
        
        new_rank = [0] * n
        new_rank[sa[0]] = 0
        
        for i in range(1, n):
            if key_func(sa[i]) == key_func(sa[i - 1]):
                new_rank[sa[i]] = new_rank[sa[i - 1]]
            else:
                new_rank[sa[i]] = new_rank[sa[i - 1]] + 1
        
        rank = new_rank
        if rank[sa[n - 1]] == n - 1:
            break
        d *= 2
        
    return sa

# LCP Array (Kasai's algorithm)
def get_lcp(s, sa):
    n = len(s)
    rank = [0] * n
    for i in range(n):
        rank[sa[i]] = i
        
    lcp = [0] * n
    h = 0
    for i in range(n):
        if rank[i] > 0:
            j = sa[rank[i] - 1]
            while i + h < n and j + h < n and s[i + h] == s[j + h]:
                h += 1
            lcp[rank[i]] = h
            if h > 0:
                h -= 1
    return lcp
