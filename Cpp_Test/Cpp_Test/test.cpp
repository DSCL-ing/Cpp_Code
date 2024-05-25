#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

template<class T>
void func(T* t)
{
    std::cout<<"Function template"<<std::endl;
    std::cout<<t<<std::endl;
}

//template<class T>
//void func<T*>(T* t)
//{
//    std::cout<<"Function Template Specialization "<<std::endl;
//}

//template<>
//void func<int*>(int*p)
//{
//
//    std::cout<<"Function"<<std::endl;
//}

int main()
{
    func<int>(nullptr);
    //func(1);
    return 0;
}