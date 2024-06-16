#include<iostream>

namespace test {

    template<class T>
    class auto_ptr {
    public:
        auto_ptr(T* ptr) :_ptr(ptr)
        {}

        auto_ptr(auto_ptr& ap) {
            _ptr = ap._ptr;
            ap._ptr = nullptr;
        }

        ~auto_ptr() {
            delete _ptr;
            std::cout << "delete ptr" << "\n";
        }
        T& operator*() {
            return *_ptr;
        }
        T* operator->() {
            return _ptr;
        }
    private:
        T* _ptr;
    };
}

int main() {
    test::auto_ptr<int> ap1(new int);
    test::auto_ptr<int> ap2(ap1);

    *ap1 = 1;
    *ap2 = 1;

    return 0;
}

//template<class T>
//class SmartPtr {
//public:
//    SmartPtr(T* ptr) :_ptr(ptr)
//    {}
//
//    ~SmartPtr() {
//        delete _ptr;
//        std::cout << "delete ptr" << "\n";
//    }
//    T& operator*() {
//        return *_ptr;
//    }
//    T* operator->() {
//        return _ptr;
//    }
//private:
//    T* _ptr;
//};

//int main()
//{
//    SmartPtr<int> sp1(new int);
//    SmartPtr<int> sp2(sp1);
//
//    return 0;
//}




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