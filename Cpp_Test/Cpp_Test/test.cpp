#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>


class A final
{
};

class B : public A
{
};

int main(int argc, char* argv[])
{
    B* p = new B;
    p->test();
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
