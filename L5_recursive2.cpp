// Recursive Functions
/*
    재귀함수 가지치기
*/

#include <iostream>
#include <cstring>

using namespace std;

char path[5] = "";
void dfs(int level)
{
    // 진입했다가 return 
    // if (path[0] == 'A')
    //     return;

    if (level == 3)
    {
        cout << path << endl;
        return;
    }

    for (size_t i=0; i<3; i++)
    {
        // 진입부터 안함
        if (level == 0 && ('A' + i) == 'A')
            continue;

        path[level] = 'A' +i;
        dfs(level+1);
        path[level] = 0;
    }

}
int main()
{
    dfs(0);

    return 0;
}