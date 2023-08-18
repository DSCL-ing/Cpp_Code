


#pragma once
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	int _bf; // balance factor

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first > kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		// 更新平衡因子
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;
			}

			if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 继续更新
				parent = parent->_parent;
				cur = cur->_parent;
			}
			else if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// 需要旋转处理 -- 1、让这颗子树平衡 2、降低这颗子树的高度
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				else
				{
					assert(false);
				}

				break;
			}
			else
			{
				assert(false);
			}
		}

		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}

	int Height()
	{
		return _Height(_root);
	}

private:
	int _Height(Node* root)
	{
		if (root == NULL)
			return 0;

		int leftH = _Height(root->_left);
		int rightH = _Height(root->_right);

		return leftH > rightH ? leftH + 1 : rightH + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}

		int leftH = _Height(root->_left);
		int rightH = _Height(root->_right);

		if (rightH - leftH != root->_bf)
		{
			cout << root->_kv.first << "节点平衡因子异常" << endl;
			return false;
		}

		return abs(leftH - rightH) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppnode = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (ppnode == nullptr)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = subR;
			}
			else
			{
				ppnode->_right = subR;
			}

			subR->_parent = ppnode;
		}

		parent->_bf = subR->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* ppnode = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = subL;
			}
			else
			{
				ppnode->_right = subL;
			}
			subL->_parent = ppnode;
		}

		subL->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 1)
		{
			parent->_bf = 0;
			subLR->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subLR->_bf = 0;
			subL->_bf = 0;
		}
		else if (bf == 0)
		{
			parent->_bf = 0;
			subLR->_bf = 0;
			subL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 0)
		{
			subR->_bf = 0;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << " ";
		_InOrder(root->_right);
	}
private:
	Node* _root = nullptr;
};

void Test_AVLTree1()
{
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t1;
	for (auto e : a)
	{
		/*	if (e == 14)
			{
			int x = 0;
			}*/

		t1.Insert(make_pair(e, e));
		cout << e << "插入：" << t1.IsBalance() << endl;
	}

	t1.InOrder();
	cout << t1.IsBalance() << endl;
}

// 10:35继续
void Test_AVLTree2()
{
	srand((size_t)time(0));
	const size_t N = 100000;
	AVLTree<int, int> t;
	for (size_t i = 0; i < N; ++i)
	{
		size_t x = rand() + i;
		t.Insert(make_pair(x, x));
		//cout << t.IsBalance() << endl;
	}

	//t.Inorder();

	cout << t.IsBalance() << endl;
	cout << t.Height() << endl;
}

//int main()
//{
//	Test_AVLTree2();
//	return 0;
//}


/*
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

using T = int;

class TreeNode {
public:
    TreeNode() : children_(2, nullptr) {}
    TreeNode(const T& x) : data_(x), children_(2, nullptr) {}

    int Show(vector<vector<string>>& pic, int dep) const;
    void Insert(const shared_ptr<TreeNode>& data_ptr);
    bool Erase(const T& x, shared_ptr<TreeNode>& pre_ptr);

private:
    inline shared_ptr<TreeNode>& left() { return children_.at(0); }
    inline shared_ptr<TreeNode>& right() { return children_.at(1); }
    inline const shared_ptr<TreeNode>& left() const { return children_.at(0); }
    inline const shared_ptr<TreeNode>& right() const { return children_.at(1); }

public:
    T data_;
    vector<shared_ptr<TreeNode>> children_;
};

class Tree {
public:
    void Show() const {
        vector<vector<string>> ret;
        root_->Show(ret, 0);
        for (auto p = ret.rbegin(); p != ret.rend(); ++p) {
            for (auto& q : *p) cout << q;
            puts("");
        }
    }
    void Insert(const T& x) {
        if (nullptr == root_)
            root_ = make_shared<TreeNode>(x);
        else
            root_->Insert(make_shared<TreeNode>(x));
    }
    bool Erase(const T& x) { return root_->Erase(x, root_); }

private:
    shared_ptr<TreeNode> root_;
};

//int main() {
//    Tree root;
//    root.Insert(52);
//    root.Insert(2);
//    root.Insert(102);
//    root.Insert(1);
//    root.Insert(100);
//    root.Insert(98);
//    root.Insert(90);
//    root.Insert(101);
//    root.Insert(1024);
//    root.Show();
//}

void TreeNode::Insert(const shared_ptr<TreeNode>& data_ptr) {
    auto& next_ptr = data_ptr->data_ < data_ ? left() : right();
    if (nullptr == next_ptr)
        next_ptr = data_ptr;
    else
        next_ptr->Insert(data_ptr);
}

int TreeNode::Show(vector<vector<string>>& pic, int dep) const {
    int start = pic.size(), sl, sr, ret;
    int this_string_length = to_string(data_).size();
    string line;
    for (int i = 0; i < this_string_length; ++i) line += "─";
    // gain
    if (nullptr != left()) {
        sl = left()->Show(pic, dep + 1);
    }
    else {
        pic.push_back(vector<string>{"", "null"});
        sl = pic.size() - 1;
    }
    pic.push_back(vector<string>{"", to_string(data_)});
    ret = pic.size() - 1;
    if (nullptr != right()) {
        sr = right()->Show(pic, dep + 1);
    }
    else {
        pic.push_back(vector<string>{"", "null"});
        sr = pic.size() - 1;
    }
    // al
    for (int i = start; i <= sl - 1; ++i) pic[i][0] = string(this_string_length + 1, ' ') + pic[i][0];
    pic[sl][0] = "└" + line + pic[sl][0];
    for (int i = sl + 1; i <= sr - 1; ++i) pic[i][0] = "│" + string(this_string_length, ' ') + pic[i][0];
    pic[ret][0] = "";
    pic[sr][0] = "┌" + line + pic[sr][0];
    for (int i = sr + 1; i < pic.size(); ++i) pic[i][0] = string(this_string_length + 1, ' ') + pic[i][0];

    return ret;
}

bool TreeNode::Erase(const T& x, shared_ptr<TreeNode>& pre_ptr) {
    if (x != data_) {
        auto& next_ptr = x < data_ ? left() : right();
        if (nullptr == next_ptr) return false;
        return next_ptr->Erase(x, next_ptr);
    }
    // x == data_
    if (nullptr == left() && nullptr == right()) {
        pre_ptr = nullptr;
        return true;
    }
    if (nullptr == left() || nullptr == right()) {
        pre_ptr = children_.at(nullptr != right());
        return true;
    }
    // both not null
    if (nullptr == right()->left()) {
        right()->left() = this->left();
        pre_ptr = right();
        return true;
    }
    if (nullptr == left()->right()) {
        left()->right() = this->right();
        pre_ptr = left();
        return true;
    }
    // find the min node in right
    auto& min_node_pre = right();
    while (nullptr != min_node_pre->left()->left()) min_node_pre = min_node_pre->left();
    min_node_pre->left()->left() = this->left();
    pre_ptr = this->right();
    return true;
}

*/















//#pragma once
//#include<iostream>
//#include<vector>
//#include<queue>
//
//using namespace std;
//
//struct TreeNode {
//    int val;
//    TreeNode* left;
//    TreeNode* right;
//    TreeNode() : val(0), left(nullptr), right(nullptr) {}
//    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};
//
//class Solution {
//public:
//    TreeNode* treeToDoublyList(TreeNode* root) {
//        return Convert(root);
//    }
//    void InOrderConvert(TreeNode* cur, TreeNode*& prev) {
//        if (!cur)
//            return;
//        InOrderConvert(cur->left, prev);
//        cur->left = prev;
//        if (prev)
//            prev->right = cur;
//        prev = cur;
//        InOrderConvert(cur->right, prev);
//    }
//
//    TreeNode* Convert(TreeNode* root) {
//        if (!root)
//            return nullptr;
//
//        //第一个结点new一个或者为nullptr
//        TreeNode* prev = nullptr;
//        InOrderConvert(root, prev);
//        TreeNode* head = root;
//
//        while (head && head->left)
//        {
//            head = head->left;
//        }
//        return head;
//    }
//};
//
//int main()
//{
//    int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
//    TreeNode A(1);
//    TreeNode B(2);
//    TreeNode C(3);
//    TreeNode D(4);
//    TreeNode E(5);
//    A.left = &B;
//    A.right = &C;
//    B.left = &D;
//    C.right = &E;
//    
//    Solution s;
//    //std::vector<vector<int>> vv = s.levelOrder(&A);
//    s.treeToDoublyList(&A);
//
//
//
//
//	return 0;
//}
