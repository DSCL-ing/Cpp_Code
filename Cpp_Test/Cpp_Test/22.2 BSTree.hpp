#pragma once
#include<iostream>


template<class K>
struct BSTreeNode {
    BSTreeNode<K>* _left;
    BSTreeNode<K>* _right;
    K _key;

    BSTreeNode(K key)
        :_key(key), _left(nullptr), _right(nullptr)
    {}
};

template<class K>
class BSTree {
public:
    using Node = BSTreeNode<K>;
    BSTree() = default;
    BSTree(const BSTree& bst) {
        _root = Copy(bst._root);
    }
    BSTree<K>& operator=(BSTree bst) { //拷贝复用
        swap(_root, bst.root);
        return *this;
    }
    ~BSTree() {
        Destroy(_root);
    }

public:
    bool Insert(const K& key) {
        if (_root == nullptr) {
            _root = new Node(key);
            _root->_key = key;
            return true;
        }
        BSTreeNode<K>* cur = _root;
        BSTreeNode<K>* parent = _root;
        while (cur) {
            if (key < cur->_key) {
                parent = cur;
                cur = cur->_left;
            }
            else if (key > cur->_key) {
                parent = cur;
                cur = cur->_right;
            }
            else {
                return false;
            }
        }
        //走出循环,说明树中不存在该节点, 可以插入
        cur = new BSTreeNode<K>(key);
        if (key < parent->_key) {

            parent->_left = cur;
        }
        else {
            parent->_right = cur;
        }
        return true;
    }

    bool Find(const K& key) {
        if (_root == nullptr) return false;

        Node* cur = _root;
        while (cur) {
            if (key < cur->_key) {
                cur = cur->_left;
            }
            else if (key > cur->_key) {
                cur = cur->_right;
            }
            else {
                return true;
            }
        }
        // 从循环出来,说明没找着
        return false;
    }

    bool Erase(const K& key) {
        if (_root == nullptr) return false;

        Node* cur = _root;
        Node* parent = _root;

        while (cur) {
            if (key < cur->_key) {
                parent = cur;
                cur = cur->_left;
            }
            else if (key > cur->_key) {
                parent = cur;
                cur = cur->_right;
            }
            else {
                //没有左孩子
                if (cur->_left == nullptr) {
                    if (cur == _root) {
                        _root = cur->_right;
                    }
                    else if (parent->_left == cur) {
                        parent->_left = cur->_right;
                    }
                    else {
                        parent->_right = cur->_right;
                    }
                    delete cur;
                    return true;
                }
                //没有右孩子
                else if (cur->_right == nullptr) {
                    if (cur == _root) {
                        _root = cur->_left;
                    }
                    if (parent->_left == cur) {
                        parent->_left = cur->_left;
                    }
                    else {
                        parent->_right = cur->_left;
                    }
                    delete cur;
                    return true;
                }
                //有左右孩子
                else {
                    //找右孩子(子树)的最小结点/最左结点
                    Node* rightMin = cur->_right;  //明确不为空
                    Node* rightMinParent = cur;
                    while (rightMin->_left) {
                        rightMinParent = rightMin;
                        rightMin = rightMin->_left;
                    }
                    // 删除右子树最小结点有3种情况(与是不是根无关)
                    //1. 要删除的结点右子树最小结点恰好是自己的右孩子.
                    //2. 要删除的结点的右孩子的左子树的最左结点没有右孩子.
                    //3. 要删除的结点的右孩子的左子树的最左结点有右孩子.
                    //结论解析: 复用删除单结点代码,进行删除rightMin即可
                    K tmp = rightMin->_key;
                    Erase(rightMin->_key); //只能从根开始遍历,性能损失,但是二分查找很快,损失不大(理想情况,BST只学习用)
                    cur->_key = tmp;
                    return true;
                } //有左右孩子的情况 
            } //找到了_继续处理的过程
        }//循环找的过程
        //循环结束,说明没找到
        return false;
    }//Erase [end]

    void InOrder() {
        _InOrder(_root);
        std::cout << std::endl;
    }

    bool InsertR(const K& key) {
        _InsertR(_root, key);
    }

    bool EraseR(const K& key) {
        return _EraseR(_root, key);
    }

private:

    //此处返回值不能使用指针引用,虽然一定情况下可以使用(不推荐),至少目前不能引用空值.
    Node* Copy(const Node* root) {
        if (root == nullptr) {
            return nullptr;
        }
        Node* newRoot = new Node(root->_key);
        newRoot->_left = Copy(root->_left);
        newRoot->_right = Copy(root->_right);
        return newRoot;
    }

    //用不用引用无所谓,好习惯做到底
    //(析构子节点时,父节点两个成员会成为垂悬指针,但是接下来父亲也要析构了,指针变量也随之回收)
    void Destroy(Node*& root) {
        if (root == nullptr) {
            return;
        }
        Destroy(root->_left);
        Destroy(root->_right);

        std::cout << root->_key << " ";
        delete root; //释放加自动置空
    }

    //练习递归+引用 -- 代码更加简洁
    bool _EraseR(Node*& root, const K& key) {
        //走到空,说明没找到,返回false
        if (root == nullptr) {
            return false;
        }

        //大于走右边,小于走左边
        if (key > root->_key) {
            return _EraseR(root->_right, key);
        }
        else if (key < root->_key) {
            return _EraseR(root->_left, key);
        }
        //找到了
        else {
            if (root->_left == nullptr) {
                Node* del = root;
                root = root->_right;
                delete del;
                return true;
            }
            else if (root->_right == nullptr) {
                Node* del = root;
                root = root->_left;
                delete del;
                return true;
            }
            //有左右孩子
            else {
                Node* leftMax = root->_left;
                //找左子树最大结点
                while (leftMax->_right) {
                    leftMax = leftMax->_right;
                }
                std::swap(root->_key, leftMax->_key);
                return _EraseR(root->_left, key);    //直接从左孩子开始递归删除.
            }
        }

    }

    //练习递归+引用指针的玩法,仅练习
    bool _InsertR(Node*& root, const K& key) { //引用的妙用,跨栈帧直接访问实参
        if (root == nullptr) {
            root == new Node(key);
            return true;
        }
        if (key == root->_key) return false;
        return (key > root->_key) ? _InsertR(root->_right, key) : _InsertR(root->_left, key);
    }

    void _InOrder(Node* root) {
        if (root == nullptr)  return;
        _InOrder(root->_left);
        std::cout << root->_key << " ";
        _InOrder(root->_right);
    }

private:
    BSTreeNode<K>* _root = nullptr;
};


//void test() {
//    int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
//    BSTree<int> bst;
//    for (int i : a) {
//        bst.Insert(i);
//    }
//    bst.InOrder();
//
//    ////Find
//    //std::cout << std::boolalpha << bst.Find(8) << std::endl; //true
//    //std::cout << std::boolalpha << bst.Find(9) << std::endl; //false
//
//    BSTree<int> cp(bst);
//    cp.InOrder();
//
//    //测试两孩子的三种情况即可
//    bst.Erase(8);  //1. 要删除的结点的右子树的最小结点恰好是要删除结点的右孩子.
//    bst.Erase(10); //2. 要删除的结点的右子树的最小结点没有右孩子
//    bst.Insert(5); //构造有右孩子的最小结点
//    bst.Erase(3);  //3. 要删除的结点的右子树的最小结点有右孩子
//    bst.Erase(4);
//    bst.Erase(7);
//    bst.Erase(1);
//    bst.Erase(14);
//    bst.Erase(13);
//    bst.Erase(6);
//    bst.Erase(5);
//    bst.InOrder();
//
//    //禁止显式调用析构函数 --> 双重释放
//    //bst.~BSTree();
//    //cp.~BSTree();
//
//}
//
//int main() {
//    test();
//}
