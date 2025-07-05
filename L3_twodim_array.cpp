// 방향, 이중 포인터
/*
2차원 배열에서, 특정 위치의 neighbor를 가져올 때, arr[y-1][x], arr[y+1][x], arr[y][x-1], arr[y][x+1]을 찾아야 함.
이걸, 방향을 나타내는 array를 만들어서 편하게 쓰자?

*/

#include <iostream>
#include <string>

using namespace std;


int map[5][5] = {
    1,3,5,1,5,
    3,7,9,5,8,
    4,5,3,9,7,
    2,7,6,1,9,
    1,6,2,3,8,
};
int pattern[2][2] = {
    3,5,
    7,9,
};
int isPattern(int dy, int dx)
{
    for (size_t y=0; y<2; y++)
    {
        for (size_t x=0; x<2; x++)
        {
            if (map[dy+y][dx+x] != pattern[y][x])
            {
                return 0;
            }

        }
    }
    return 1;
}

int main(){

    int arr[3][3] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    int direct[4][2] = {
        -1,0,
        1,0,
        0,-1,
        0,1
    };

    int x=1; int y=1; int sum=0;
    for (size_t i = 0; i<4; i++)
    {
        int newX = x + direct[i][1];
        int newY = y + direct[i][0];
        
        if (newX >=0 && newX<=2 && newY>=0 && newY <=2)
        {
            sum += arr[newY][newX];
        }
    }
    
    // 이중포인터 변수
    int a = 0;
    int* p = &a;
    int** pp = &p;   // **p = 200; 하면 a가 바뀜.


    for (size_t y=0; y<4; y++)
    {
        for (size_t x=0; x<4; x++)
        {
            int ret = isPattern(y,x);
            if (ret == 1)
            {
                a += 1;
            }
        }
    }

    std::cout << a << endl;


    return 0;
}
