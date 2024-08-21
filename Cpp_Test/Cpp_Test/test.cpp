
#include<iostream>
#include<mutex>
#include<atomic>
#include<queue>
#include<chrono>
#include<thread>
#include<functional>
#include<random>
#include<iomanip>
#include<string>

#include<cassert>

template<class K,class V>
struct AVLTreeNode {
    
    //三叉链
    AVLTreeNode<K,V>* _left;
    AVLTreeNode* _right;
    AVLTreeNode* _parent;

    int _bf; //balance factor
    std::pair<K,V> _kv;

    AVLTreeNode(const std::pair& kv)
        :_left(nullptr),
        _right(nullptr),
        _parent(nullptr),
        _bf(0),
        _kv(kv)
    {}
};

template<class K,class V>
class AVLTree {
public:
    using Node = AVLTreeNode<K, V>;

public:
    bool Insert(const std::pair<K,V> kv) {
        //第一个结点做根
        if (_root == nullptr) {
            _root = new Node(kv);
            return true;
        }

        //搜索
        Node* parent = root;
        Node* cur = root;
        while (cur) {
            //大于往右走
            if (kv.first > cur->_kv.first) {
                parent = cur;
                cur = cur->_right;
            }
            //小于往左走
            else if (kv.first < cur->_kv.first) {
                parent = cur;
                cur = cur->_left;
            }
            //找到了,存在相同的key
            else {
                return false;
            }
        } //循环搜索...

        //不存在,可以插入
        cur = new Node(kv); //新插入结点平衡因子都是0
        if (cur == parent->_left) {
            parent->_left = cur;
        }
        else {
            parent->_right = cur;
        }
        cur->_parent = parent; //三叉链链上父结点

        //调整平衡因子 : 最多到根,根的parent为nullptr
        while (parent) {

            //更新平衡因子
            if (cur == parent->_left) {
                parent->_bf--;
            }
            else {
                parent->_bf++;
            }

            //看是否需要调整
            if (parent->_bf == 1 || parent->_bf == -1) {
                parent = parent->_parent;
            }
            else if(parent->_bf == 0){
                break; 
            }
            else if(parent->_bf == 2 || parent->_bf == -2){
                //旋转
            }
            else {
                assert(false);
            }
        }

        return true;
    }

private:
    Node* _root;
};

