#pragma once
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
struct _RBTree_iterator {
    using Node = RBTreeNode<K,V>;
    using Self = _RBTree_iterator<K,V>;
    Node* _node;
    _RBTree_iterator(Node* node)
        :_node(node)
    {}

    _RBTree_iterator(const Self<K, V>& it)
        :_node(const_cast<Node*>(it._node))
    { }

    //要的就是浅拷贝,默认就好
    //iterator<K, V>& operator=(iterator<K,V> it) {
    //    std::swap(it._node,_node);
    //    return *this;
    //}

    bool operator!=(const Self& s) {
        return _node != s._node;
    }

    std::pair<K, V>& operator*() {
        return (*_node)._kv;
    }

    //++
    /*
        推导1:一个结点的左子树一定比自己小,右子树一定比自己大
            我如果是父的左结点,则我一定比父小.反之我一定比父大.
        一个结点的左子树的最小结点是最小的值,他的父是仅大于他的结点,他的父的右子树的最左结点是仅更大一点的结点.

        升序: 左子树<根<右子树

        如何找到自己结点的下一个正序数 :
        1. 右子树一定比自己大,找右子树中最小那(最左结点)个就是比自己大的
        2. 没有右子树,则说明自己是最大的了,自己这棵子树已经遍历完了;
           1. 如果自己是父的右孩子,则说明父结点这棵树走到头了(我是最大),需要再看爷爷(迭代往上)
           2. 如果自己是父的左孩子,则说明父结点是下一个正序数(推导1).
    */
    //前置++
    Self& operator++() {
        //此版本实现迭代器不需要判空,为空说明遍历结束,要么是用户错误使用
        Node* cur = _node;
        //1. 有右子树
        if (cur->_right) {
            //找右子树的最小结点
            Node* rightMin = cur->_right;
            while (rightMin->_left) {
                rightMin = rightMin->_left;
            }
            _node = rightMin;
        }
        //2. 没有右子树
        else {
            ////1.没有父亲,说明是根
            //Node* parent = cur->_parent;
            //if (parent == nullptr) {
            //    _node == nullptr;
            //}
            ////2.且我是父的左子树,说明父亲是下一个正序值
            //else if (parent->_left == cur) {
            //    _node = parent;
            //}
            ////3.或我是父亲的右子树,说明走完了当前最小分支祖先这棵树.迭代往上
            //else if (parent->_right == cur) {
            //    while (parent && cur != parent->_left) {
            //        cur = parent;
            //        parent = parent->_parent;
            //    }
            //    _node = parent;
            //}
            //else {
            //    asssert(false);
            //}

            //上面3种情况可以合并成一种情况:找最近的不是右孩子的祖父
            Node* parent = cur->_parent;
            while (parent && cur != parent->_left) {
                cur = parent;
                parent = parent->_parent;
            }
            _node = parent;
        }
        return *this;
    }

    //后置++
    Self operator++(int) {
        Self tmp(_node);
        operator++();
        return tmp;
    }


    Self& operator--() {
        //将++反过来就是--
        Node* cur = _node;
        //左子树存在,就找最大
        if (cur->_left) {
            Node* leftMax = cur->_left;
            while (leftMax->_right) {
                leftMax = leftMax->_right;
            }
            _node = leftMax;
        }
        //2. 没有左子树
        else {
            Node* parent = cur->_parent;
            while (parent && cur != parent->_right) {
                cur = parent;
                parent = parent->_parent;
            }
            _node = parent;
        }
        return *this;
    }

    Self operator--(int) {
        Self tmp(_node);
        operator--();
        return tmp;
    }

};

template<class K, class V>
class RBTree {

public: //construct
    using Node = RBTreeNode<K, V>;
    using iterator = _RBTree_iterator<K, V>;
    RBTree()
        :_root(nullptr)
    {}

public: //iterator
    iterator begin() {
        Node* cur = _root;
        while (cur && cur->_left) {     //需要的是最左节点,不能走到空
            cur = cur->_left;
        }
        return cur;
    }
    iterator end() {
        return nullptr;
    }

public: //member function

    iterator Find(const K& key) {
        if (_root == nullptr) {
            return false;
        }
        Node* cur = _root;
        while (cur) {
            if (key > cur->_kv.first) {
                cur = cur->_right;
            }
            else if (key < cur->_kv.first) {
                cur = cur->_left;
            }
            else {
                return cur;
            }
        }
        return nullptr;
    }

    bool Insert(const std::pair<K, V>& kv) {
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
                cur = cur->_right;
            }
            else if (kv.first < cur->_kv.first) {
                parent = cur;
                cur = cur->_left;
            }
            else {
                //存在相同的
                return false;
            }
        } //while比较过程 [end]

        //没找到,新增
        cur = new Node(kv); //cur地址改变,只能使用kv进行比较(始终使用kv就好了)
        //维护三叉链
        cur->_parent = parent;
        if (cur->_kv.first > parent->_kv.first) {
            parent->_right = cur;
        }
        else {
            parent->_left = cur;
        }


        //检查和调整红黑树
        //FixInsert();
        /**
         * 右单旋情形									    旋转后
         *            g(黑)							 |	           p(黑)
         *      p(红)       u(黑)				     |	      c(红)     g(红)
         *    c(红)	                     		     |                      u(黑)
         */

         /**
          * 左右双旋情形                                      旋转后
          *            g(黑)						     |                 c(黑)
          *    p(红)             u(黑)				 |          p(红)		 g(红)
          *  x      c(红)        					 | 		x 			       u(黑)
          */
        while (parent && parent->_col == Color::RED) {
            Node* grandpa = parent->_parent;
            Node* uncle = nullptr;
            if (parent == grandpa->_left && grandpa->_right) {
                uncle = grandpa->_right;
            }
            else if (parent == grandpa->_right && grandpa->_left) {
                uncle = grandpa->_left;
            }
            else {
                uncle = nullptr;
            }

            //叔叔存在且为红
            if (uncle && uncle->_col == Color::RED) {
                parent->_col = Color::BLACK;
                grandpa->_col = Color::RED;
                uncle->_col = Color::BLACK;

                cur = grandpa;
                parent = grandpa->_parent;
            }
            //叔叔为黑色或无(已经确定左右父爷叔)
            else {
                //左左:对爷爷右单旋
                if (cur == parent->_left && parent == grandpa->_left) {
                    RotateR(grandpa);
                    parent->_col = Color::BLACK;
                    grandpa->_col = Color::RED;
                }
                //左右:对父左单旋,对爷爷右单旋
                else if (cur == parent->_right && parent == grandpa->_left) {
                    RotateL(parent);                     //转成左右,cur变成父,父变成子
                    RotateR(grandpa);                    //cur变成子树的根,右孩子是爷爷
                    cur->_col = Color::BLACK;            //新爷爷变黑
                    grandpa->_col = Color::RED;          //旧爷爷变红,和旧父同色
                }
                //右右
                else if (cur == parent->_right && parent == grandpa->_right) {
                    RotateL(grandpa);
                    parent->_col = Color::BLACK;
                    grandpa->_col = Color::RED;
                }
                //右左
                else if (cur == parent->_left && parent == grandpa->_right) {
                    RotateR(parent);                    //转成右右,此时cur变成父了
                    RotateL(grandpa);                   //cur变成子树的根,左孩子是爷爷
                    cur->_col = Color::BLACK;            //新爷爷变黑
                    grandpa->_col = Color::RED;          //旧爷爷变红,和旧父同色
                }
                //检查/排错
                else {
                    assert(false);
                }
                //不需要更新变量,因为子树的根不是红了,不需要再更新
                break;
            }
        }
        //只有旋转会影响_root,旋转过程会自动更新_root,不用担心_root没有正确指向
        //_root不影响所有路径的结点(同增同减),统一更新即可.
        _root->_col = Color::BLACK;
        return true;

    }

    void RotateL(Node* parent) {
        Node* pparent = parent->_parent;
        Node* cur = parent->_right;
        Node* leftChild = cur->_left;

        if (pparent) {
            if (cur->_kv < pparent->_kv) {
                pparent->_left = cur;
                cur->_parent = pparent;
            }
            else {
                pparent->_right = cur;
                cur->_parent = pparent;
            }
        }
        else {
            cur->_parent = nullptr;
            _root = cur;
        }

        parent->_right = leftChild;
        if (leftChild) {
            leftChild->_parent = parent;
        }
        cur->_left = parent;
        parent->_parent = cur;
    }

    void RotateR(Node* parent) {
        Node* pparent = parent->_parent;
        Node* cur = parent->_left;
        Node* rightChild = cur->_right;

        //爷我
        if (pparent) {
            if (cur->_kv < pparent->_kv) {
                pparent->_left = cur;
                cur->_parent = pparent;
            }
            else {
                pparent->_right = cur;
                cur->_parent = pparent;
            }
        }
        else {
            cur->_parent = nullptr;
            _root = cur;
        }

        //交换父子关系
        cur->_right = parent;
        parent->_parent = cur;

        //托管
        parent->_left = rightChild;
        if (rightChild) {
            rightChild->_parent = parent;
        }
    }



    void InOrder() {
        _InOrder(_root);
        std::cout << std::endl;
    }

    bool IsBalance() {
        //平衡条件
        //1.根是黑
        //2.红色结点不能连续
        //3.所有路径黑色结点数量相同
        //  实现方式:记录任意一条路径的黑结点数量,以该数量为基准,比较其他路径是否相等,不相等就是不平衡.(走到空就算是一条路径)

        //条件1
        if (_root == nullptr)           return true;
        if (_root->_col == Color::RED)  return false;

        //2和3需要遍历,因此另开一个函数
        //2只需要结点即可,3还需要基准值和黑结点数量
        int benchMark = 0;
        Node* cur = _root;
        while (cur) {
            if (cur->_col == Color::BLACK) {
                benchMark++;
            }
            cur = cur->_left;
        }
        return _check(_root, 0, benchMark);
    }

    bool _check(Node* root, int blackNum, const int benchMark) {
        //条件3
        if (root == nullptr) {
            //走到根,路径结束,比较黑结点数量,只要有一个不同就是不同
            //return blackNum == benchMark ? true : false;
            if (blackNum != benchMark) {
                std::cout << "基准值: " << benchMark << " 当前路径黑色结点数: " << blackNum << std::endl;
                return false;
            }
            return true;
        }
        if (root->_col == Color::BLACK) {
            blackNum++;
        }

        //条件2:相比于比较子(两步操作),比较父更简单(1步操作)
        // 父结点一定存在:只有根不存在父结点,但根第一个就处理掉了
        if (root->_col == Color::RED && root->_parent->_col == Color::RED) {
            std::cout << "子结点: " << root->_kv.first << " 与父结点同为红色" << std::endl;
            return false;
        }

        //通过条件:左右子树都为真
        return _check(root->_left, blackNum, benchMark) && _check(root->_right, blackNum, benchMark);
    }

    int Hight() {
        return _Hight(_root);
    }

    int _Hight(Node* root) {
        if (root == nullptr) {
            return 0;
        }
        int L = _Hight(root->_left);
        int R = _Hight(root->_right);

        return std::max(L, R) + 1;
    }

    ~RBTree() {
        Destroy(_root);
    }

    void Destroy(Node*& root) {
        if (root == nullptr) {
            return;
        }
        Destroy(root->_left);
        Destroy(root->_right);
        delete root;
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

private:
    Node* _root;
};




