#include<iostream>                  //std::cout 
#include<thread>                    //std::thread
#include<queue>                     //std::queue
#include<condition_variable>        //std::condition_variable
#include<mutex>                     //std::mutex, std::unique_lock, std::lock_guard
#include<functional>                //std::bind
#include <cstring>
#include<atomic>

template<class T>
struct A {
    operator T() {
        return ++_a;
    }
    T _a = 0;
};

int main() {
    A<int> a;
    std::cout << a << "\n";
    //std::cout<<
    std::cin << 1<<"\n";
}
