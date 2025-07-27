/*
    N개의 노드와 N-1개의 간선, 그래프는 연결되어 있어야 한다.

    1] 노드번호: 차수 라고 할 때, (1:N-1, 나머지: 1 -> 1*(N-1) + (N-1)*1) 가능. (1*(N-2) + (N-2)*1 + 1*2) 가능. 1*(N-3) + (N)
    2] N=M+K라고 하면, M끼리 간선만들고, K끼리 간선만들고 둘이 하나 이으면 됨. (M-1 + K-1 + 1 = N-1).
    3] 간선1짜리가 없을수도 있나? -> 불가능 N개가 차수 1 없으려면 서로 cycle이뤄야 함 -> N개 간선 필요
    4] N을 M과 K로 나누는 방법: (N,0) ~ (N//2(+1), N//2) : N//2+1개
    5] N을 M,K로 나눌 수 있으면 M도, K도,, 쭉쭉쭉 가능
    6] 각 단계에서 greedy하게 max를 찾으면서 재귀적으로?
    7] 뭘 재귀? 
        if 노드개수=1 -> 차수 0에 +1             (유일)
        else는 규칙으로 가능
            if 노드개수=2 -> 차수 1에 +2             (유일)
            if 노드개수=3 -> 차수 1에 +2, 차수 2에 +1 (유일)
            if 노드개수=4 -> 2+2(일직선) or 1+3(ㅗ모양). 이으면서 0이아닌 차수에 +1 한 것들 모두가 candidate. -> 2+2에서 1개(1:2 + 1:2 -> 1:2,2:2), 1+3에서 1개 (0:1 + 1:2,2:1 -> 1:2,2:2 & 1:3,3:1)
        
        vector dict = {node:result} 메모용

        input: 노드개수
        output: 차수 별 노드수 (벡터 포인터?)
        dp(int N)

        if N in dict.keys
            return dict[N]
        
        K = (M,N-M) 조합 수
        final_score = -1
        <vector> final_result

        for (M,N-M) 조합:
            score_M, result_M = dp(M)    # result는 N dim vec
            score_NM, result_NM = dp(N-M)
            result = result_M + result_NM   # 냅다 더함.
            score = score_M + score_NM
            c0 = 차수0 개수 (최대 2개)
            goup = 0
            if c0==0:
                goup = 2
            else:   // 차수가 0이면 무조건 올려야 함 (연결)
                result[0] = result[0] - c0
                result[1] = result[1] + c0
                if c0==1
                    goup = 1
                if c0==2
                    goup = 0
            
            for nodescore : 차수점수(내림차순 sorted) 
                if goup ==0
                    break
                if result[nodescore차수-1] != 0
                    result[nodescore차수-1] --  
                    result[nodescore차수] ++
                    goup--
            candidate_score = (차수점수 * result).sum()
            if candidate_score > final_score
                final_score = candidate_score
                final_result = result
            if candidate_score == final_score
                if final_result == result
                    continue
                else:

        return final_score, final_result
            

    9] gpt의 도움
        간선은 항상 (N-1) -> 차수 합: 2(N-1). -> a_n이 차수라고 하면, sum{n=1~N} a_n = 2(N-1)이어야 한다는거 -> 2N-2를 N개에게 어떻게 나눠주는가로 풀 수 있음 (Integer Partition 문제)
            - 차수 합이 2(N-1)이기만 하면 항상 그래프가 되는가? 그래프가 안되는 구성은 없나? N=4일 때 (1,1,1,3), (1,1,2,2). N=5일 때 (1,1,1,1,4), (1,1,1,2,3), (1,1,2,2,2) N=6일 때 (1,1,1,1,1,5), (1,1,1,1,2,4), (1,1,1,1,3,3), (1,1,1,2,2,3), (1,1,2,2,2,2) 가능한듯
            -> prufer code theory
        -> 그럼, N이 주어졌을 때 2N-2를 어떻게 분배할건가.. -> integer partition

        예시생각) N=5일 때
            P(8,5) = P(7,4) + P(3,5)를 생각해보면 P(3,5)=0. P(7,4)만큼의 경우의 수가 가진 점수에다가 1의 점수를 더해주면 됨.
            P(7,4) = P(6,3) + P(3,4)를 생각해보면 P(3,4)=0. P(6,3)만큼의 경우의 수가 가진 점수에다가 1의 점수를 더해주면 됨.
            P(6,3) = P(5,2) + P(3,3)을 생각해보면 P(3,3)=1. 여기선 2가 N-2개 있을 때의 점수가 하나 나오고, P(6,3)만큼의 경우의 수가 가진 점수에다가 1의 점수를 더해주는 점수가 하나 나옴
            P(5,2) = P(4,1) + P(3,2)를 생각해보면 P(4,1)=1, P(3,2)=1. 각각의 경우마다 점수를 세주면 되는데..
        그러면,
        P(2N-2, N) 점수 = max(1점수 + P(2N-3, N-1) 점수, 0)
        P(2N-3, N-1) 점수 = max(1점수 + P(2N-4, N-2) 점수,0)
        P(2N-4, N-2) 점수 = max(1점수 + P(2N-5, N-3) 점수, P(N-2,N-2)구성을 right shift한 점수)
        P(2N-5, N-3) 점수 = max(1점수 + P(2N-6, N-4) 점수, P(N-2,N-3)구성을 right shift한 점수)
        ...
        P(2N-2-(N-1), 1) = P(N-1, 1) 점수 = (N-1)점수
        ...
        P(N-2, 3) 구성: (2개) 
        P(N-2, 2) 구성 -> 1&P(N-3,1) or P(N-3,2)
        P(N-2, 1) 구성: (1개) N-2 x1
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// 이렇게 구성하면 주어진 테케는 맞지만 6, 0 0 100 0 0 으로 주면 틀림. 왜? P(6,2)에서 1,5와 4,2만 비교함. 3,3이 없음.
// 왜? P(6,2) = P(5,1) + P(4,2) 인데
// P(4,2)를 구할 때 1,3과 2,2를 보는데 1,3이 더 크므로 1,3을 택함. 그러나 P(6,2)를 고려할 땐 2,2를 택했을 때 더 큼. 실제 답도 2,2를 택했어야 함
const int MAX_N = 51;

struct Node
{
    long long score;
    int config[MAX_N];     // since 차수 <= 50

    Node()
    {
        score = -1LL;
        fill(config, config + MAX_N, 0);   // fill algorithm은 
    }
    Node(long long s)
    {
        score = s;
        fill(config, config + MAX_N, 0);   
    }
    Node(long long s, const int* arr)
    {
        score = s;
        for (int i=0; i<MAX_N; ++i)
            config[i] = arr[i];
    }

};

void arr_rshift(int* arr, int length)
{
    for (int i=length; i>0; --i)
        arr[i] = arr[i-1];
    arr[0] = 0;
}


Node partition_score(int n, int k,int N, vector<vector<Node>>& P, const vector<long long>& number_score)
{
    if (n<=0 || k<=0 || n<k) 
    {   
        return Node(0);
    }
    if (k==1) 
    {
        int arr[MAX_N] = {0};
        arr[n] = 1;
        return Node(number_score[n], arr);
    }
    if (k==n)
    {
        int arr[MAX_N] = {0};
        arr[1] = n;
        return Node(number_score[1] * n, arr);
    }
    if (P[n][k].score != -1)
        return P[n][k];


    Node part1 = partition_score(n-1, k-1, N, P, number_score);
    int config_with_1[MAX_N];
    for (int i=0; i<MAX_N; ++i)
        config_with_1[i] = part1.config[i];
    config_with_1[1] += 1;
    long long score_with_1 = part1.score + number_score[1];

    Node part2 = partition_score(n-k, k, N, P, number_score);
    int config_without_1[MAX_N];
    for (int i=0; i<MAX_N; ++i)
        config_without_1[i] = part2.config[i];
    arr_rshift(config_without_1, N-1);
    long long score_without_1 = 0;
    for (int i=1; i<=N; ++i)
        score_without_1 += config_without_1[i] * number_score[i];
            

    if (score_with_1 > score_without_1)
        return P[n][k] = Node(score_with_1, config_with_1);
    else if (score_with_1 < score_without_1)
        return P[n][k] = Node(score_without_1, config_without_1);   
    else // if score is equal;
    {
        if (config_with_1 == config_without_1)
            return P[n][k] = Node(score_with_1, config_with_1);
        else
        {
            bool better = false;
            for (int i = MAX_N-1; i >0; --i) {
                if (config_with_1[i] > config_without_1[i]) {
                    better = true;
                    break;
                } else if (config_with_1[i] < config_without_1[i]) {
                    better = false;
                    break;
                }
            }
            if (better)
                return P[n][k] = Node(score_with_1, config_with_1);
            else
                return P[n][k] = Node(score_without_1, config_without_1);
        }
    }
    
    return P[n][k];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> number_score(N+1);

    number_score[0]=0;
    for (int i=1; i<N; i++)
    {   
        cin >> number_score[i];
    }

    if (N==1)
    {
        cout << 0;
        return 0;
    }
        

    vector<vector<Node>> P(2*N-1, vector<Node>(N+1));
    partition_score(2*N-2, N, N, P, number_score);
    cout << P[2*N-2][N].score;

    return 0;
}   