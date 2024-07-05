#include<iostream> //std::cout 
#include<thread> //std::thread
#include<queue> //std::queue
#include<condition_variable> //std::condition_variable
#include<mutex> //std::mutex, std::unique_lock, std::lock_guard
#include<functional> //std::bind


struct A {
    A() = default;
    int operator=(int i) {  //只给a重载
        _a = i;
        return _a;
    }
    A& operator=(const A& a) { //拷贝构造作用
        _a = a._a;
        _b = a._b;
        return *this;
    }
    int _a = 0;
    int _b = 0;
};

int main() {
    return 0;
}

