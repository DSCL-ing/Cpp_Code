﻿#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>



class A {
public:
    virtual void fun1(){
        std::cout<<"func1()"<<"\n";
    }
    virtual void fun2(){
        std::cout<<"func2()"<<"\n";
    }
};

class B :public A {
public:
    virtual void fun3(){
        std::cout<<"func3()"<<"\n";
    }
};

using VFPTR = void(*)(void);
void PrintVFTable(VFPTR table[])
{
    for (int i = 0; table[i]; i++)
    {
        printf("%p\n",table[i]);
    }
}

int main()
{
    A a;
    B b;
    PrintVFTable((VFPTR*)(*((int*)&a)));
    puts("");
    PrintVFTable(*(VFPTR**)&b);
    return 0;
}


//class Base {
//public:
//    virtual void func() {}
//private:
//    int _a = 1;
//    char _b;
//};
//
//int main()
//{
//    std::cout << sizeof(Base) << "\n";
//    Base b;
//    return 0;
//}
//


//class A {
////public:
//private:
//    int _a = 1;
//};
//
//class B : public A {
//public:
//    int _b = 2;
//};
//
//class C : public A {
//public:
//    int _c = 3;
//};
//
//class D :public B, public C {
//public:
//    int _d = 4;
//};
//
//int main()
//{
//    //B b;
//    //C c;
//    D d;
//    std::cout<<sizeof(D)<<"\n";
//}
//

//class Base{
//public:
//     void func() {}
//private:
//    int _a;
//    char _b;
//};
//
//
//class Driver :public Base {
//
//};
//
//int main(int argc, char* argv[])
//{
//    std::cout<<sizeof(Base)<<"\n";
//    std::cout<<sizeof(Driver)<<"\n";
//    return 0;
//}

//class Person {
//public:
//    virtual void BuyTicket(int val = 1) {
//        std::cout << "全票" << ":" << val << "\n";
//    }
//    virtual void func(int val = 1) {
//        std::cout << "全票" << ":" << val << "\n";
//    }
//};
//
//class Student :public Person {
//public:
//    void BuyTicket(int val = 0) {
//        std::cout << "半票" << "=" << val << "\n";
//    }
//    virtual int Add()
//    {
//        std::cout<<"Studetn"<<"\n";
//        return 0;
//    }
//};
//
//class C : public Student {
//public:
//    virtual int Add()
//    {
//        std::cout<<"C"<<"\n";
//        return 0;
//    }
//    int _c = 3;
//};
//
//void fun(Student &s)
//{
//    s.Add();
//}
//
//int main() {
//    Person p;
//    Student s;
//    C c;
//    fun(c);
//    return 0;
//}
