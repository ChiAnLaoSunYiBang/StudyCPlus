#include <iostream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;
template <typename T>
class A
{
public:
    A() {}
};
template <typename T, class a = A<T>> // B类包含A类，称之为复合 ，图示方法：B<黑色菱形><实线-箭头>A
class B
{
public:
    a t;
};
/////////////////////////////////////////////////
class D;
class C
{
public:
private:
    D *d;
};
class D //委托，两个类的生命周期不同，C<空心菱形><箭头-右>D
{
    friend class C;

public:
    D() {}
};
//继承 F<直线-箭头>E
class E
{
public:
    int v;
};
class F : public E
{
};
//委托加继承，解决一对多的状态更新问题
//修改为多继承
class observe
{
public:
    observe(observe *_bf = nullptr) { set_p(_bf); }
    virtual void set_p(observe *o_ptr) {}
    virtual observe *get_p(int index) {}
    virtual void updateCnt(int) {}
};
class p1 : public observe
{
public:
    p1(observe *_bf) : observe(_bf) {}
    void updateCnt(int cnt)
    {
        cout << "p1 see:" << cnt << endl;
    }
};
class p2 : public observe
{
public:
    p2(observe *_bf) : observe(_bf) {}
    void updateCnt(int cnt)
    {
        cout << "p2 see:" << cnt << endl;
    }
};
class factory : public observe
{
public:
    factory()
    {
    }
    void start()
    {
        int i = 20;
        while (i-- != 0)
        {
            for (auto n : o_arr)
            {
                n->updateCnt(i);
            }
        }
    }
    ~factory()
    {
        for (auto n : o_arr)
            delete n;
    }
    void set_p(observe *o_ptr)
    {
        if (!o_ptr)
            return;
        for (auto n : o_arr)
        {
            if (o_ptr == n)
                return;
        }
        o_arr.push_back(o_ptr);
    }
    observe *get_p(int index)
    {
        if (index >= o_arr.size())
        {
            return nullptr;
        }
        return o_arr[index];
    }

private:
    vector<observe *> o_arr;
};
int main(int argc, char *argv[])
{
    factory ff;
    p1 pp(&ff);
    p2 ppp(&ff);
    ff.start();
    return 0;
}
