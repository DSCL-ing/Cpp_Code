#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
#include<cstdio>
#include<functional>

#pragma warning(disable:4996)

namespace test {
    template<class T>
    class shared_ptr {
    public:
        shared_ptr() : _ptr(nullptr), _pRefCount(new int(0)), _pmtx(new std::mutex)
        {}

        shared_ptr(T* ptr) :_ptr(ptr), _pRefCount(new int(1)), _pmtx(new std::mutex)
        {}

        shared_ptr(const shared_ptr<T>& sp) :_ptr(sp._ptr), _pRefCount(sp._pRefCount), _pmtx(sp._pmtx) {
            AddRef();
        }

        template<class T, class D>
        shared_ptr(T* ptr, D del) : shared_ptr(ptr) {
            _del = del;
        }


        ~shared_ptr() {
            Release();
        }

        shared_ptr<T>& operator=(const shared_ptr<T>& sp) {
            if (_ptr != sp._ptr)
            {
                if (*_pRefCount == 0) //天生就为0
                {
                }
                else {
                    Release();
                }

                _ptr = sp._ptr;
                _pRefCount = sp._pRefCount;
                _pmtx = sp._pmtx;
                AddRef();
            }
            return *this;
        }

        void Release() {
            _pmtx->lock();
            if (--(*_pRefCount) <= 0) {
                _pmtx->unlock();
                //delete _ptr;
                _del(_ptr);
                delete _pRefCount;
                delete _pmtx;
                std::cout << "delete " << _ptr << "\n";
            }
            else {
                _pmtx->unlock();
            }
        }

        void AddRef() {
            _pmtx->lock();
            ++(*_pRefCount);
            _pmtx->unlock();
        }

        T& operator*() {
            return *_ptr;
        }
        T* operator->() {
            return _ptr;
        }

        T* get() const {
            return _ptr;
        }

        int use_count() const {
            return *_pRefCount;
        }


    private:
        T* _ptr;
        int* _pRefCount;
        std::mutex* _pmtx;
        std::function<void(T* ptr)> _del = [](T*ptr){delete ptr;};
    };
}


struct Date
{
    int _year = 0;
    int _month = 0;
    int _day = 0;
    ~Date() {
        std::cout << "~Date()" << "\n";
    }
};

template<class T>
struct DeleteArray {
    void operator()(T* ptr) {
        delete[] ptr;
    }
};



int main() {
    test::shared_ptr<Date> sp0(new Date);
    test::shared_ptr<Date> sp1(new Date[10], DeleteArray<Date>());
    test::shared_ptr<Date> sp2(new Date[10], [](Date* ptr) {delete[] ptr; });
    test::shared_ptr<FILE> sp3(fopen("test.cpp", "r"), [](FILE* ptr) {std::cout << "fclose()" << "\n"; fclose(ptr); });
    return 0;
}

//    template<class T>
//    class weak_ptr
//    {
//    public:
//        weak_ptr()
//            :_ptr(nullptr)
//        {}
//
//        weak_ptr(const shared_ptr<T>& sp)
//            :_ptr(sp.get())
//        {}
//
//        weak_ptr<T>& operator=(const shared_ptr<T>& sp)
//        {
//            _ptr = sp.get();
//
//            return *this;
//        }
//
//        T& operator*()
//        {
//            return *_ptr;
//        }
//
//        T* operator->()
//        {
//            return _ptr;
//        }
//
//    private:
//        T* _ptr;
//    };
//
//}


//struct ListNode
//{
//    int _data;
//    test::weak_ptr<ListNode> _prev;
//    test::weak_ptr<ListNode> _next;
//
//    ~ListNode() { std::cout << "~ListNode()" << std::endl; }
//};

//int main() {
//    test::shared_ptr<ListNode> sp1(new ListNode);
//    test::shared_ptr<ListNode> sp2(new ListNode);
//    sp1->_next = sp2;
//    sp2->_prev = sp1;
//    return 0;
//}

//struct Date
//{
//    int _year = 0;
//    int _month = 0;
//    int _day = 0;
//};
//
////void SharePtrFunc(test::shared_ptr<Date>& sp, size_t n)
//void SharePtrFunc(std::shared_ptr<Date>& sp, size_t n)
//{
//    for (size_t i = 0; i < n; ++i)
//    {
//        //test::shared_ptr<Date> copy(sp);
//        std::shared_ptr<Date> copy(sp);
//        copy->_year++;
//        copy->_month++;
//        copy->_day++;
//    }
//}
//
//int main() {
//    //test::shared_ptr<Date> sp (new Date);
//    std::shared_ptr<Date> sp (new Date);
//
//    const size_t n = 1000000;
//    std::thread t1(SharePtrFunc, std::ref(sp), n);
//    std::thread t2(SharePtrFunc, std::ref(sp), n);
//    std::thread t3(SharePtrFunc, std::ref(sp), n);
//
//    t1.join();
//    t2.join();
//    t3.join();
//
//    std::cout<<sp.use_count()<<"\n";
//    std::cout<<sp->_year<<"\n";
//    std::cout<<sp->_month<<"\n";
//    std::cout<<sp->_day<<"\n";
//    return 0;
//}

//int main() {
//    test::shared_ptr<int> sp1(new int(1));
//    *sp1 = 11;
//    test::shared_ptr<int> sp2(new int(2));
//    test::shared_ptr<int> sp3;
//    sp3 = sp1;
//    *sp3 = 11;
//    sp3 = sp3;
//    *sp3 = 11;
//    sp3 = sp1;
//    *sp3 = 11;
//    std::cout << *sp1 << "\n";
//    sp3 = sp2;
//    *sp3 = 22;
//    std::cout << *sp2 << "\n";
//}

//namespace test {
//    template<class T>
//    class unique_ptr {
//    public:
//        unique_ptr(T* ptr) :_ptr(ptr)
//        {}
//
//        ~unique_ptr() {
//            delete _ptr;
//            std::cout << "delete ptr" << "\n";
//        }
//        T& operator*() {
//            return *_ptr;
//        }
//        T* operator->() {
//            return _ptr;
//        }
//
//        //C++11封拷贝 
//        //unique_ptr(const unique_ptr<T>& up) = delete;
//        //unique_ptr<T>& operator = (const unique_ptr<T>&up) = delete;
//    private:
//        //C++98封拷贝
//        unique_ptr(const unique_ptr<T>& up); //C++98
//        unique_ptr<T>& operator=(const unique_ptr<T>&up);
//
//        T* _ptr;
//    };
//}

//int main() {
//    return 0;
//}

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