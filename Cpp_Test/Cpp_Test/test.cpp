#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>


class A {
public:
     virtual void func()  {}
};

class B : public A {
public:
    void func(int i) override{ }
};

int main(int argc, char* argv[])
{
    return 0;
}

//class Person {
//public:
//     void BuyTicket(int val = 1) {
//        std::cout << "全票" <<":"<<val<<"\n";
//    }
//    void call() {
//        BuyTicket();
//    }
//};
//
//class Student :public Person {
//public:
//    void BuyTicket(int val = 0) {
//        std::cout << "半票" <<"="<<val<<"\n";
//    }
//};
//
//int main(){
//    Student s;
//    s.call();
//    s.BuyTicket();
//    return 0;
//}
