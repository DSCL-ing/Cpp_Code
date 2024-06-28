#include<iostream>
#include<thread>
#include<chrono>
#include<cstdlib>
#include<functional>

#pragma warning(disable:4996)

//int g_val;

void func1() {
    do {
        std::cout << std::this_thread::get_id() << "\n";
    } while (1);
}


void func2() {
    do {
        //std::cout << std::this_thread::get_id() << "\n";
        //_sleep(100);
    } while (0);
}


int main() {

    //std::thread t1;
    //if (t1.joinable() == true)
    //{
    //    t1.join();
    //}
    std::thread t1(func2);
    std::thread::native_handle_type t = t1.native_handle();
    printf("%d",t);
    t1.join();

    std::cout<<std::thread::hardware_concurrency()<<"\n";

    //std::thread t1(func1);
    //std::thread t2(func2);
    //t1.join();
    //t2.detach();
    //t2.join();
    //_sleep(1000);
    return 0;
}

