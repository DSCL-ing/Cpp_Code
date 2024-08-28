#pragma once

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


template<class K, class V>
struct AVLTreeNode {

    //三叉链
    AVLTreeNode<K, V>* _left;
    AVLTreeNode* _right;
    AVLTreeNode* _parent;

    int _bf; //balance factor
    std::pair<K, V> _kv;

    AVLTreeNode(const std::pair<K, V>& kv)
        :_left(nullptr),
        _right(nullptr),
        _parent(nullptr),
        _bf(0),
        _kv(kv)
    {}
};

template<class K, class V>
class AVLTree {
public:
    using Node = AVLTreeNode<K, V>;
    AVLTree()
        :_root(nullptr)
        , _size(0)
    {}

public:
    bool Insert(const std::pair<K, V> kv) {
        //第一个结点做根
        if (_root == nullptr) {
            _root = new Node(kv);
            _size++;
            return true;
        }

        //搜索
        Node* parent = _root;
        Node* cur = _root;
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
        cur = new Node(kv);                         //new后,cur值发生改变,之后都不能使用地址进行比较
        if (cur->_kv.first < parent->_kv.first) {
            parent->_left = cur;
        }
        else {
            parent->_right = cur;
        }
        cur->_parent = parent; //三叉链链上父结点
        _size++;

        //调整平衡因子 : 最多到根,根的parent为nullptr
        while (parent) {

            //更新平衡因子
            if (cur->_kv.first < parent->_kv.first) {
                parent->_bf--;
            }
            else {
                parent->_bf++;
            }

            //看是否需要调整
            if (parent->_bf == 1 || parent->_bf == -1) {
                cur = parent;
                parent = parent->_parent;
            }
            else if (parent->_bf == 0) {
                break;
            }
            else if (parent->_bf == 2 || parent->_bf == -2) {
                if (parent->_bf == -2 && cur->_bf == -1) {      //左左
                    RotateR(parent);
                }
                else if (parent->_bf == 2 && cur->_bf == 1) {   //右右
                    RotateL(parent);
                }
                else if (parent->_bf == -2 && cur->_bf == 1) {  //左右
                    RotateLR(parent);
                }
                else if (parent->_bf == 2 && cur->_bf == -1) {    //右左
                    RotateRL(parent);
                }
                else {                                          //错误检查
                    assert(false);
                }
                break;
            }
            else {
                assert(false);
            }
        }

        return true;
    }

    void InOrder() {
        _InOrder(_root);
        std::cout << std::endl;
    }

    size_t Hight() {
        return _Hight(_root);
    }

    bool IsBalance() {
        return _IsBalance(_root);
    }

private:
    void _InOrder(Node* root) {
        if (root == nullptr) {
            return;
        }
        _InOrder(root->_left);
        std::cout << root->_kv.first << " ";
        _InOrder(root->_right);
    }

    size_t _Hight(Node* root) {
        if (root == 0) return 0;                //空
        size_t leftH = _Hight(root->_left);
        size_t rightH = _Hight(root->_right);
        return std::max(leftH, rightH) + 1;     //+1:自己高度为1
    }

    bool _IsBalance(Node* root) {
        if (root == nullptr) return true;
        int leftH = _Hight(root->_left);
        int rightH = _Hight(root->_right);
        int bf = rightH - leftH;
        return  bf == root->_bf         //平衡因子
            && (bf > -2 && bf < 2)      //高度差
            && _IsBalance(root->_left)
            && _IsBalance(root->_right);
    }

private:


    //右右
    void RotateL(Node* parent) {
        //. 记录爷爷(父亲的父亲)
        //. 我是父的右儿子(我是主角,新插入结点是我儿子)
        //. 记录下我的左子树(托管)
        //  旋转(爷、父、子关系重新调整）
        //      成为爷爷的右儿子 (如果没有爷爷,则跳过;且说明父是根,更新我成为根)
        //      把我的左子树托管给父成为他的右孩子
        //      旧父成为我的左儿子,旧父的父更新成我
        //. 更新平衡因子


        //. 记录爷爷(父亲的父亲)
        //. 我是父的右儿子
        //. 记录下我的左子树
        Node* pparent = parent->_parent;
        Node* cur = parent->_right;
        Node* leftchild = cur->_left;

        //旋转
        //. 成为爷爷的右儿子 (如果没有爷爷,则跳过;且说明父是根,更新我成为根)
        if (pparent) {              //有爷爷
            if (parent == pparent->_left)
                pparent->_left = cur;
            else {
                pparent->_right = cur;
            }
            cur->_parent = pparent; //三叉链维护
        }
        else {                      //没有爷爷,父亲是根
            cur->_parent = nullptr;
            _root = cur;
        }
        //. 父子地位交换
        parent->_right = leftchild;
        if (leftchild) {            //三叉链维护
            leftchild->_parent = parent;
        }
        cur->_left = parent;
        parent->_parent = cur;
        //旋转 【end】

        //更新平衡因子
        cur->_bf = 0;
        parent->_bf = 0;
    }


    //左左
    void RotateR(Node* parent) {
        //. 记录爷爷
        //. 我是父的左儿子
        //. 记录下我的右子树
        Node* pparent = parent->_parent;
        Node* cur = parent->_left;
        Node* rightChild = cur->_right;

        //旋转
        //. 成为爷爷的左儿子 (如果没有爷爷,则跳过;且说明父是根,更新我成为根)
        if (pparent) {              //有爷爷
            if (parent == pparent->_left)
                pparent->_left = cur;
            else {
                pparent->_right = cur;
            }
            cur->_parent = pparent; //三叉链维护
        }
        else {                      //没有爷爷,父亲是根
            cur->_parent = nullptr;
            _root = cur;
        }
        //. 父子地位交换
        parent->_left = rightChild;
        if (rightChild) {            //三叉链维护
            rightChild->_parent = parent;
        }
        cur->_right = parent;
        parent->_parent = cur;
        //旋转 【end】

        //更新平衡因子
        cur->_bf = 0;
        parent->_bf = 0;

    }
    //左右
    void RotateLR(Node* parent) {
        //我是cur,但是主角是我的右儿子(新插入结点)
        //记录下我的右儿子,简称孙子
        //记录下孙子的平衡因子(特征)
        //对孙子的爸爸(我)进行左单旋,再右旋(新爸:我的父)
        //更新平衡因子
        Node* cur = parent->_left;
        Node* grandson = cur->_right;
        int bf = grandson->_bf;

        RotateL(cur);
        RotateR(grandson->_parent);

        //三种情况
        if (bf == 0) {
            parent->_bf = 0;
            cur->_bf = 0;
            grandson->_bf = 0;
        }
        else if (bf == 1) {
            parent->_bf = 0;
            cur->_bf = -1;
            grandson->_bf = 0;
        }
        else if (bf == -1) {
            parent->_bf = 1;
            cur->_bf = 0;
            grandson->_bf = 0;
        }
        else {
            assert(false); //错误检查
        }
    }

    //右左
    void RotateRL(Node* parent) {
        //我是cur,但是主角是我的左儿子(新插入结点)
        //记录下我的左儿子,简称孙子
        //记录下孙子的平衡因子(特征)
        //对孙子进行右单旋,再左单旋
        //更新平衡因子
        Node* cur = parent->_right;
        Node* grandson = cur->_left;
        int bf = grandson->_bf;

        RotateR(cur); //将孙子的爹,就是我,进行右单旋
        RotateL(grandson->_parent); //将儿子的新爹进行左单旋

        //三种情况
        if (bf == 0) {
            parent->_bf = 0;
            cur->_bf = 0;
            grandson->_bf = 0;
        }
        else if (bf == 1) {
            parent->_bf = -1;
            cur->_bf = 0;
            grandson->_bf = 0;
        }
        else if (bf == -1) {
            parent->_bf = 0;
            cur->_bf = 1;
            grandson->_bf = 0;
        }
        else {
            assert(false);
        }
    }

private:
    Node* _root;
    size_t _size;
};

//void RandomArray_Generator(int* a, int n) {
//    std::random_device rnd;//random num device //效率低，只用于生成种子
//    std::mt19937 rng(rnd()); //random num generator -- 生成随机数
//    std::uniform_int_distribution<int> uni(0, 1000000000);//整型区间筛选
//    //[0-N]有6成为不重复,4成重复 --若需要9成不重复需要扩大筛选范围为10倍的N,即插入N需筛选10N
//
//    //int a[] = { 3,1,8,4,2,7,5,9,6,0 }; //自定义数组
//    int size = n;
//    for (int i = 0; i < size; i++) {
//        a[i] = uni(rng); //随机数
//        //a[i] = size - i; //逆序
//        //a[i] = i;         //正序
//        //a[i] = size/2;     //重复数
//        //if (i % 10000 == 0) {
//        //    a[i] = uni(rng);  //插入一些随机数
//        //}
//    }
//}
//
//void Cost(std::function<void(void)> func) {
//    auto begin = std::chrono::high_resolution_clock::now();
//    func();
//    auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> cost = end - begin;
//    std::cout << cost.count() << "/s" << std::endl;
//}
//
//void InsertTest(AVLTree<int, int>& t, int* a, int size) {
//    for (int i = 0; i < size; i++) {
//        t.Insert(std::make_pair(a[i], a[i]));
//        //if (t.IsBalance() == false) assert(false);
//    }
//}
//
//
//int main() {
//    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
//   //int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
//    int size = 1000000;
//    int* a = new int[size];
//    RandomArray_Generator(a, size);
//    AVLTree<int, int> t;
//    InsertTest(t, a, size);
//    //Cost([&]() {std::cout << "cost: "; InsertTest(t, a, size); });
//    Cost([&]() {std::cout << "cost: "; std::sort(a, a + size); });
//    //t.InOrder();
//    //std::cout<<std::boolalpha;
//    //std::cout << "是否平衡: " << t.IsBalance() << std::endl;
//}


