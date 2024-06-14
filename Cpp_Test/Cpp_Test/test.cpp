#include<iostream>

template<class T>
class SmartPtr {
public:
    SmartPtr(T*ptr):_ptr(ptr) 
    {}
    ~SmartPtr() {
        delete _ptr;
        std::cout<<"delete ptr"<<"\n";
    }
    T& operator*() {
        return *_ptr;
    }
    T* operator->() {
        return _ptr;
    }
private:
    T*_ptr;
};

int main()
{
    SmartPtr<int> sp1(new int);
    SmartPtr<int> sp2(new int);
    *sp1 = 10; 
    std::cout<< *sp1 <<std::endl;

    return 0;
}

//int div()
//{
//    int a, b;
//    std::cin >> a >> b;
//    if (b == 0)
//        throw std::invalid_argument("除0错误");
//    return a / b;
//}
//
//void example() {
//    SmartPtr<int> sp1(new int);
//    SmartPtr<int> sp2(new int);
//    try {
//        div();
//    }
//    catch (...) {
//        throw;
//    }
//}
//
//int main() {
//    try {
//        example();
//    }
//    catch (std::exception& e) {
//        std::cout << e.what() << std::endl;
//    }
//}