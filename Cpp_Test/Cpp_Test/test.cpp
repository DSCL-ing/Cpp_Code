#include<iostream>                  //std::cout 
#include<thread>                    //std::thread
#include<queue>                     //std::queue
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include<chrono>
#include<future>


//#include <iostream>
//#include <thread>

//int main() {
//    int x = 5;
//    int y = 7;
//
//    // 创建一个线程，执行一个lambda表达式，捕获x和y的引用
//    std::thread t([&]() {
//        std::cout << "Sum: " << x++ + ++y << std::endl;
//        });
//
//    // 等待线程完成
//    t.join();
//
//    return 0;
//}


int main() {
    std::promise<std::string>  pro;
    std::thread t([&](){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        pro.set_value("hello future");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    });
    
    std::future<std::string> f = pro.get_future();
    f.wait();
    std::cout<<"get value:"<<f.get();

   t.join();

    return 0;
}
