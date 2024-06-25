#include<iostream>

#include<chrono>

int main() {

    std::chrono::duration<double, std::ratio<9, 7>> d1(3); //单位为9/7秒
    std::chrono::duration<double, std::ratio<6, 5>> d2(1); //单位为6/5秒
    /*
    9和6的最大公约数是3;
    7和5的最小公倍数是35;
    */
    // d1 和 d2 统一之后的时钟周期
    std::chrono::duration<double, std::ratio<3, 35>> d4 = d1 - d2; 
    auto d3 = d1 - d2;
    std::cout<<d3.count()<<"\n";
    std::cout<<d4.count()<<"\n";




    //std::chrono::duration<int> a(1);
    //std::chrono::duration<int ,std::milli> b(10);
    //std::chrono::duration<int ,std::ratio<1,1000000>>  c(100);

    //std::cout<<a.count()<<std::endl;
    //std::cout<<b.count()<<std::endl;
    //std::cout<<c.count()<<std::endl;

    //std::chrono::hours h(2);             //2小时
    //std::chrono::minutes min(3);         //3分钟
    //std::chrono::seconds sec(4);         //4秒钟
    //std::chrono::milliseconds millis(5); //5毫秒
    //std::chrono::microseconds micros(6); //6微秒
    //std::chrono::nanoseconds nanos(7);   //7纳秒

    return 0;
}

