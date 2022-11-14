#include <iostream>
#include <string.h>

using namespace std;
class String
{
public:
    String(const char *cstr = 0);         //构造
    String(const String &str);            //拷贝构造
    String &operator=(const String &str); //拷贝赋值
    ~String();                            //析构函数
    char *get_c_srt() const { return m_data; }

private:
    char *m_data;
};
inline String::String(const char *cstr = 0)
{
    if (cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else
    {
        m_data = new char[1];
        *m_data = '\0';
    }
}
inline String::String(const String &str)
{
    this->m_data = new char[strlen(str.m_data) + 1];
    strcpy(this->m_data, str.get_c_srt());
}
inline String &String::operator=(const String &str) //再类内包含指针时，要重写构造函数
{
    if (this == &str) //自我检测，当指针指向的地址相同时，不进行复制，返回当前数据
        return *this;
    delete[] m_data;                                 //释放被拷贝赋值的类内的数据，
    this->m_data = new char[strlen(str.m_data) + 1]; //获取一个新的地址，以及新申请的空间
    strcpy(this->m_data, str.get_c_srt());
    return *this;
}
inline String::~String()
{
    delete[] m_data;
}
int main(int argc, char *argv[])
{
    return 0;
}
