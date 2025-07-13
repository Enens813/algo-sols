/*
우선순위 큐(priority queue)는 우선순위가 높은 데이터가 먼저 나가는 형태의 자료구조
우선순위 큐는 max heap이나 min heap을 이용하여 구현함.

Heap은 완전이진트리 형태의 자료구조.
Max Heap은 부모 노드의 value 값이 자식보다 크거나 같은 완전이진트리
Min Heap은 부모 노드의 value 값이 자식보다 작거나 같은 완전이진트리

우선순위 큐를 unsorted array나 linked list로 구현하면 삽입에 O(1), 삭제에 O(N)
우선순위 큐를 sorted array나 linked list로 구현하면 삽입에 O(N), 삭제에 O(1)
우선순위 큐를 Heap으로 구현하면 삽입에 O(log N), 삭제에 O(log N)

구현방법)
삽입: 1. Heap의 마지막 노드에 새 노드를 추가 -> 2. 추가된 새 노드를 부모와 비교하여 교환 -> 3. 정상적인 Heap이 될 때까지 2를 반복
삭제: 1. Root 노드 (가장 우선순위 높음) 제거 -> 2. Heap의 마지막 노드를 Root 노드로 만듦 -> 3. root노드와 자식노드를 비교하여 교환 -> 4. 정상적인 Heap이 될 때까지 3을 반복
둘 다 이진트리 높이만큼이 최악의 case이므로 logN 시간복잡도

참고)
<queue> 안에 구현되어있음
methods
 - push() : 노드 추가
 - pop() : root 노드 제거
 - top() : root 노드 반환
 - empty() : 비어있으면 true
 - size() : 노드 수 반환

Reference: https://suyeon96.tistory.com/31
*/

#include <iostream>
#include <queue>
using namespace std;

#define MAX_ELEMENT 200

template <typename T>
struct Node{
    int key;
    T data;

    Node()
    {
        key=0;
    }

    Node(int _key, T _data)
    {
        key= _key;
        data = _data;
    }

    ~Node(){}
};

template<typename T>
class MaxHeap{

public:
    Node<T> node[MAX_ELEMENT];
    int size = 0;

    Node<T>& getParent(int index){
        return node[index/2];   }
    Node<T>& getLeftChild(int index){
        return node[index*2];   }
    Node<T>& getRightChild(int index){
        return node[index*2+1];   }


    void push(int key, T data)
    {
        // isFull 생략 (PS 단계에선 그럴리 없음)

        // heap의 맨 마지막 노드에 넣고, size 증가
        int index = ++size;

        // index가 Heap을 거슬러 올라가며 parent와 비교. root가 아니고, 본인 key가 parent key보다 크면 부모와 index 교환
        while (index != 1 && key > getParent(index).key)
        {
            // 부모 node를 자신의 index로 바꿈
            node[index] = getParent(index);
            // 자신의 index는 원래 부모의 것으로.
            index /= 2;
        }
        
        // 최종 위치에 데이터 삽입
        node[index].key = key;
        node[index].data = data;
    }

    T pop()
    {
        // isEmpty 생략 (PS 단계에선 그럴리 없음)
        
        Node<T> itemNode = node[1];

        // Heap의 마지막 노드의 index를 root로 설정하고 size 감소 
        Node<T> lastNode = node[size--];
        int index=1;

        // root부터 내려가며 자식 노드와 비교
        while (index <= size)
        {
            // 자식노드가 없으면 break
            if (index*2 > size)
                break;
            
            // 자식노드가 하나(마지막 노드)이면
            else if (index*2 == size)
            {
                // 자신이 자식노드보다 작다면
                if (lastNode.key < getLeftChild(index).key)
                {
                    // 자식 노드는 자신의 index를 갖고
                    node[index] = getLeftChild(index);
                    // 자신의 index는 자식노드의 index가 됨
                    index *= 2;
                    break;
                }
                // 자신이 자식노드보다 크다면 중지
                else
                    break;
            }

            // 자식노드가 둘 다 있음
            else {
                int leftChildKey = getLeftChild(index).key;
                int rightChildKey = getRightChild(index).key;

                // 자신이 자식노드 둘 중 하나보다 작다면, 둘 중 key가 더 큰 자식 노드와 교환
                if (lastNode.key < leftChildKey || lastNode.key < rightChildKey)
                {
                    node[index] = leftChildKey > rightChildKey ? getLeftChild(index) : getRightChild(index);
                    index = leftChildKey > rightChildKey ? index*2 : index*2+1;
                }
                // 자신이 두 자식노드보다 크다면 중지
                else
                    break;
            }
        }

        // 원래 마지막이었던 노드를 최종 위치에 저장
        node[index] = lastNode;

        // 삭제 노드의 data 반환
        return itemNode.data;
    }

    T top(){
        return node[1].data;
    }

    bool empty(){
        return size ==0;
    }
};


// customizing type
struct customNode {
    int height;
    int tax;

    customNode(){
        height = 0;
        tax = 0;
    }
    customNode(int _height, int _tax){
        height = _height;
        tax = _tax;
    }
};

// height 기준으로 큰 값이 먼저 오게 (max heap)
struct Compare {
    bool operator()(const customNode& a, const customNode& b) {
        return a.height < b.height; // height가 클수록 우선순위 높음
    }
};

int main()
{
    // Max Heap
    priority_queue<int, vector<int>, less<int>> pq; // type, container, compare

    pq.push(5);
    pq.push(2);
    pq.push(8);
    pq.push(9);
    pq.push(14);

    pq.pop();
    pq.pop();

    cout << "STL Max Heap Priority Queue: ";
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;


    // with customized type
    priority_queue<customNode, vector<customNode>, Compare> pq2; // type, container, compare

    pq2.push(customNode(5,1));
    pq2.push(customNode(2,2));
    pq2.push(customNode(8,3));
    pq2.push(customNode(9,4));
    pq2.push(customNode(14,5));

    pq2.pop();
    pq2.pop();

    cout << "STL Max Heap Priority Queue with customized Type: ";
    while (!pq2.empty())
    {
        cout << pq2.top().height << " ";
        pq2.pop();
    }
    cout << endl;


    // With DIY MaxHeap
    MaxHeap<int> PQ;
    PQ.push(5,5);
    PQ.push(2, 2);
    PQ.push(8, 8);
    PQ.push(9, 9);
    PQ.push(14, 14);

    PQ.pop();
    PQ.pop();

    cout << "DIY Max Heap Priority Queue: ";
    while (!PQ.empty())
    {
        cout << PQ.top() << " ";
        PQ.pop();
    }
    cout << endl;

}
