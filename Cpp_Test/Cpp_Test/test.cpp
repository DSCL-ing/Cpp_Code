#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

template<typename T>
void func(T t)
{
    std::cout<<"template"<<std::endl;
}

void func(int t)
{
    std::cout<<"function"<<std::endl;
}

int main()
{
    func<int>(1);
    func(1);
    return 0;
}