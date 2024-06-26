#include<iostream>
#include<thread>
#include<chrono>

template<class T>
void func(std::chrono::duration<T> d) {

}

int main() {
    func(std::chrono::duration<long long>());
    func(std::chrono::seconds());

    std::cout<<std::this_thread::get_id()<<"\n";

    std::cout<<"sleep_for:10s"<<"\n";
    //std::this_thread::sleep_until
    std::cout<<"sleep_for:end"<<"\n";


    //std::chrono::nanoseconds ret = end - start;
    

        //std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
        //std::chrono::time_point<std::chrono::steady_clock> end= std::chrono::steady_clock::now();
        //std::chrono::duration<long long,std::nano> ret = end - start;
        //std::cout<<"计时器计时时长:"<<ret.count()<<"纳秒"<<ret.count()/ 1000000000<<"秒" << "\n";
  
    return 0;
}

