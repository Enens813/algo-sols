/*
세그먼트 트리(Segment Tree)는 구간 쿼리(range query)와 점 업데이트(point update)가 모두 빠르게 가능한 트리 기반 자료구조
ex. 구간 합, 구간 최대공약수 등 구할 때 사용

구성방법: N 길이 list가 들어오면,  root 노드에는 0~N을 할당. root의 자식 노드는 0~N//2, N//2+1~N으로 나눔. 이걸 반복.
그럼 leaf에는 각 element가 하나씩 할당됨. 각 노드마다 할당된 element들을 합함. 즉, parent는 각 leaf의 합이 됨.
몇 번째 값인지 찾기 쉽게, segment tree index는 root를 1, 왼쪽 첫번째 자식을 2, 오른쪽 첫번째 자식을 3으로 하고, 아래도 계속 이어서 함. 이렇게 하면 맨 왼쪽은 2^n의 index를 가지고, 모든 자식 노드의 왼쪽은 짝수가 됨.
길이가 9인 리스트가 들어왔다고 가정했을 때 segment tree는 element 번호로 나타내면, ([{(0,1), 2}, {3,4}], [{(5,6), 7}, {8,9}]) 처럼 구성됨.

예를 들어, 3~6의 구간합을 구할 때는 {3,4}와 {5,6}을 더하면 됨. 4개를 더해야 되던 것이 두개로 줄음.
6~9의 구간합을 구할 때는 6과 7과 {8,9}를 더하면 됨. 4개를 더해야 되는 것이 세개로 줄음. 이건 구간이 길어지고, input 배열이 커질수록 효율적이게 됨.

6의 값을 update한다면, 6, (5,6), {(5,6),7}, [{(5,6), 7}, {8,9}], ([{(0,1), 2}, {3,4}], [{(5,6), 7}, {8,9}]) 의 다섯 개 값에서 원래 6값을 빼고 새 6값을 더해야 함.

특징: leaf node는 배열의 값을, leaf가 아닌 node에는 자식들의 합을 저장.
segment tree의 크기: N 길이 배열이 들어왔을 때, leaf가 N개 이므로, 각 층마다, 1+2+4+8+..+(N보다 크거나같은 2의 배수)만큼, 즉 (N보다 크거나같은 2의 배수)의 두배만큼 필요.
이는, best case에서 2N, worst case에서 4N필요.(ex. N=33일때, 64*2가 필요하므로 거의 4N)

tree 구성방법:
    (segment tree index 번호, 이 node에 할당될 input배열의 시작범위, 이 node에 할당될 input배열의 끝범위)를 이용
     (node에 할당되는 input 배열의 시작범위 != 끝범위) 이고, 즉 leaf node가 아니고, 2*현재 tree index와 2*현재 tree index+1 의 node가 비어있으면(자식 노드에 값이 아직 안 들어왔으면) 재귀적으로 자식 노드를 호출
    node에 할당되는 input 배열의 시작범위 == 끝범위 일때 재귀가 멈추고, 배열의 값을 node의 값으로 넣음.

tree 구간합 방법:
    "Segment tree node에 할당된 input 배열의 범위" 가 구간합 query의 범위와 겹치는 부분이 없다면 -> 0반환하고, 자식노드를 호출하지 않음
    "Segment tree node에 할당된 input 배열의 범위" 가 구간합 query의 범위안에 속한다면 -> 본인 Node의 값을 반환하고, 자식노드를 호출하지 않음
    "Segment tree node에 할당된 input 배열의 범위" 가 구간합 query의 범위안에 일부는 속하고, 일부는 아니라면 -> 자식노드를 호출

tree 포인트 업데이트 방법:
    "Segment tree node에 할당된 input 배열의 범위"가 query point를 포함하면 바꾸기 전 query node값을 빼고, 새 query node값을 더함 & leaf node가 아니라면 자식 노드 호출
    "Segment tree node에 할당된 input 배열의 범위"가 query point를 포함하지 않으면 break

시간복잡도:
    구간 쿼리: O(log N)
    점 업데이트: O(log N)
    구성(build): O(N)
공간 복잡도: O(N ~ 4N)

일반 배열을 썼을 때의 시간 복잡도:
    구간 쿼리: O(N)
    점 업데이트: O(1)
    구성: O(N)
일반 배열을 썼을 때의 공간 복잡도: O(N)

참고: https://velog.io/@kimdukbae/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0-%EC%84%B8%EA%B7%B8%EB%A8%BC%ED%8A%B8-%ED%8A%B8%EB%A6%AC-Segment-Tree
*/


// 예제
/*
정수 배열 A = [1, 3, 5, 7, 9, 11] 가 주어졌을 때,
다음 쿼리를 효율적으로 처리하는 자료구조를 만들어라:

1. 특정 구간 [l, r]의 합을 구하라 (Sum Query)
2. 특정 위치의 값을 업데이트하라 (Point Update)
*/

#include <iostream>
#include <iomanip>  // for setw

using namespace std;


const int N=10;
int Arr[N] = {1,2,3,4,5,6,7,8,9};
int SegmentTree[4*N];


int Make_SegmentTree(int Node, int Start, int End)
{
    if (Start == End) return SegmentTree[Node] = Arr[Start];

    int Mid = (Start+End) / 2;
    int Left_Result = Make_SegmentTree(Node*2, Start, Mid);
    int Right_Result = Make_SegmentTree(Node*2+1, Mid+1, End);
    SegmentTree[Node] = Left_Result + Right_Result;

    return SegmentTree[Node];
}

// Node: segment tree node 번호, Start/End는 해당 노드가 포함하는 범위, Left/Right는 우리가 구하고자 하는 범위
int Sum(int Node, int Start, int End, int Left, int Right)
{
    if (Left > End || Right < Start) return 0;
    if (Left <= Start && End <= Right) return SegmentTree[Node];

    int Mid = (Start+End)/2;
    int Left_Result = Sum(Node*2, Start, Mid, Left, Right);
    int Right_Result = Sum(Node*2+1, Mid+1, End, Left, Right);
    
    return Left_Result + Right_Result;
}

// Node: segment tree node 번호, Start/End는 해당 노드가 포함하는 범위, Index는 바꿀 query point의 input배열 index, Diff는 새 point 값 - 원래 point 값
void Update_SegmentTree(int Node, int Start, int End, int Index, int Diff)
{
    if (Index < Start || Index > End) return;

    SegmentTree[Node] = SegmentTree[Node] + Diff;

    if (Start != End)
    {
        int Mid = (Start+End) / 2;
        Update_SegmentTree(Node*2, Start, Mid, Index, Diff);
        Update_SegmentTree(Node*2+1, Mid+1, End, Index, Diff);
    }
}

void Print_SegmentTree_By_Level() {
    int treeSize = 4 * N;  // SegmentTree의 크기
    int level = 0;
    int index = 1;

    while (index < treeSize) {
        int nodesInLevel = 1 << level;  // 2^level 개의 노드
        bool hasPrinted = false;

        for (int i = 0; i < nodesInLevel && index < treeSize; ++i, ++index) {
            if (SegmentTree[index] != 0) {  // 유효 노드만 출력
                cout << SegmentTree[index] << " ";
                hasPrinted = true;
            }
        }
        if (hasPrinted) cout << endl;
        level++;
    }
}

int main()
{
    Make_SegmentTree(1,0, N-1);
    Print_SegmentTree_By_Level();

    int res = Sum(1, 0, N-1, 3, 6);

    int Index=5;
    int Value=1;
    Arr[Index] = Value;

    int Diff = Value - Arr[Index];
    Update_SegmentTree(1, 0, N-1, Index, Diff);
    Print_SegmentTree_By_Level();

    int res2 = Sum(1, 0, N-1, 3, 6);

    cout << res << " " << res2 << endl;
    return 0;
}