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





int main()
{
    std::vector<int> v1 = { 1,23,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }; //
    std::list<int> l1 = { 1,1,1,1,1,1,1,11,1,1,1 };

    auto i1 = { 1,1,1,1,1,1,1,1,1,1,1 };
    //std::cout << typeid(i1).name() << std::endl; 
    std::initializer_list<int>::iterator it = i1.begin();
    std::cout<<it<<std::endl;
    std::map<std::string, std::string> dict{ {"1","1"},{"2","2"} };

    //pair支持花括号 -- 和圆括号一样
    std::pair<int, int> kv = { 2,2 };
    return 0;
}

