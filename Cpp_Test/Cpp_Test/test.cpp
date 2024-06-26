#include<iostream>
#include<thread>
#include<chrono>
#include<cstdlib>

#pragma warning(disable:4996)

int g_count;

void func1() {
    do {
        std::cout << std::this_thread::get_id() << "\n";
    } while (true);
}


void func2() {
    do {
        std::this_thread::yield();
        std::cout << std::this_thread::get_id() << "\n";
    } while (true);
}

int main() {

    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();
    return 0;
}

