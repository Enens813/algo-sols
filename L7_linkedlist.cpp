// Linked List
/*
    노드 -> 노드 -> 노드 ...
    장점: 데이터 추가가 쉬움. 중간에 추가하기도 쉬움. 배열로 하려면 전부 복사해서 옮겨야 함
*/
#include <iostream>
#include <cstring>

using namespace std;


struct Node{
    int data;
    Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;
void AddNode(int data)
{
    if (head == nullptr)
    {   
        // 헤드에 추가
        head = new Node;
        head-> data = data;
        head->next = nullptr;

        tail = head;
    }
    else{
        //제일 마지막 노드 뒤에 추가
        tail->next = new Node;
        tail->next->data = data;
        tail->next->next = nullptr;

        // tail을 새로 추가한 Node로 변경
        tail = tail->next;
    }
}

int main()
{
    // 동적할당
    // 지역변수는 stack에 할당되어 해당 지역을 벗어나면 해제됨
    // 동적할당변수는 heap에 할당되어 따로 메모리 해제를 하지 않으면 안 사라짐
    
    int* p;
    p = new int;
    *p = 3;
    cout << *p << endl;
    delete p;

    Node* pp = new Node;
    pp -> data = 5;
    cout << (*pp).data << endl;
    delete pp;

    AddNode(3);
    AddNode(4);
    AddNode(5);

    Node* np = head;
    while (true)
    {
        if (np == nullptr)
            break;
        
        cout << np-> data << " ";
        np = np->next;

    }

    // 위 while과 같은 코드
    for (Node* np = head; np !=nullptr; np = np->next )
    {
        cout << np->data << " ";
    }
    
    return 0;
}
