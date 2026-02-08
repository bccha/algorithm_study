from collections import deque

# DFS (재귀)
def dfs(cur, adj, visited):
    visited[cur] = True
    print(cur, end=' ')
    for nxt in adj[cur]:
        if not visited[nxt]:
            dfs(nxt, adj, visited)

# BFS (큐)
def bfs(start, adj, visited):
    q = deque([start])
    visited[start] = True
    
    while q:
        cur = q.popleft()
        print(cur, end=' ')
        
        for nxt in adj[cur]:
            if not visited[nxt]:
                visited[nxt] = True
                q.append(nxt)

# 위상 정렬
def topological_sort(n, adj, indegree):
    q = deque([i for i in range(1, n + 1) if indegree[i] == 0])
    result = []
    
    while q:
        cur = q.popleft()
        result.append(cur)
        
        for nxt in adj[cur]:
            indegree[nxt] -= 1
            if indegree[nxt] == 0:
                q.append(nxt)
                
    if len(result) != n:
        return [] # 사이클 존재
    return result
