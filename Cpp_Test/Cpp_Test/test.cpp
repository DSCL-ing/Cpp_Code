
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

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
    using Node = RBTreeNode<K, V>;
    RBTree()
        :_root(nullptr)
    {}
public:
    bool Insert(const std::pair<K, V>& kv) {
        if (_root == nullptr) {
            _root = new Node(kv);
            _root->_col = Color::BLACK;
            return true;
        }
        if (kv.first == 1) {
            int x = 0;
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

void InsertTest(RBTree<int, int>& t, int* a, int size) {
    for (int i = 0; i < size; i++) {
        t.Insert(std::make_pair(a[i], a[i]));
        //if (t.IsBalance() == false) assert(false);
    }
}


int main() {
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16,14 };
    int size = 10;
    //int* a = new int[size];
    //RandomArray_Generator(a, size);
    RBTree<int, int> t;
    InsertTest(t, a, size);
    //Cost([&]() {std::cout << "cost: "; InsertTest(t, a, size); });
    //Cost([&]() {std::cout << "cost: "; std::sort(a, a + size); });
    //t.InOrder();
    //std::cout<<std::boolalpha;
    //std::cout << "是否平衡: " << t.IsBalance() << std::endl;
}

