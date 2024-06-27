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
        _sleep(100);
    } while (true);
}

class A {
public:
    static void fun1(){}
     void fun2(){std::cout<<"func2()"<<"\n"; }

};

int main() {

    std::thread t1(std::bind(&A::fun2,A()));
    t1.join();
 
 
    //std::thread t1(func1);
    //std::thread t2(func2);
    //t1.join();
    //t2.detach();
    //t2.join();
    //_sleep(1000);
    return 0;
}

