#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

/* 문제이해
A는 (A+2 mod 8) & (A-2 mod 8) 과 수직
0 -> 2,6
1 -> 3,7
2 -> 4,0
4 -> 6,2
6 -> 0,4
7 -> 1,5
*/

// segment tree 여러개 만드는 것보다 Node의 tree를 만드는 게 cache 적중률 높고, 재참조 루프 덜 걸림!
struct Node
{
    int startDirection;
    int endDirection;
    bool canPass; // struct에서 bool 다음에 int가 오면 padding. padding 을 없애려면 bool을 나중에 선언
};

bool build(int node, int start, int end, vector<int>& vec, vector<Node>& segtree)
{
    // leaf node 일 때
    if (start == end) 
    {
        segtree[node].startDirection = vec[start];
        segtree[node].endDirection = vec[end];
        return segtree[node].canPass = 1;
    }

    // recursive 하게 자식 노드 구성
    int leftnode = node*2;
    int rightnode = node*2+1;
    int mid = (start + end) / 2;

    bool LeftResult = build(leftnode, start, mid, vec, segtree);
    bool RightResult = build(rightnode, mid+1, end, vec, segtree);

    // 해당 구간을 통과할 수 있는가
    int criterion = (segtree[leftnode].endDirection - segtree[rightnode].startDirection + 8) % 8;
    if (criterion ==2 || criterion == 6)
        segtree[node].canPass = 0;
    else
        segtree[node].canPass = LeftResult && RightResult;

    // 구간의 처음과 끝 방향은 무엇인가
    segtree[node].startDirection = segtree[leftnode].startDirection;
    segtree[node].endDirection = segtree[rightnode].endDirection;

    return segtree[node].canPass;
}

void update(int node, int start, int end, int index, int newvalue, vector<Node>& segtree)
{
    // update 할 index가 구간에 포함되는가
    if (index < start || end < index) return;
    
    // update 할 index가 구간의 시작 또는 끝인가
    if (start == index)
        segtree[node].startDirection = newvalue;
    if (end == index)
        segtree[node].endDirection = newvalue;

    // 시작과 끝을 바꿨으면 leaf node는 항상 segtree=1이므로 .canPass바꿀 필요 없음
    if (start == end) return;
    
    // recursive 하게 자식 노드 수정
    int leftnode = node*2;
    int rightnode = node*2+1;
    int mid = (start + end) / 2;

    update(leftnode, start, mid, index, newvalue, segtree);
    update(rightnode, mid+1, end, index, newvalue, segtree);

    int criterion = (segtree[rightnode].startDirection - segtree[leftnode].endDirection + 8) % 8;
    if (criterion ==2 || criterion == 6)
        segtree[node].canPass = 0;
    else
        segtree[node].canPass = segtree[leftnode].canPass && segtree[rightnode].canPass;
    
    return ;
}

// bool: query 결과, int,int: 시작과 끝
tuple<bool, int, int> query(int node, int start, int end, int left, int right, vector<Node>& segtree)
{
    // node 구간이 query 구간 밖인가
    if (right < start || end < left) return {1,-1, -1};

    // node 구간이 query 구간 안인가
    if (left <= start && end <= right)
        return {segtree[node].canPass, segtree[node].startDirection, segtree[node].endDirection};

    // 그렇지 않다면 recursive 하게 자식 노드 호출
    int leftnode = node*2;
    int rightnode = node*2+1;
    int mid = (start + end) / 2;

    auto [left_pass, left_start, left_end] = query(leftnode, start, mid, left, right, segtree);
    auto [right_pass, right_start, right_end] = query(rightnode, mid+1, end, left, right, segtree);

    if (left_start == -1 && right_start == -1) return {1,-1,-1};
    else if (left_start == -1) return {right_pass, right_start, right_end};
    else if (right_start == -1) return {left_pass, left_start, left_end};
    else {
        int diff = (right_start - left_end + 8) % 8;
        bool can_connect = !(diff == 2 || diff == 6);
        bool total_pass = left_pass && right_pass && can_connect;
        return {total_pass, left_start, right_end};
    }
}


// segment tree 풀이
int main()
{
    // io 속도 증가
    ios::sync_with_stdio(false);    // C++의 cout, cin이 C의 scanf, printf의 동기화 해제
    cin.tie(nullptr);               // C++의 cin과 cout은 tied 되어있어서, cin을 호출하면 cout을 자동 flush 함. 근데 flush는 느림. 이 코드로 cin을 호출할 때 cout을 flush없이 함.
    /*
    C++의 cin/cout(iostream)과 C의 scanf/printf(stdio)는 동기화 되어있음. C++의 cin과 C의 stdin 버퍼가 같이 동작하고, C++의 cout과 C의 stdout버퍼가 같이 동작함. 이는 cin/cout/scanf/printf를 같이 사용해도 충돌 없게 하기 위함.
    이 버퍼 동기화를 'ios::sync_with_stdio(false)'로 해제하면, 버퍼를 C버퍼를 동기화시킬 필요가 없어져서 속도가 빨라짐
    대신, cin/cout과 scanf/printf를 혼용하면 안 됨

    C++의 cin과 cout은 tied 되어있어서, cin을 호출하면 cout을 자동 flush 함. 
    근데 flush는 느림. 'cin.tie(nullptr)'로 cin을 호출할 때 cout flush를 안하게 만들 수 있음.
    대신, cin직전의 cout이 제대로 출력되지 않을 수 있음 주의.
    */

    // input 구성
    int N, M;
    cin >> N >> M;

    vector<int> vec(N);
    vector<Node> segtree(4*N);
    vector<int> finalResults;   // vector<bool>을 쓰면 일반적인 vector 가 아니고 bit 단위로 값을 압축 저장하는 구현체 -> 일반 vector 보다 모든 연산이 느림! -> TLE(Time Limit Excess) 발생가능

    // data init
    for (int n=0; n<N; ++n)
        cin >> vec[n];

    // build segtree
    build(1, 0, N-1, vec, segtree);

    // query처리
    for (int m=0; m<M; m++)
    {
        int q, a, b;
        cin >> q >> a >> b;
        if (q==1)
        {
            vec[a-1] = b;
            update(1,0,N-1, a-1, b, segtree);
        }
            
        if (q==2)
        {
            tuple<bool, int, int> res = query(1,0,N-1, a-1, b-1, segtree);
            finalResults.push_back(get<0>(res));
        }
    }

    for (int res : finalResults) {
        cout << res << '\n';    // endl은 출력 후 버퍼를 강제로 flush 하므로 매우 느림. 많은 출력할 때는 \n 사용!!!
    }

    return 0;
}







// 그냥 반복문 풀이 -> 시간초과
/*
int main()
{
    int N, M;
    cin >> N >> M;

    vector<int>vec(N);
    vector<int> results; // q == 2 쿼리 결과 저장용

    // init
    for (int n=0; n<N; n++)
    {
        int i;
        cin >> i;
        vec[n] = i;
    }

    for (int m=0;m<M; m++)
    {
        int q, a, b;
        cin >> q >> a >> b;
        if (q==1)
        {
            vec[a-1] = b;
        }
        if (q==2)
        {
            int ok = 1;
            for (int k=a; k<b; k++)
            {   
                int sub = vec[k] - vec[k-1];

                if (sub==2 || sub==6 || sub==-2 || sub==-6)
                {
                    ok = 0;
                }
            }

            results.push_back(ok);
        }
    }

    // 결과 출력
    for (int r : results) {
        cout << r << "\n";
    }
    
    return 0;
}
*/