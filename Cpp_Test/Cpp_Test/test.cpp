#include<iostream>
#include<chrono>
#include<ctime>
#include<windows.h>

#pragma warning(disable:4996)

std::string getTime()
{
    //struct tm
    //  int tm_sec;			 Seconds.	[0-60] (1 leap second)
    //  int tm_min;			 Minutes.	[0-59] 
    //  int tm_hour;		 Hours.	[0-23] 
    //  int tm_mday;		 Day.		[1-31] 
    //  int tm_mon;			 Month.	[0-11] 
    //  int tm_year;		 Year	- 1900.  
    //  int tm_wday;		 Day of week.	[0-6]
    //  int tm_yday;		 Days in year.[0-365]
    //  int tm_isdst;		 DST.		[-1/0/1]

    time_t curr = time(nullptr);
    struct tm* tmp = localtime(&curr); //参数事time_t类型的时间戳
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%d-%d-%d %d:%d:%d", tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
    return buffer;
}

int main() {

    //auto nt = std::chrono::system_clock().now();
    //auto t = std::chrono::system_clock::to_time_t(nt);
    //std::cout<<ctime(&t)<<"\n";
    //std::cout<<nt.time_since_epoch().count()<<std::endl;
    ////std::cout<<getTime()<<std::endl;

    //std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
    //Sleep(1000);
    //std::chrono::steady_clock::time_point end= std::chrono::high_resolution_clock::now();
    ////std::chrono::steady_clock::time_point ret = end - start;
    //auto ret = end -start;
    //std::cout<<ret.count()<<std::endl;

    std::chrono::system_clock::time_point epoch;  //新纪元起始
    std::cout<<epoch.time_since_epoch().count()<<"\n";

    std::chrono::duration<long long> day(std::chrono::hours(24));
    //std::chrono::hours day(24); //相同

    std::chrono::system_clock::time_point epoch1 = epoch+day;
    //std::chrono::system_clock::time_point epoch1(epoch+day); //相同
    std::cout<<epoch1.time_since_epoch().count()<<"\n"; //法一
   
    std::chrono::system_clock::time_point now_time =  std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(now_time);
    std::cout<<ctime(&time)<<"\n";
    std::cout<<now_time.time_since_epoch().count()<<"\n"; //获取时间戳后还需要将时间戳转换工具转换
    return 0;
}

