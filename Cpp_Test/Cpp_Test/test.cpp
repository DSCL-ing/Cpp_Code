#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
#include<cstdio>
#include<functional>
#include<array>
#include<vector>
#include<string>

int main() {
    std::string str = "123a123a";
    size_t n= 0;
    int a = std::stoi(str,&n, 10);
    std::cout<<a<<", char:"<<n << "\n";

    

    return 0;
}