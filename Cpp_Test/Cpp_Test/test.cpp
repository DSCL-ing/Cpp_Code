﻿
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

#if 1

template<class T>
class A{
public:
using reference = T&;
using const_reference = const T&;
using pointer = T*;
using const_pointer = const T*;

using const_A = A<const T>;

    A()
    
    
    
};

int main() {
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };




    //RBTree<int,int> t;
    //for(int it : a){
    //    t.Insert(std::make_pair(it,it));
    //}
    ////t.InOrder();

    //auto it = t.begin();
    //while (it != t.end()) {
    //    std::cout<<(*it).first<<std::endl;
    //    ++it;
    //    //测试++/--;
    //    if (it != t.end()) {
    //        it--;
    //        it++;
    //        --it;
    //        ++it;
    //    }
    //}

    //for (auto it : t) {
    //    std::cout<<it.first<<std::endl;
    //}



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
