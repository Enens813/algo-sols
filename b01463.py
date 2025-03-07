import sys
from functools import lru_cache

sys.setrecursionlimit(10**6)

@lru_cache(maxsize=10**6)  # 캐시 크기 제한
def min_operations(n):
    if n == 1:
        return 0
    
    # 기본적으로 1을 빼는 연산
    res = min_operations(n - 1) + 1
    
    # 2로 나눌 수 있는 경우
    if n % 2 == 0:
        res = min(res, min_operations(n // 2) + 1)
    
    # 3으로 나눌 수 있는 경우
    if n % 3 == 0:
        res = min(res, min_operations(n // 3) + 1)
    
    return res

n = int(sys.stdin.readline().strip())
print(min_operations(n))
