#include <iostream>
#include <thread>
#include <functional>
#include<chrono>
#include<future>
#include<string>

class Base {
public:
    using funcptr = std::string(*)(std::string, int num);

public:
    std::string operator()(std::string msg) {
        return std::string("operator(): " + msg);
    }
    operator funcptr() { //若类型转换成函数,可以通过仿函数方式直接使用对象()进行调用;但如果与operator()的函数指针类型相同,则只会使用operator(),而不会调用operator T(),即operator T()被隐藏. 
        return Showmsg; //为了区分两者,可使用不同的函数指针类型.
    }
    static std::string Showmsg(std::string msg, int num) {
        return std::string("showmsg(): " + msg + std::to_string(num));
    }
    std::string func(std::string msg) {
        return std::string("func(): " + msg);
    }
private:
};

int main() {
    std::cout << Base()("hello") << "\n";       //operator ()()
    std::cout << Base()("hello", 1) << "\n";   //operator T()()
    std::cout << Base() << "\n";                //operator T()

    Base b;
    std::packaged_task<std::string(std::string)> p_task1(b);
    std::packaged_task<std::string(std::string, int)> p_task2(b);
    std::packaged_task<std::string(std::string, int)> p_task3(std::bind(Base::Showmsg, "hello", 3));  //最好的用法,是让bind自动推导模板参数 
    std::packaged_task<std::string(std::string)> p_task4(std::bind(&Base::func, &b,std::placeholders::_1));

    p_task1("p_tast1 hello");
    p_task2("p_tast2 hello", 2);
    p_task3("p_task3 hello", 3);
    p_task4("p_task4 hello");

    std::future<std::string> fut1 = p_task1.get_future();
    std::future<std::string> fut2 = p_task2.get_future();
    std::future<std::string> fut3 = p_task3.get_future();
    std::future<std::string> fut4 = p_task4.get_future();

    puts("");
    std::cout << fut1.get() << "\n";
    std::cout << fut2.get() << "\n";
    std::cout << fut3.get() << "\n";
    std::cout << fut4.get() << "\n";

    return 0;
}



//void func(std::promise<std::string>& pro) {
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    pro.set_value("hello world");
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//
//}
//
//int main() {
//
//    std::promise<std::string> pro;
//    std::thread t1(func, std::ref(pro));
//
//    auto fut = pro.get_future();
//    while (true) {
//        bool flag = false;
//        std::future_status ret = fut.wait_for(std::chrono::seconds(1));
//        switch (ret) {
//        case std::future_status::deferred:              //只有async函数才有效
//            std::cout << "异步线程还未启动" << "\n";
//            break;
//        case std::future_status::ready:
//            std::cout << "结果已就绪" << "\n";
//            flag = true;
//            break;
//        case std::future_status::timeout:
//            std::cout << "等待超时" << "\n";
//            break;
//        default:
//            std::cout << "结果异常" << "\n";
//        }
//        if (flag == true) {
//            break;
//        }
//        std::cout << "do something..." << "\n";
//        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
//    }
//    std::cout << "输出结果::" << fut.get() << "\n";
//
//    t1.join();
//    return 0;
//}
