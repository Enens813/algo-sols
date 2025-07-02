// Hash Table (Direct Addressing Table)
/*
값 자체를 index로 활용 -> search 속도가 1 (index/주소를 이용해서 바로 가져오기)
python의 dict같은 느낌.
C++에선 table 크기를 미리 지정해야 함. -> memory 낭비가 큼, 대신 속도가 빠름

왜 이름이 Hash? 실제 구현될 때는 값을 index로 바꿀 때 hash 함수 사용. 근데 다른 값이 같은 index가 되면 안됨(injective function, 일대일, 단사 함수). 이를 Hash 함수로 구현함.

Hash table을 만들어서 순서대로 출력시키면 정렬 algorithm으로도 쓸 수 있음
*/

#include <iostream>
#include <string>

using namespace std;

int isPattern(int idx)
{
    for (size_t i=0; i<3; i++)
    {
        if (pattern[i]!= vect[idx+i]) // idx~idx+3이 pattern과 하나라도 다르면 0
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    char ch = 'A';

    int bucket[256] = {};

    char str[7] = "ADBFAD";

    for (size_t i=0; i<6; i++)
    {
        bucket[str[i]]++;
    }

    // 이때 bucket이 hash table..! str에 어떤 alphabet이 몇 개 있는 지를 담은 array

    for (int x=0; x<256; x++)
    {
        if (bucket[x] != 0)
        {
            std::cout << (char)x << " : " << bucket[x] << endl;
        }
    }

    // Hashtable 이용해서 패턴찾기
    char vect[10] = "BTABCQABC";
    char pattern[4] = "ABC";
    int result = 0;

    for (size_t i=0; i<7; i++)
    {
        result = isPattern(i);
    }
    std::cout << result << endl;
    
    return 0;
}