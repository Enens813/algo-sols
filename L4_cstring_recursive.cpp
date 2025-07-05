// Recursive Functions
/*

*/

#include <iostream>
#include <cstring>

using namespace std;

char path[10] = "";
void dfs(int level)
{
    if (level == 3)
    {
        std::cout << path << endl;
        return;
    }

    // tree의 왼쪽 노드
    path[level] = 'A';
    dfs(level+1);
    std::cout << "first " << level << endl;
    path[level] = 0;

    // tree의 오른쪽 노드
    path[level] = 'B';
    dfs(level+1);
    std::cout << "secon " << level << endl;
    path[level] = 0;

}
int main()
{
#pragma region cstring
    // cstring
    char nameA[10] = "ABC";
    char nameB[10] = "ABC";
    char nameC[10] = "";

    if (strcmp(nameA, nameB) == 0) // 같을 때 0
    {
        int a= 0;
    }

    int len = strlen(nameA);

    std::cout << strlen(nameC) << endl;

    strcpy_s(nameC, nameA);

    std::cout << len << " " << strlen(nameC) << endl;
#pragma endregion

    dfs(0);

    return 0;
}