#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
#include<cstdio>
#include<functional>
#include<array>
#include<vector>

int main() {
    long long n1;
    long long int n2;
    signed long long n3;
    signed long long int n4;
    std::cout<<typeid(n1).name()<<"\n";
    std::cout<<typeid(n2).name()<<"\n";
    std::cout<<typeid(n3).name()<<"\n";
    std::cout<<typeid(n4).name()<<"\n";
    std::cout<<sizeof(n1)<<"\n";
    return 0;
}