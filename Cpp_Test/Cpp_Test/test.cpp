#include<iostream>
#include<thread>
#include<chrono>
#include<cstdlib>

#pragma warning(disable:4996)

//int g_val;

void func1() {
    do {
        std::cout << std::this_thread::get_id() << "\n";
    } while (1);
}


void func2() {
    do {
        std::cout << std::this_thread::get_id() << "\n";
        _sleep(100);
    } while (true);
}

int main() {
    
    std::thread t2(func2);
    t2.detach();
    _sleep(1000);


    //std::thread t1(func1);
    //std::thread t2(func2);
    //t1.join();
    //t2.detach();
    //t2.join();
    //_sleep(1000);
    return 0;
}

