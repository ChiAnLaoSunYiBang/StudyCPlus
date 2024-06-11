#include <iostream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

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
