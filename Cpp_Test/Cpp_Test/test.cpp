#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include"9Date.h"

template<class T>
struct Less {
    bool operator()(const T& left, const T& right) {
        return left < right;
    }
};

////全特化
//template<>
//struct Less<Date*> {
//    bool operator()(Date* left, Date* right) {
//        std::cout<<"full specialization"<<std::endl;
//        return *left < *right;
//    }
//};

//偏特化
template<class T>
struct Less<T*> {
    bool operator()(T* left, T* right) {
        std::cout<<"partial specialization"<<std::endl;
        return *left < *right;
    }
};



int main()
{
    Date d1(1111,11,11); 
    Date d2(2222,12,12);
        
    Less<Date*>()(&d1,&d2);

    return 0;
}