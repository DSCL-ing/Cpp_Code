#pragma once

#include<assert.h>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
using std::pair;

namespace test
{

	enum Colour { RED, BLACK }; 

	template<class K, class V>
	struct RBTreeNode
	{
		RBTreeNode* _left;
		RBTreeNode* _right;
		RBTreeNode* _parent;
		std::pair<K, V> _kv;
		Colour _col;

		RBTreeNode(const std::pair<K, V>& kv)
			: _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _kv(kv)
			, _col(RED)
		{}
	};

	template<class K, class V>
	class RBTree
	{
	public:
		typedef RBTreeNode<K, V> node;
	private:
		node* _root = nullptr;
	public:

		node* find(const K& key)
		{
			node* cur = _root;
			while (cur)
			{
				if (key < cur->_kv.first)
				{
					cur = cur->_left;
				}
				else if (key > cur->_kv.first)
				{
					cur = cur->_right;
				}
				else
				{
					return cur;
				}
			}
			return nullptr;
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			if (!_root)
			{
				_root = new node(kv);
				_root->_col = BLACK; 
				return true;
			}
			node* cur = _root;
			node* parent = nullptr;
			while (cur)
			{
				if (kv.first > cur->_kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (kv.first < cur->_kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			cur = new node(kv);
			if (kv.first > parent->_kv.first)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			cur->_parent = parent;

			while (parent && parent->_col == RED) 
			{
				node* g = parent->_parent; 
				if (parent == g->_right)
				{
					node* u = g->_left; 
					if (u && u->_col == RED)
					{
						g->_col = RED;
						parent->_col = BLACK;
						u->_col = BLACK;
						cur = g; 
						parent = cur->_parent;
					}
					else
					{
						if (cur == parent->_right)
						{
							RotateL(g);
							parent->_col = BLACK;
							g->_col = RED;
						}
						else
						{
							RotateR(parent);
							RotateL(g);
							g->_col = RED;
							cur->_col = BLACK;
						}
						break;
					}

				}
				else
				{
					node* u = g->_right; 
					if (u && u->_col == RED)
					{
						g->_col = RED;
						parent->_col = BLACK;
						u->_col = BLACK;
						cur = g;
						parent = cur->_parent;
					}
					else
					{
						if (cur == parent->_left)
						{
							RotateR(g);
							parent->_col = BLACK;
							g->_col = RED;
						}
						else
						{
							RotateL(parent);
							RotateR(g);
							g->_col = RED;
							cur->_col = BLACK;
						}
						break;

					}
				}
			}
			_root->_col = BLACK;
			return true;

		}
	public:
		void InOrderTraversal()
		{
			_InOrderTraversal(_root);
		}

		bool isBalanceTree()
		{
			//需要判断3个规则
			//1.根为黑
			if (_root && _root->_col == RED)
			{
				cout << "错误:根是红色" << endl;
				return false;
			}

			//2.不能有连续得红
			//3.黑同
			int benchmark = 0;
			node* cur = _root;
			while (cur)
			{
				if (cur->_col == BLACK)
				{
					++benchmark;
				}
				cur = cur->_left;
			}
			return _check(_root, 0, benchmark);
		}

		int Height()
		{
			return _Height(_root);
		}
		~RBTree()
		{
			Destroy(_root);
		}

	private:
		void Destroy(node*& root)
		{
			if (!root)
			{
				return;
			}
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
			root = nullptr;
		}

		bool _check(node* root, int blackNum, int benchmark) 
		{
			if (!root) //
			{
				if (blackNum != benchmark)
				{
					cout << "错误:存在不同路径的黑色结点数量不相同" << endl;
					return false;
				}
				return true;
			}

			if (root->_col == BLACK)
			{
				++blackNum;
			}

			if (root->_col == RED &&  root->_parent->_col == RED)
			{
				cout << root->_kv.first << " 错误,与父节点同时为红色";
				return false;
			}

			return _check(root->_left, blackNum, benchmark) && _check(root->_right, blackNum, benchmark);
		}

		int _Height(node* root)
		{
			if (!root)
			{
				return 0;
			}
			int leftH = _Height(root->_left);
			int rightH = _Height(root->_right);

			return leftH > rightH ? leftH + 1 : rightH + 1;
		}

		void _InOrderTraversal(node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrderTraversal(root->_left);
			cout << root->_kv.first << " ";
			_InOrderTraversal(root->_right);
		}

		void RotateL(node* parent)
		{
			node* subR = parent->_right;
			node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}

			node* pparent = parent->_parent;

			subR->_left = parent;
			parent->_parent = subR;

			if (!pparent)
			{
				_root = subR;
				_root->_parent = nullptr;
			}
			else
			{
				if (pparent->_left == parent)
				{
					pparent->_left = subR;
				}
				else
				{
					pparent->_right = subR;
				}
				subR->_parent = pparent;
			}
		}

		void RotateR(node* parent)
		{
			node* subL = parent->_left;
			node* subLR = subL->_right;

			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}

			node* pparent = parent->_parent;

			subL->_right = parent;
			parent->_parent = subL;


			if (parent == _root)
			{
				_root = subL;
				_root->_parent = nullptr;
			}
			else
			{
				if (pparent->_left == parent)
				{
					pparent->_left = subL;
				}
				else
				{
					pparent->_right = subL;
				}
				subL->_parent = pparent;
			}
		}
	};

	void test_RBTree1() 
	{
		int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
		//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		test::RBTree<int, int> t;
		for (auto i : arr)
		{
			t.Insert(std::make_pair(i, i));
		}
		t.InOrderTraversal();
		cout << endl;
		cout << t.isBalanceTree() << endl;
	}

#include<time.h>
	void test_RBTree2() //随机数测试
	{
		srand((size_t)time(0));
		const size_t N = 5000000;
		test::RBTree<int, int> t;
		for (size_t i = 0; i < N; ++i)
		{
			size_t x = rand() + i;
			//size_t x = rand()*i - rand();
			//cout << "x:>" << x << "\t";
			t.Insert(std::make_pair(x, x));
		}
		//cout << t.isBalanceTree() << endl;
		cout << "RBT高度:>" << t.Height() << endl;
	}

	void test_RBTree3()
	{
		int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
		//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		test::RBTree<int, int> t;
		for (auto i : arr)
		{
			t.Insert(std::make_pair(i, i));
		}


		auto* ret = t.find(15);
		if (ret)
			cout << ret->_kv.first;


	}

}




