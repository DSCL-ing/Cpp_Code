
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

#if 0
//#include"25.2 RBTree.hpp"
//
//template<class K>
//class my_set {
//    bool Insert(const K& key) {
//        return t.Insert(std::make_pair(key,key));
//    }
//
//    //Node* Find(const K& key) {
//    //    return  t.Find(key);
//    //}
//    
//    RBTree<K,K> t;
//};
//
//template<class K, class V>
//class my_map {
//    bool Insert(const std::pair<K, V>& kv) {
//        return t.Insert(kv);
//    }
//    RBTree<K,V> t;
//};


int main() {
    //my_set<int> s;
    //my_map<int,int> m;
    std::string str;
    for (int i = 0; i < 100; i++) {
        str+=1;
    }
}

#elif 1
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
