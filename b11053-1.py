import sys
import bisect

def lis_binary_search(arr):
    lis = []  # LIS 배열 (길이만 알면 되므로 원소 유지 X)

    for num in arr:
        pos = bisect.bisect_left(lis, num)  # 이분 탐색으로 적절한 위치 찾기
        if pos == len(lis):
            lis.append(num)  # 가장 큰 숫자면 추가
        else:
            lis[pos] = num  # 더 작은 값으로 대체 (길이 유지)

    return len(lis)

n = int(sys.stdin.readline().strip())
arr = list(map(int, sys.stdin.readline().split()))
print(lis_binary_search(arr))
