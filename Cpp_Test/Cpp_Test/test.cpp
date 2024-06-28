#include<iostream>
#include<thread>
#include<chrono>
#include<cstdlib>
#include<mutex>


std::once_flag g_flag;

class Singleton {
public:
    Singleton(const Singleton& s) = delete;
    Singleton& operator=(const Singleton&s) = delete;
    static Singleton* GetInstance() {
        std::call_once(g_flag,[](){ std::cout<<"do once:"<<std::this_thread::get_id()<<"\n"; _instance = new Singleton; });
        std::cout<<std::this_thread::get_id()<<"\n";
        return _instance;
    }
    static void func() {

    }

private:
    Singleton(){};
    static Singleton* _instance;
};
Singleton* Singleton::_instance = nullptr;


int main() {
   std::thread t1(Singleton::GetInstance);
   std::thread t2(Singleton::GetInstance);
   std::thread t3(Singleton::GetInstance);
    
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

