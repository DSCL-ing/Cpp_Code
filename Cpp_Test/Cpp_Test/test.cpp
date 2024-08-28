
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

#include"25.2 RBTree.hpp"

template<class K>
class my_set {
    bool Insert(const K& key) {
        return t.Insert(std::make_pair(key,key));
    }

    //Node* Find(const K& key) {
    //    return  t.Find(key);
    //}
    
    RBTree<K,K> t;
};

template<class K, class V>
class my_map {
    bool Insert(const std::pair<K, V>& kv) {
        return t.Insert(kv);
    }
    RBTree<K,V> t;
};

int main() {
    my_set<int> s;
    my_map<int,int> m;
}
