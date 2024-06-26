#include<iostream>
#include<thread>
#include<chrono>




int main() {
    std::cout<<std::this_thread::get_id()<<"\n";

    std::cout<<"sleep_for:10s"<<"\n";
        auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for<int>(std::chrono::duration<int>(10));
    std::cout<<"sleep_for:end"<<"\n";
        auto end = std::chrono::high_resolution_clock::now();
        auto ret = end - start;
        std::cout<<"计时器计时时长:"<<ret.count()<<"纳秒 == "<<ret.count()/ 1000000000<<"秒" << "\n";
        
    //std::chrono::nanoseconds ret = end - start;
    

        //std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
        //std::chrono::time_point<std::chrono::steady_clock> end= std::chrono::steady_clock::now();
        //std::chrono::duration<long long,std::nano> ret = end - start;
        //std::cout<<"计时器计时时长:"<<ret.count()<<"纳秒"<<ret.count()/ 1000000000<<"秒" << "\n";
  
    return 0;
}

