
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

#if 1
#include"25.2 RBTree.hpp"

template<class K>
class my_set {
public:
    using Node = RBTreeNode<K,K>;
    struct iterator {
        using rb_iterator = _RBTree_iterator<K,K> ;
        iterator() 
        :it
        {}
        rb_iterator it;

        K& operator*() {
            return _node->_kv.first;
        }

        iterator operator++() {
            
        }
    };
    

    bool Insert(const K& key) {
        return _t.Insert(std::make_pair(key,key));
    }

    iterator Find(const K& key) {
        return _t.Find(key);
    }

    iterator begin() {
        return _t.begin();
    }

    iterator end() {
        return _t.end();
    }
    
    RBTree<K,K> _t;
};

template<class K, class V>
class my_map {
    bool Insert(const std::pair<K, V>& kv) {
        return t.Insert(kv);
    }
    RBTree<K,V> t;
};


int main() {
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
    my_set<int> s;
    my_map<int,int> m;
    for(int it : a){
        s.Insert(it);
    }

    for (auto it : s) {
        std::cout<<it<<std::endl;
    }


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
