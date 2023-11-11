#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"2Date.h"
#include<vector>
#include<list>
#include<map>
struct Point
{
    int _x;
    int _y;
};

void 列表初始化()
{
    int x1 = 1;
    int x2 = { 2 };
    int x3{ 3 };

    int x4(1); //圆括号初始化可以认为是int的构造
}

void func(const int& a)
{
   std::cout<<"左值引用"<<std::endl;
}

void func(int&& a)
{
    std::cout<<"右值引用"<<std::endl;
}


int main()
{
    int a = 0;
    int b = 1;
    func(a);
    func(a+b);
    return 0;
}

