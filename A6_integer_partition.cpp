/*
    integer partition(정수/자연수 분할) : 자연수 n을 k개의 자연수의 합으로 나타내는 것. 가능한 방법의 수를 P(n,k)로 나타냄.
    이 자체는 알고리즘은 아니고, 이를 푸는 알고리즘 소개.
    ex. P(n,1) = P(n,n) = 1, P(7,3) = 4 (5+1+1, 4+2+1, 3+3+1, 3+3+2)

    특징1: P(n,k) = P(n-1, k-1) + P(n-k, k)                     <- 1이 있는 경우와 없는 경우로 나눔
    특징2: P(n,k) = P(n-k, 1) + P(n-k, 2) + ... + P(n-k, k)     <- 일단 1을 k개에 다 균일하게 분배 후, 나머지(n-k)를 나눔.

    P(n) = P(n,1) + P(n,2) + ... + P(n, n)                    <- n을 몇개로든 나눌 수 있는 방법의 수

    유사한 개념으로 set partition(집합 분할)이 있음
    set partition : n개의 원소를 가진 집합을 k개의 부분집합으로 나누는 것. 가능한 경우의 수를 S(n,k)로 나타냄.
    ex. S(3,2) = 3 ({1}+{2,3}, {1,2}+{3}, {1,3}+{2})

    특징1: S(n,k) = S(n-1, k-1) + k * S(n-1, k)                 <- 특정 원소 x가 단독으로 있을 지(남은 n-1개로 k-1개를 만듦), 아닐지(n-1개로 k개를 만든 다음 x가 k개중 하나를 골라감)를 기준으로 두개로 나눈 것. 특정 원소가 무엇이든 상관 없이 값은 똑같음
    특징2: S(n, n-1) = nC2                                      <- 두 원소만 같은 집합 나머지는 단독집합. 그 두 원소 정하는 방법: nC2
    특징3: S(n,2) = 2^(n-1) - 1                                 <- n개 원소마다 둘중 어디로 갈지 정함 (2^n) -> 공집합 제외 (2^n -2) -> 두 집합 구분안됨 (2^n -2)/2 = 2^(n-1)-1
    S(n,k)는 서로 다른 n개를 k개로 나누는 것,
    P(n,k)는 서로 같은 n개를 k개로 나누는 것. (1 n개를 k개로 나눈다고 생각)

    reference: https://blog.naver.com/vollollov/220989048062

    암튼, 아래는 자연수의 분할을 dynamic programming으로 계산하는 방법이다.
    감을 잡아보자면,
    P(4,1) = 1 (4)
    P(4,2) = 2 (3+1, 2+2)
    P(4,3) = 1 (2+1+1)
    P(4,4) = 1 (1+1+1+1)

    점화식을 이용해서 dp로 구하면 O(nk)에 계산 가능하다
*/

#include <iostream>
#include <vector>
using namespace std;

// int P[500000];
const int MOD = 1e9+7;
/*
    mod 사용이유
    
    int는 2e9(2,147,483,647), long long은 9e18까지 가능. 그러나 팩토리얼, 지수 등이 들어간 점화식은 이 범위 초과 가능
    -> 몇 알고리즘 문제는 정답을 M으로 나눈 나머지를 출력하라고 요구함 (overflow 방지)

    1e9+7은 큰 소수이면서 int최대/2보다 작아 overflow 방지 가능
    특히 소수면, 곱셈 역원(multiplicative inverse) 계산에 유리.
        b/c. a * b mod M = 1 이면 b는 a의 역원.
        a가 M에 대해 역원을 가지려면 gcd(a,M)=1 즉 a, M이 서로소여야 함
        소수를 M으로 쓰면 M보다 작은 모든 수와 서로소이므로, 모두 역원 존재.
        역원이 필요할 때는 나눗셈을 mod할 때. 조합 계산할 때 특히 팩토리얼을 나눠주면서 역원 필요.
        fyi. 역원 계산 방법(소수 mod일 때): 페르마의 소정리(Fermat's Little Theorem)
            a^(p-1) = 1 mod p이므로 a^(-1) = a^(p-2)
            proof) mod p에서 {1, 2, ... p-1}은 곱셈군을 이룸 (곱셈에 닫혀있고 역원이 있음)


        fyi. 역원 계산 방법(일반 mod일 때): 확장 유클리드 알고리즘
            ax + My = 1인 x를 찾음

    단, c = a*b 대신 c = (a % MOD) * (b % MOD) % MOD 처럼 써야 함
*/


// 쉬운 2차원 배열 버전
long long partition(int n, int k, vector<vector<long long>>& P)
{
    // 예외처리
    if (k<=0 || n <=0) return 0;
    if (k==1 || n==k) return 1;
    // memo
    if (P[n][k] != -1) return P[n][k];

    P[n][k] = partition(n-1, k-1, P) + partition(n-k, k, P);
    return P[n][k];
}

// "토글링": 1차원 배열만 사용 -> 공간복잡도 O(N^2) -> O(N)
long long countpartitions(int n)
{
    vector<long> dp(n+1, 0); // P(n)만 담아놓음.
    dp[0]=1;
    for (int k=1; k<=n; ++k)
    {
        for (int i=k; i<=n; ++i)
        {
            dp[i] += dp[i-k];
        }
        /*
        k=1일 때, dp[i]에는 1을 미리 나누고, i-1을 분할하는 방법의 수를 더함
        k=2일 때, dp[i]에는 2를 미리 나누고, i-2를 분할하는 방법의 수를 더함
        ...
        */
    }

    return dp[n];
}

int main()
{
    int N = 100;
    vector<vector<long long>> P(N+1, vector<long long>(N+1, -1));

    long long result = 0;
    for (int k=1; k<=N; k++)
    {
        result += partition(N, k, P);
    }
    cout << result << endl;
    cout << endl;
    cout << countpartitions(100) << endl;
    return 0;

}