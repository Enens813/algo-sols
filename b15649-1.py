def backtrack(N, M, sequence, visited):
    if len(sequence) == M:
        print(" ".join(map(str, sequence)))
        return
    
    for num in range(1, N + 1):
        if not visited[num]:
            visited[num] = True
            backtrack(N, M, sequence + [num], visited)
            visited[num] = False

# 입력 받기
N, M = map(int, input().split())
visited = [False] * (N + 1)
backtrack(N, M, [], visited)