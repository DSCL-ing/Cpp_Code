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

template<typename ToDuration>
using MyTimePoint = std::chrono::time_point<std::chrono::system_clock,ToDuration>;

int main() {
   
  
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> millis; 
    std::chrono::time_point<std::chrono::system_clock,std::chrono::seconds> s = std::chrono::time_point_cast<std::chrono::seconds>(millis); 



 
    return 0;
}

