#include <iostream>
#include <thread>
#include <functional>
#include<chrono>
#include<future>
#include<string>


template<class T = int, class U = int>
auto Add(T t, U u)->decltype(t + u) {
    return t + u;
}


int main() {
    std::cout << Add(1, 1.1) << "\n";
    return 0;
}
