/*
Union find 알고리즘은 여러 개의 원소들이 어떤 집합(set)에 속해 있는지를 관리하는 자료구조/알고리즘
두 집합을 하나의 합집합으로 만드는 작업(union)과 노드가 어떤 set에 속하는지를 판단하는 작업(find)로 구성됨
두 object가 연결되어있는 지 여부를 판단할 때 사용 (관계 update 가 dynamic한 상황 고려)

구성방법: 각 원소는 자기 자신만으로 이루어진 트리로 표현 (자신이 부모이자 자식)
union(x,y)를 하면 x의 루트 아래로 다른 루트를 붙임
find(x)를 하면 x가 속한 트리의 root를  반환
경로 압축 트리를 통해 트리를 납작하게 만들어 빠르게 탐색


참고: C++에는 union이라는 문법이 있다. (Struct와 비슷) 따라서 함수이름을 union으로 지으면 안된다!
참고: C++에는 std::rank라는 struct도 있다..! 따라서 rank라는 array를 만들면 안된다!

*/


#include<iostream>

using namespace std;

const int MAX_SIZE = 1000;

int parent[MAX_SIZE];
int rankArr[MAX_SIZE];

// tree initialization
void init(int n)
{
    for (int i=0; i<n; ++i)
    {
        parent[i] = i;
        rankArr[i] = 0;
    }
}

// 재귀적으로 root를 찾아감
int find(int x)
{
    if (parent[x] ==x)
        return x;
    else
        return parent[x] = find(parent[x]);
        // return find(parent[x])처럼 해도 되지만! find하면서 만난 모든 값의 부모 노드를 root로 만들면, 즉 x의 할아버지, 증조할아버지, 고조할아버지까지 다이렉트로 이어줌 (: 경로 압축, Path Compression.)
}

void unionset(int x, int y)
{
    int rx = find(x);
    int ry = find(y);

    if (rx == ry)
        return ;
    /* 이거만 해줘도 됨. 더 효율적이려면 rankArr 도입하는 것도 좋음. (더 큰 트리를 밑에)
    else
        parent[ry] = x;
    */

    // rankArr은 트리의 추정 크기.
    if (rankArr[rx] < rankArr[ry])
        parent[rx] = y;
    else
        parent[ry] = x;
    
    // rank가 3과 1이면 1을 3에 (3의 root에) 붙여도 전체 트리 높이는 3 유지. -> 트리 높이가 같을 때에만 높이 증가
    // 이렇게 하면 트리의 깊이가 깊어지는 걸 막을 수 있음.
    if (rankArr[rx] == rankArr[ry])
        rankArr[rx]++;

    return;
}

int main()
{
    int N= 100;
    init(N);


}

