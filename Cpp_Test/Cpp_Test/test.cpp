#include <iostream>
#include <thread>
#include <functional>
#include<chrono>
#include<future>

void func(std::promise<std::string>& pro) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pro.set_value("hello world");
    std::this_thread::sleep_for(std::chrono::seconds(1));

}

int main() {

    std::promise<std::string> pro;
    std::thread t1(func, std::ref(pro));

    auto fut = pro.get_future();
    while (true) {
        bool flag = false;
        std::future_status ret = fut.wait_for(std::chrono::seconds(1));
        switch (ret) {
        case std::future_status::deferred:              //只有async函数才有效
            std::cout << "异步线程还未启动" << "\n";
            break;
        case std::future_status::ready:
            std::cout << "结果已就绪" << "\n";
            flag = true;
            break;
        case std::future_status::timeout:
            std::cout << "等待超时" << "\n";
            break;
        default:
            std::cout << "结果异常" << "\n";
        }
        if (flag == true) {
            break;
        }
        std::cout << "do something..." << "\n";
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    }
    std::cout << "输出结果::" << fut.get() << "\n";

    t1.join();
    return 0;
}


//int main() {
//    std::promise<std::string>  pro;
//    std::thread t([&](){
//        std::this_thread::sleep_for(std::chrono::seconds(2));
//        pro.set_value("hello future");
//        std::this_thread::sleep_for(std::chrono::seconds(2));
//    });
//    
//    std::future<std::string> f = pro.get_future();
//    f.wait();
//    std::cout<<"get value:"<<f.get();
//
//   t.join();
//
//    return 0;
//}
