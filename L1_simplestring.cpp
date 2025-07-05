// g++ {파일명}.cpp -o {실행파일명}.exe 하면 vscode 안거치고 바로 gcc로 compile 후 실행
#include <iostream>
#include <string>

using namespace std;

class MyString
{
public:
    MyString(const char* str)
    {
        for (int i=0; i<256; i++)
        {
            this->str[i] = '\0';
        }

        for (int i=0; i<256; i++)
        {
            if (str[i] == '\0')
            {
                len = i;
                break;
            }

            this->str[i] = str[i];
        }

        
    }

    int size()
    {
        return len;
    }

    void operator+=(const char* str )
    {
        int idx = 0;
        for  (int i=len; i<256; i++)
        {
            if (str[idx] == '\0')
            {
                len = i;
                break;
            }

            this->str[i] = str[idx];
        }
    }

private:
    char str[256];
    int len;
};
int main(){
    cout << "Hello, World" << endl;

    std::string str = "Hello";
    int len = str.size();

    MyString str2 = "ABCD";
    int len2 = str2.size();

    cout << len << len2 << endl;

    return 0;
}