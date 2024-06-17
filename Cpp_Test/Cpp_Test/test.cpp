#include<iostream>
#include<mutex>
#include<thread>
#include<memory>

namespace test {
    template<class T>
    class shared_ptr {
    public:
        shared_ptr() : _ptr(nullptr), _pRefCount(new int(0)),_pmtx(new std::mutex)
        {}

        shared_ptr(T* ptr) :_ptr(ptr), _pRefCount(new int(1)),_pmtx(new std::mutex)
        {}

        shared_ptr(const shared_ptr<T>& sp) :_ptr(sp._ptr), _pRefCount(sp._pRefCount) ,_pmtx(sp._pmtx){
            AddRef();
        }


        ~shared_ptr() {
            Release();
        }

        shared_ptr<T>& operator=(const shared_ptr<T>& sp) {
            /*
            operator较为复杂,具有任意性(可以多次赋值,拷贝只能一次)
            1.如果使用赋值进行初始化,则和拷贝赋值一样.
            2.如果是二次赋值,需要考虑有:
            - 新管理资源走拷贝构造一套.
            - 原先管理资源的引用计数减少.为0时需要析构(走一次析构)
            - 处理"自己"给"自己"赋值
                - 智能指针对象相同,指向的资源相同
                - 智能指针对象不同,指向的资源相同
                传统的方法(*this!=对象),只能处理第一种;而(*this._ptr != sp._ptr)能够兼容两种方法;

            虽然处理逻辑和析构函数很像,但是C++中成员函数不能自己调用析构函数,因为肚子里的蛋不能杀的了鸡.
            如果需要提高复用性,可以将逻辑独立成一个函数,然后析构和赋值重载都分别进行调用
            */
            if (_ptr != sp._ptr)
            {
                if (*_pRefCount == 0) //天生就为0
                {}
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
                delete _ptr;
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

        T* get() {
            return _ptr;
        }

        int use_count() {
            return *_pRefCount;
        }


    private:
        T* _ptr;
        int* _pRefCount;
        std::mutex* _pmtx;
        /*
        1.线程安全问题,智能指针只负责自身线程安全,并不负责资源的线程安全,资源的线程安全由资源自己负责.
        而引用计数是属于智能指针维护的,因此,智能指针的线程安全问题为引用计数的线程安全问题.即保护引用计数
        2.锁的定义方式和_pRefCount一样.一份资源(此处资源为_pRefCount)对应一个.
        */
    };
}

struct ListNode
{
    int _data;
    std::shared_ptr<ListNode> _prev;
    std::shared_ptr<ListNode> _next;

    ~ListNode() { std::cout << "~ListNode()" << std::endl; }
};

int main() {
    std::shared_ptr<ListNode> sp1 (new ListNode);
    std::shared_ptr<ListNode> sp2 (new ListNode);
    sp1->_next = sp2;
    sp2->_prev = sp1;
    return 0;
}

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