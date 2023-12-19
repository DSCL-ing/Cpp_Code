#define _CRT_SECURE_NO_WARNINGS 1

#include <ctime>
#include <random>
#include <iostream>
#include<string.h>
#include<algorithm>
#include<string>
#include<map>
#include<memory>
#include<mutex>
#include<thread>
#include<functional>
#include<vector>


class A {
public:
    virtual void f() {}
};
class B : public A
{};
void fun(A* pa) {
    B* pb1 = static_cast<B*>(pa); //C风格直接强转也可以
    // 如果是pa指向的是A对象,则pb会变成子类类型的父类对象,因为pb是子类类型,能够访问到子类成员,如果此时pa访问子类成员,就会造成越界.因此不安全.
    B* pb2 = dynamic_cast<B*>(pa);
    std::cout << "pb1:" << pb1 << std::endl;
    std::cout << "pb2:" << pb2 << std::endl;
}
int main()
{
    A a;
    B b;
    fun(&a); //不安全
    fun(&b); //安全
    return 0;
}





