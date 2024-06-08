#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>


class Base1 {
public:
    virtual void func1() { std::cout << "Base1::func1" <<std::endl; }
    virtual void func2() { std::cout << "Base1::func2" <<  std::endl; }
private:
    int b1 = 1;
};

class Base2 {
public:
    virtual void func1() { std::cout << "Base2::func1" << std::endl; }
    virtual void func2() { std::cout << "Base2::func2" << std::endl; }
private:
    int b2 = 1;
};

class Derive : public Base1, public Base2 {
public:
    virtual void func1() { std::cout << "Derive::func1" << std::endl; }
    virtual void func3() { std::cout << "Derive::func3" << std::endl; }
private:
    int d1 =2;
};

using VFPTR = void(*)(void);
void PrintVFTable(VFPTR table[])
{
    for (int i = 0; table[i]; i++)
    {
        printf("%p", table[i]);
        VFPTR f = table[i];
        f();
    }
}
int main()
{
    Derive d;
    Base1 *ptr1 = &d;
    Base2 *ptr2 = &d;
    ptr1->func1();
    ptr2->func2();
    return 0;
}



//class A {
//public:
//    virtual void fun1(){
//        std::cout << "func1()" << "\n";
//    }
//    virtual void fun2(){
//        std::cout <<"func2()"<<"\n";
//    }
//};
//
//class B :public A {
//public:
//    virtual void fun3(){
//        std::cout <<"func3()"<<"\n";
//    }
//};
//
//using VFPTR = void(*)(void);
//void PrintVFTable(VFPTR table[])
//{
//    for (int i = 0; table[i]; i++)
//    {
//        printf("%p -> ",table[i]);
//        VFPTR f = table[i];
//        f();
//    }
//}
//
//int main()
//{
//    A a;
//    B b;
//    PrintVFTable((VFPTR*)(*((VFPTR*)&a)));
//    puts("");
//    PrintVFTable(*(VFPTR**)&b);
//    return 0;
//}


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
//    virtual void func(){
//    }
//private:
//    int _a;
//};
//
//class Derive :public Base {
//};
//
//int main()
//{
//    Base b;
//    Derive d;
//    int x = 0;
//    int *y = new int;
//    static int z = 1;
//    const char * str = "hello world";
//
//    printf("栈对象地址:        %p\n",&x);
//    printf("堆对象地址:        %p\n",y);
//    printf("静态区对象地址:    %p\n",&z);
//    printf("常量区对象地址:    %p\n",str);
//    printf("Base对象虚表指针:  %p\n",*(int**)(&b)); //32位环境
//    printf("Derive对象虚表指针:%p\n",*(int**)(&d)); 
//
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
