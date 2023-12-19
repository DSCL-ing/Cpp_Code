#define _CRT_SECURE_NO_WARNINGS 1

#include <ctime>
#include <random>
#include <iostream>
#include<string.h>
#include<algorithm>
#include<string>
#include<map>
#include<memory>
#include<mutex>
#include<thread>
#include<functional>
#include<vector>




int main()
{
    volatile const  int a = 2;
    int* p = const_cast<int*>(&a);
    *p = 3;
    std::cout << a << std::endl;
    std::cout << *p << std::endl;
    return 0 ;
}





