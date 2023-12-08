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


// 设计只能在栈上定义类(不能完全做到,最多只能禁止堆,不能禁止static区)
class HeapOnly
{
public:
    static HeapOnly createObj(int x = 0) 
    {
        HeapOnly ho;
        return ho;
    }
private:
    HeapOnly(int x = 0):_x(0)
    {}
    //HeapOnly(const HeapOnly& ho) = delete;
    //HeapOnly& operator=(const HeapOnly& ho) = delete;
    int _x;
};

int main()
{
    HeapOnly ho =  HeapOnly::createObj(0); //在栈上定义一个指针,调用类域内的静态函数createObj去new一个对象,得到对象的指针
    //HeapOnly ho1(*ho); //还需要禁掉拷贝构造
    return 0;
}













