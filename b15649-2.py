import numpy as np

def generate_permutations(N, M):
    numbers = np.arange(1, N + 1)
    mask = np.ones(N, dtype=bool)  # 마스킹 배열 생성
    
    def permute(matrix, depth):
        if depth == M:
            print(" ".join(map(str, matrix)))
            return
        
        for i in range(N):
            if mask[i]:  # 방문하지 않은 숫자만 선택
                mask[i] = False  # 현재 숫자를 사용함으로 마스킹
                permute(matrix + [numbers[i]], depth + 1)
                mask[i] = True  # 백트래킹: 원래 상태로 복원
    
    permute([], 0)

# 입력 받기
N, M = map(int, input().split())
generate_permutations(N, M)
