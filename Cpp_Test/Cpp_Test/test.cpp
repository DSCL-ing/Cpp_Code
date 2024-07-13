#include <iostream>
#include <thread>
#include <functional>
#include<chrono>
#include<future>
#include<string>

#include <type_traits>
#include <iostream>

using namespace std;

struct B
{
protected:
    virtual void Foo() {}
};

// Neither trivial nor standard-layout
struct A : B
{
    int a;
    int b;
    void Foo() override {} // Virtual function
};

// Trivial but not standard-layout
struct C
{
    int a;
private:
    int b;   // Different access control
};

// Standard-layout but not trivial
struct D
{
    int a;
    int b;
    D() {} //User-defined constructor
};

struct POD
{
    POD() = delete;
    int a;
    int b;
    static void fun(){};
};

int main()
{
    cout << boolalpha;


    cout << "B is trivial is " << is_trivial<B>() << endl; // false
    cout << "B is standard-layout is " << is_standard_layout<B>() << endl;  // false

    cout << "A is trivial is " << is_trivial<A>() << endl; // false
    cout << "A is standard-layout is " << is_standard_layout<A>() << endl;  // false

    cout << "C is trivial is " << is_trivial<C>() << endl; // true
    cout << "C is standard-layout is " << is_standard_layout<C>() << endl;  // false

    cout << "D is trivial is " << is_trivial<D>() << endl;  // false
    cout << "D is standard-layout is " << is_standard_layout<D>() << endl; // true

    cout << "POD is trivial is " << is_trivial<POD>() << endl; // true
    cout << "POD is standard-layout is " << is_standard_layout<POD>() << endl; // true

    return 0;
}


//class A {
//    A();
//    public:
//    int a;
//    private:
//    int b;
//};
//
//class Base {
//};
//
//class Base2{
//
//};
//
//class Child : public Base ,public Base2{
//public:
//    int j;
//    float f;
//    A p;
//};
//int main() {
//    std::cout << "Is Base standard layout: " << std::is_standard_layout<Base>::value << std::endl;
//    std::cout << "Is Child standard layout: " << std::is_standard_layout<Child>::value << std::endl;
//    return 0;
//}
//struct Base
//{
//    //static int a;
//    double d;
//};
//
//struct Child : public Base
//{
//    //static int c;
//    float b;
//};          // ok

//struct Base1
//{
//    int a;
//};
//
//struct Child1 : public Base1
//{
//    static int c;
//}; // ok
//
//struct Child2 :public Base, public Base1 {
//    static int d;
//}; // ok
//
//struct Child3 :public Base1 { int d; };         // error
//
//struct Child4 :public Base1, public Child     // error
//{
//    static int num;
//};

//int main() {
//    std::cout << std::is_standard_layout<Base>::value << "\n";
//    std::cout << std::is_standard_layout<Child>::value << "\n";
//
//    return 0;
//}