
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

#if 1
//class A
//{
//public:
//    virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//    virtual void test() {};
//};
//
//class B : public A
//{
//public:
//    void func(int val = 0) override{ std::cout << "B->" << val << std::endl; }
//    virtual void test() override{ func(); }
//};
//
//int main(int argc, char* argv[])
//{
//    B* p = new B;
//    p->test();
//    return 0;
//}

class A
{
public:
    virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
    virtual void test() { func(); }
};

class B : public A
{
public:
    void func(int val = 0) {  std::cout<<typeid(this).name()<<std::endl;  std::cout << "B->" << val << std::endl; }
};

int main(int argc, char* argv[])
{
    B* p = new B;
    p->test();
    return 0;
}

#elif 0
#include <cstring>
#include <iostream>
#include <thread>

class my_string {
public:
    using Self = my_string;

    // 左值 带参构造函数
    my_string(const char* str = "")
        : _size(strlen(str)),  // 依据_size的大小是0还是非0,决定如何分空间
        _capacity(0),
        _str(nullptr) {
        if (_size == 0) {
            _capacity =
                3;  // msvc缺省值是15,不过我们这个用来学习的,小一点可以测试结果
        }
        else {
            _capacity = _size;
        }

        _str = new char[_capacity];
        strcpy(_str, str);
    }

    ~my_string() {
        _size = 0;
        _capacity = 0;
        delete[] _str;
    }

    void Swap(my_string& str) {
        std::swap(str._size, _size);
        std::swap(str._capacity, _capacity);
        std::swap(str._str, _str);
    }

    my_string(const my_string& str) {
        my_string tmp(str._str);
        Swap(tmp);
    }

    Self& operator=(my_string str) { Swap(str); }

    char* _str;
    size_t _capacity;  // 总容量
    size_t _size;      // 有效字符串长度
};

int main() {
    return 0;
}
#endif
