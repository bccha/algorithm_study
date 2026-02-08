import heapq

INF = float('inf')

# 다익스트라
def dijkstra(start, n, adj):
    dist = [INF] * (n + 1)
    dist[start] = 0
    pq = [(0, start)] # (거리, 노드)
    
    while pq:
        d, cur = heapq.heappop(pq)
        
        if d > dist[cur]:
            continue
            
        for nxt, weight in adj[cur]:
            if dist[cur] + weight < dist[nxt]:
                dist[nxt] = dist[cur] + weight
                heapq.heappush(pq, (dist[nxt], nxt))
                
    return dist

# 벨만-포드 edges = [(u, v, w), ...]
def bellman_ford(start, n, edges):
    dist = [INF] * (n + 1)
    dist[start] = 0
    
    # N-1번 완화
    for _ in range(n - 1):
        for u, v, w in edges:
            if dist[u] != INF and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                
    # 음수 사이클 확인
    has_negative_cycle = False
    for u, v, w in edges:
        if dist[u] != INF and dist[u] + w < dist[v]:
            has_negative_cycle = True
            break
            
    return dist, has_negative_cycle

# 플로이드-워셜
# dist 초기화 주의: 연결 없으면 INF, 자기 자신 0
def floyd_warshall(n, dist):
    for k in range(1, n + 1):
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if dist[i][k] != INF and dist[k][j] != INF:
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    return dist
