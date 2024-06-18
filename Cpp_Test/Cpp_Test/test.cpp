#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
#include<cstdio>
#include<functional>
#include<array>
#include<vector>

int main() {
    auto bar = std::make_shared<int>(10);
    auto foo(std::make_shared<int>(10));
    auto foo1 = std::make_shared<std::array<char, 64>>();
    auto foo2 = std::make_shared<std::vector<int>>(10,0);
    auto foo3 = std::make_shared<std::vector<int>>(10);

    return 0;
}
