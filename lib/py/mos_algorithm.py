import math

def mos_algorithm(n, arr, queries):
    sqrt_n = int(math.sqrt(n))
    
    # 정렬 (Hilbert variant or even/odd variant)
    def query_sort_key(q):
        l, r, idx = q
        block = l // sqrt_n
        return (block, r if block % 2 == 1 else -r)
        
    queries.sort(key=query_sort_key)
    
    ans = [0] * len(queries)
    cnt = [0] * 1000005
    res = 0
    
    def add(idx):
        nonlocal res
        cnt[arr[idx]] += 1
        if cnt[arr[idx]] == 1:
            res += 1
            
    def remove(idx):
        nonlocal res
        cnt[arr[idx]] -= 1
        if cnt[arr[idx]] == 0:
            res -= 1
            
    l, r = queries[0][0], queries[0][0] - 1
    
    for q_l, q_r, q_idx in queries:
        while l > q_l:
            l -= 1
            add(l)
        while r < q_r:
            r += 1
            add(r)
        while l < q_l:
            remove(l)
            l += 1
        while r > q_r:
            remove(r)
            r -= 1
        ans[q_idx] = res
        
    return ans
