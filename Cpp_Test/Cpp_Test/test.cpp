#include<iostream>
#include<thread>
#include<chrono>
#include<cstdlib>
#include<mutex>

#pragma warning(disable:4996)

int g_val;
std::mutex mtx;

void other() {
    std::cout << "do other thing" << "\n";
}

void func() {
    while (true) {
        _sleep(100);
        //while (mtx.try_lock() == false)
        //    other();
        //std::cout << g_val++ << "\n";
        mtx.unlock();
    }
}



int main() {
    std::recursive_timed_mutex t;
    std::thread t1(func);
    std::thread t2(func);
    std::thread t3(func);

    t1.join();
    t2.join();
    t3.join();


    //std::thread t1(func1);
    //std::thread t2(func2);
    //t1.join();
    //t2.detach();
    //t2.join();
    //_sleep(1000);
    return 0;
}

