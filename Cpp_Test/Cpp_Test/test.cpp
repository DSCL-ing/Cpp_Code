#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
#include<cstdio>
#include<functional>
#include<array>

int main() {
    auto bar = std::make_shared<int>(10);
    auto foo(std::make_shared<int>(10));
    auto foo1 = std::make_shared<std::array<char, 64>>();
    return 0;
}
