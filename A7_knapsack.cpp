/*
Knapsack problem (0-1 knapsack)
 - 배낭이 있고, 배낭안에 넣을 수 있는 최대 무게가 K
 - 배낭에 넣을 수 있는 물건은 N개, 각 물건마다 가치 V와 무게 W를 갖고 있음
 - 배낭 안에 담길 수 있는 가치의 최댓값을 구하라

DP approach
 - 물건을 일렬로 놓음. 첫번째 거부터, "누적무게 + 이번에 넣을 무게 < 최대무게"인 동안 계속 넣음.
 - 가방에 i번째 물건을 넣을 때, 무게가 K를 초과하면, max(i번째 물건을 넣기 전, 다른걸 빼고 i번째를 넣음)
    - i번째 물건을 넣기 전 값 : dp[i-1][K] (최대무게가 K일 때, i-1번째 물건을 넣었을 때의 최댓값)
    - i번째 물건이 다른 물건을 대체할 때의 값 : dp[i][K-W_i] + V_i
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;

    vector<pair<int, int>> items(N+1);
    
    for (int i=1; i<=N; ++i)
        cin >> items[i].first >> items[i].second;

    
    vector<vector<int>> dp(N+1, vector<int> (K+1, 0) );

    // i번째 물건을 고려
    for (int i=1; i<=N; ++i)
    {
        int weight = items[i].first;
        int value = items[i].second;

        // j크기의 가방을 고려
        for (int j=1; j<=K; ++j)
        {
            if (j < weight)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight]+value);
        }
    }

    cout << dp[N][K];


    // 1-dim array ver. (thanks to BOJ ID: audwns27)
    int dp2[K+1] = {};  // 배낭 용량에 따른 최대 가치
    int w, v;
    for (int i=1; i<=N; ++i)
    {
        cin >> w >> v;
        for (int j=K; j>=w; j--)            // 새로 들어온 걸 넣을 수 있는 경우만 고려 (배낭 최대무게가 새로 들어온 것보다 큰 경우만)
            if (dp2[j - w] + v > dp2[j])    // 새로 들어온 걸 넣었을 때 기존의 최댓값보다 커지는 지만 고려
                dp2[j] = dp2[j - w] + v;
    }
    cout << dp2[K];

    
    return 0;
}