#pragma once
#define _CRT_SECURE_NO_WARNINGS 1


#include <ctime>
#include <random>
#include <iostream>
using std::cout;
using std::endl;
#include<string.h>
#include<algorithm>

#include<string>
#include<map>

class A
{
public:
    std::map<std::string, int> _m;

    class B
    {
        //A* a;
        public:
        void fun()
        {
            a->_m[""];
        }
    };

};

int main()
{
    A a;
    A::B b;
       b.fun();
	return 0;

}







