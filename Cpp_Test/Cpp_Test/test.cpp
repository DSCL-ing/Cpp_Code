#include<iostream>                  //std::cout 
#include<thread>                    //std::thread
#include<queue>                     //std::queue
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include<chrono>


int main()
{
    std::atomic_int a_i = 10;
    std::cout<<a_i<<"\n";
    return 0;
}

