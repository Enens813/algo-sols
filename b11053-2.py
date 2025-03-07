import sys

def lis_dp(arr):
    n = len(arr)
    dp = [1] * n  # 모든 원소는 최소 길이 1의 부분 수열이 됨

    for i in range(n):
        for j in range(i):
            if arr[j] < arr[i]:
                dp[i] = max(dp[i], dp[j] + 1)

    return max(dp)  # LIS의 길이 반환

n = int(sys.stdin.readline().strip())
arr = list(map(int, sys.stdin.readline().split()))
print(lis_dp(arr))
