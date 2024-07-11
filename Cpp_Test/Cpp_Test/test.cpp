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
#include<set>
#include<string>

void solution(std::string& str) {
    bool flag = false;
    int start = 0;
    int end = str.size() - 1;
    for (start; start <= end; start++) {
        for (int i = start; i <= end;) {
            if (i != end && str[i] == str[i + 1]) {
                i = i + 1;
            }
            else {
                if (start<i&&str[start] == str[i]) {
                    str.erase(start ,i-start+1);
                    end = str.size() - 1;
                    flag = true;
                }
                break;
            }
        }
        if (flag == true) {
            break;
        }
    }
    if (flag == false) {
        return;
    }
    solution(str);
}

int main() {
    std::string str;
    while (std::cin >> str) {
        solution(str);
        std::cout << str << "\n";
    }
}



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
