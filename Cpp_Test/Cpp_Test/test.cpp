#include<iostream>

namespace test {
    template<class T>
    class unique_ptr {
    public:
        unique_ptr(T* ptr) :_ptr(ptr)
        {}

        ~unique_ptr() {
            delete _ptr;
            std::cout << "delete ptr" << "\n";
        }
        T& operator*() {
            return *_ptr;
        }
        T* operator->() {
            return _ptr;
        }

        //C++11封拷贝 
        //unique_ptr(const unique_ptr<T>& up) = delete;
        //unique_ptr<T>& operator = (const unique_ptr<T>&up) = delete;
    private:
        //C++98封拷贝
        unique_ptr(const unique_ptr<T>& up); //C++98
        unique_ptr<T>& operator=(const unique_ptr<T>&up);

        T* _ptr;
    };
}

int main() {
    test::unique_ptr<int> up1(new int);
    test::unique_ptr<int> up2(up1);


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