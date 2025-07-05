// struct & pointers

#include <iostream>
#include <cstring>

using namespace std;


int main()
{
    struct Vector2
    {
        int x;
        int y;
    };
    Vector2 p1;
    Vector2* vp = &p1;

    // 아래 두 연산자는 같은 역할. 주소에서 객체로 가서 참조하는 연산을 ->로 정의
    (*vp).x = 100;
    vp -> y = 200;

    struct Node{
        int data;
        Node* next;
    };
    Node* head;
    Node n1, n2, n3;
    n1.data = 1; n2.data = 2; n3.data = 3;
    head = &n1;
    n1.next = &n2;
    n2.next = &n3;

    cout << head->data << endl;
    cout << head->next->data << endl;
    cout << head->next->next->data << endl;

    return 0;
}