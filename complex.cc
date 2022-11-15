#include <iostream>
#include <iomanip>
#include <time.h>
#include <sstream>
using namespace std;
class complex
{
public:
    complex(double r = 0, double i = 0) : re(r), im(i) {} //使用初始化列表，而不是跳过，进行赋值
    complex &operator+=(const complex &);
    double real() const { return re; } //加const,可被常量对象调用，不加则不能。
    double imag() const { return im; }
    void fun(complex &in) //相同类型，互为友元类
    {
        cout << in.im << endl;
    }

private:
    double re, im;
    friend complex &__doapl(complex *, const complex &); //入参，出参，尽量使用引用。
    complex fun_1(double &a, double &b)                  //函数内创建的对象或值不能用引用传递，函数结束后，被引用的值会消失
    {
        return complex(a, b);
    }
};

complex &__doapl(complex *ths, const complex &r)
{
    ths->im = r.im;
    ths->re = r.re;
    return *ths;
}
inline complex &complex::operator+=(const complex &r) //成员函数，操作符重载
{
    cout << "i am += !" << endl;
    return __doapl(this, r);
}
inline complex operator+(const complex &x, const complex &y) //返回value,不返回临时值的引用
{
    return complex(x.imag() + y.imag(), x.real() + y.real());
}
inline bool operator==(double x, const complex &y)
{
    return x == y.real() && y.imag() == 0;
}
ostream &operator<<(ostream &os, const complex &x) // << 是从左到右，依次输出
{
    return os << '(' << x.real() << ',' << x.imag() << ')';
}
int main(int argc, char *argv[])
{
    complex aa;
    complex bb;
    aa.fun(bb);
    aa += bb;
}
