#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>


class A {
public:
    A(int a):_a(a) {
    }
    int _a ;
};

class B :virtual public A {
public:
    B(int b)    :A(2)
    {
    }
    int _b = 2;
};


class C :virtual public A {
public:
    C(int c) : A(3){
    }
    int _c = 3;
};

class D :public C, public B {
public:
    D():B(4),C(5),A(6){}
    int _d = 4;
};

int main() {
    //D *p = new D;
    D d;

    int a[3] = {1,2,3};

    return 0;
}

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
