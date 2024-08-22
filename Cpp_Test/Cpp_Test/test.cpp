
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

    AVLTreeNode(const std::pair<K,V>& kv)
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
    AVLTree()
    :_root(nullptr)
    {}

public:
    bool Insert(const std::pair<K,V> kv) {
        //第一个结点做根
        if (_root == nullptr) {
            _root = new Node(kv);
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
                if (parent->_bf == -2 || cur->_bf == -1) {      //左左
                    RotateR(parent);
                }
                else if (parent->_bf == 2 || cur->_bf == 1) {   //右右
                    RotateL(parent);
                }
                else if (parent->_bf == -2 || cur->_bf == 1) {  //左右
                    RotateLR(parent);
                }
                else if(parent->_bf == 2 || cur->_bf == -1){    //右左
                    RotateRL(parent);
                }
                else {                                          //错误检查
                    assert(false);
                }
            }
            else {
                assert(false);
            }
        }

        return true;
    }

private:
    //右右
    void RotateL(Node* parent) {
        //. 记录爷爷(父亲的父亲)
        //. 我是父的右儿子(我是主角)
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
            if(parent == pparent->_left)
                pparent->_left = cur;
            else {
                pparent->_right = cur;
            }
        }
        else {                      //没有爷爷,父亲是根
            cur->_parent = nullptr;
            _root = cur;
        }
        //. 父子地位交换
        parent->_right = leftchild; 
        if (leftchild) {            //三叉链维护我的左孩子
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
            if(parent == pparent->_left)
                pparent->_left = cur;
            else {
                pparent->_right = cur;
            }
        }
        else {                      //没有爷爷,父亲是根
            cur->_parent = nullptr;
            _root = cur;
        }
        //. 父子地位交换
        parent->_left = rightChild; 
        if (rightChild) {            //三叉链维护我的左孩子
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
        //我是儿子,但是主角是孙子
        //记录下孙子
        //记录下孙子的平衡因子(特征)
        //对孙子进行左单旋,再右旋
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
            assert(false);
        }
    }

    //右左
    void RotateRL(Node* parent) {
        //我是儿子(父的右孩子),但是主角是孙子
        //记录下孙子(我的左孩子)
        //记录下孙子的平衡因子(特征)
        //对孙子进行左单旋,再右旋
        //更新平衡因子
        Node* cur = parent->_right;
        Node* grandson = cur->_left;
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
    Node* _root;
};


int main() {
    int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    AVLTree<int,int> t;
    for (int it : a) {
        t.Insert(std::make_pair(it,it));
    }
}

