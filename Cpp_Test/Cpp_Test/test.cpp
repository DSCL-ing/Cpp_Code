#include<iostream>                  //std::cout 
#include<thread>                    //std::thread
#include<queue>                     //std::queue
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include<chrono>

struct Counter
{
    void increment()
    {
        for (int i = 0; i < 100000000; ++i)
        {
            std::lock_guard<std::mutex> locker(m_mutex);
            m_value++;
        }
    }

    void decrement()
    {
        for (int i = 0; i < 100000000; ++i)
        {
            std::lock_guard<std::mutex> locker(m_mutex);
            m_value--;
        }
    }

    int m_value = 0;
    //std::atomic_int m_value = 0;
    std::mutex m_mutex;
};

int main()
{
    Counter c;
    auto increment = std::bind(&Counter::increment, &c);
    auto decrement = std::bind(&Counter::decrement, &c);

    std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::thread t1(increment);
    std::thread t2(decrement);
    //auto ret = end -start;
    t1.join();
    t2.join();
    std::chrono::steady_clock::time_point end  = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::nano> ret = end -start;
    std::cout<<"Counter: "<<c.m_value<<"\n";
    std::cout<<ret.count()/1000000000<<"秒" << "\n";
    return 0;

}

