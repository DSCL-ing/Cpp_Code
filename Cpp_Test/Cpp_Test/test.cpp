#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

template<class T>
class SmartPtr {
public:
    SmartPtr(T*ptr):_ptr(ptr) 
    {}
    ~SmartPtr() {
        delete _ptr;
        std::cout<<"delete ptr"<<"\n";
    }
private:
    T*_ptr;
};

int div()
{
    int a, b;
    std::cin >> a >> b;
    if (b == 0)
        throw std::invalid_argument("除0错误");
    return a / b;
}

void example() {
    SmartPtr<int> sp1(new int);
    SmartPtr<int> sp2(new int);
    try {
        div();
    }
    catch (...) {
        throw;
    }
}

int main() {
    try {
        example();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}