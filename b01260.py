from collections import deque

def dfs(graph, v, visited):
    visited[v] = True
    print(v, end=" ")
    
    for neighbor in sorted(graph[v]):  # child node 중 작은 번호부터 방문
        if not visited[neighbor]:
            dfs(graph, neighbor, visited)

def bfs(graph, start):
    visited = {node: False for node in graph}
    queue = deque([start]) # 방문할 리스트
    visited[start] = True
    
    while queue:
        v = queue.popleft()
        print(v, end=" ")
        
        for neighbor in sorted(graph[v]):  # 작은 번호부터 방문
            if not visited[neighbor]:
                queue.append(neighbor) # 방문할 리스트에 모든 자식 노드들 추가
                visited[neighbor] = True

# 입력 받기
n, m, v = map(int, input().split()) # node, edge root. e.g 4, 5, 1
# map : iterator. 한 번에 하나의 요소만 반환. 필요할 때만 값 생성 (lazy evaluation)
graph = {i: set() for i in range(1, n + 1)}

for _ in range(m):
    a, b = map(int, input().split())
    graph[a].add(b)
    graph[b].add(a)  # 양방향 연결

# DFS 실행
visited_dfs = {node: False for node in graph}
dfs(graph, v, visited_dfs)
print()

# BFS 실행
bfs(graph, v)
