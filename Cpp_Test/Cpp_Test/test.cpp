
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>

#include<iostream>
#include<chrono>
#include<functional>
#include<random>
#include<iomanip>
#include<string>
#include<cassert>

enum class Color { RED, BLACK };

template<class K, class V>
struct RBTreeNode {
    //三叉链
    RBTreeNode* _left;
    RBTreeNode* _right;
    RBTreeNode* _parent;

    std::pair<K,V> _kv;
    Color _col;
    
    RBTreeNode(const decltype(_kv)& kv)
    : _left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_kv(kv)
    ,_col(Color::RED) //默认为红,因为规则最宽松
    {}
};

template<class K,class V>
class RBTree {
public:
    bool Insert(const std::pair<K,V>& kv) {
        if (_root == nullptr) {
            _root = new Node(kv);
            _root->_col = Color::BLACK;
            return true;
        }

        Node* cur = _root;
        Node* parent = _root;
        while (cur) {
            if (kv.first > cur->_kv.first) {
                parent = cur;
                cur = cur -> _right;
            }
            else if (kv.first < cur->_kv.first) {
                parent = cur;
                cur = cur -> _left;
            }
            else {
                //存在相同的
                return false;
            }
        } //while比较过程 [end]

        //没找到,新增
        cur = new Node(kv); //cur地址改变,只能使用kv进行比较(始终使用kv就好了)
        //维护三叉链
        if (cur->_kv->first > parent->_kv.first) {
            parent->_right = cur;
        }
        else {
            parent->_left = cur;
        }
    
        //检查和调整红黑树


    }

private:
    using Node = RBTreeNode<K,V>;
    Node* _root;
};


void RandomArray_Generator(int* a, int n) {
    std::random_device rnd;//random num device //效率低，只用于生成种子
    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N

    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
    int size = n;
    for (int i = 0; i < size; i++) {
        a[i] = uni(rng); //随机数
        //a[i] = size - i; //逆序
        //a[i] = i;         //正序
        //a[i] = size/2;     //重复数
        //if (i % 10000 == 0) {
        //    a[i] = uni(rng);  //插入一些随机数
        //}
    }
}

void Cost(std::function<void(void)> func) {
    auto begin = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cost = end - begin;
    std::cout << cost.count() << "/s" << std::endl;
}

//void InsertTest(AVLTree<int,int>& t, int* a, int size) {
//    for (int i = 0; i < size; i++) {
//        t.Insert(std::make_pair(a[i], a[i]));
//        //if (t.IsBalance() == false) assert(false);
//    }
//}


int main() {
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
   //int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
    int size = 1000000;
    int* a = new int[size];
    RandomArray_Generator(a, size);
    //AVLTree<int, int> t;
    //InsertTest(t,a,size);
    //Cost([&]() {std::cout << "cost: "; InsertTest(t, a, size); });
    Cost([&]() {std::cout << "cost: "; std::sort(a, a + size); });
    //t.InOrder();
    //std::cout<<std::boolalpha;
    //std::cout << "是否平衡: " << t.IsBalance() << std::endl;
}

