#pragma once

#include<assert.h>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
using std::pair;
using std::make_pair;
using std::string;


namespace test
{

	//与库中的RBT差异
	/**
	 *
	 * 库中还有结点数量 count
	 *
	 * 库中RBT是带头结点哨兵卫的,头结点的左是中序第一个(最小结点),右节点是中序的最后一个(最大结点),
	 * 哨兵卫的parent指向根节点,根节点的parent指向哨兵卫
	 *
	 * 库中的begin直接取head的left -- 函数:leftmost() //最左结点
	 * 库中的end 是head的right -- 不是rightmost,rightmost是最右结点,end是最右结点的下一个
	 * 库中的end 需要判断一下,防止只有左子树的歪脖子树时,end == head->right,死循环
	 *
	 * 和库的区别就是end,库的end能走回到head,我的不能,只能走到空就没了d
	 *
	 */


	enum Colour { RED, BLACK };

	template<class T> //T是什么,为什么只传T? T为key或pair,T是key或者key-value类型
	struct RBTreeNode
	{
		RBTreeNode* _left;
		RBTreeNode* _right;
		RBTreeNode* _parent;
		T _data; //data是key或pair
		Colour _col;

		RBTreeNode(const T& data)
			: _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _data(data)
			, _col(RED)
		{}
	};

	template<class T, class Ref, typename Ptr>
	struct __RBTree_iterator
	{
		typedef RBTreeNode<T> node;
		node* _node;
		__RBTree_iterator(node* node)
			:_node(node)
		{}


// 1、typedef __RBTreeIterator<T, T&, T*> itertaor;  拷贝构造
// 2、 typedef __RBTreeIterator<T, const T&, const T*> const_itertaor;
//  支持普通迭代器构造const迭代器的构造函数
		__RBTree_iterator(const __RBTree_iterator<T,T&,T*>& it)
			:_node(it._node)
		{}

		typedef __RBTree_iterator<T, Ref, Ptr> Self;

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &(_node->_data);
		}
		bool operator!=(const Self& x)
		{
			return _node != x._node;
		}
		Self& operator++()
		{
			//++逻辑
			/**
			 * 如果右子树不为空,则下一个是右子树的最左节点
			 *
			 * 如果右子树完了,则父亲也完了.
			 *
			 * 如果我是父亲的左,完了则走父亲
			 *
			 * 直到没有父亲,结束
			 *
			 * 方法1:三叉链非递归
			 * 方法2:借助栈,非递归
			 *
			 */
			 //if (!_node) //还不知为何不需要判空
			 //{
			 //	return *this;
			 //}

			 /**
			  * 特性:
			  * -- 除了右子树为空,每个结点的下一个是他的右子树走到空的那一个,
			  *
			  * 1.如果右子树不为空,,每个结点的下一个是他的右子树的最左结点,右子树往左走走到空的那一个,
			  * 2.如果右子树为空,则下一个是他所在的左子树的那个结点(祖先),cur往父亲的右倒着走,走到第一个出现的父亲的左,这个父亲就是下一个结点
			  * -- 沿着到根的路径往上走，找孩子是左子树的那个祖先
			  */
			if (_node->_right)
			{
				node* cur = _node->_right;
				while (cur->_left)
				{
					cur = cur->_left;
				}
				_node = cur;
			}
			else
			{
				node* cur = _node;
				node* parent = _node->_parent;
				while (parent && parent->_right == cur)
				{
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}

			return *this;
		}
		Self& operator--()
		{
			//和++对称
			if (_node->_left)
			{
				node* cur = _node->_left;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			else
			{
				node* cur = _node;
				node* parent = _node->_parent;
				while (parent && parent->_left == cur)
				{
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}
	};

	//参数K用在find,erase等,虽然K也可以被T取代了,但没必要,K更快
	template<class K, class T, class keyOfT> //库中还有1个compare，先不写了
	class RBTree
	{
	public:
		typedef RBTreeNode<T> node; //T是key或pair
	public:
		typedef __RBTree_iterator<T, T&, T*> iterator;
		typedef __RBTree_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			node* cur = _root;
			while (cur && cur->_left)//不能走到空
			{
				cur = cur->_left;
			}
			return iterator(cur);//返回中序的第一个结点,最左结点
		}

		iterator end() //end是最一个位置的下一个
		{
			return iterator(nullptr);//暂时可以这么写
		}

		const_iterator begin()const
		{
			node* cur = _root;
			while (cur && cur->_left)
			{
				cur = cur->_left;
			}
			return iterator(cur);
		}

		const_iterator end() const
		{
			return iterator(nullptr);
		}

	private:
		node* _root = nullptr;
	public:
		node* find(const K& key)
		{
			keyOfT kof;//kof是个仿函数,根据不同参数返回不同的参数对象
			node* cur = _root;
			while (cur)
			{
				if (key < kof(cur->_data)) // --------------------------------------------
				{
					cur = cur->_left;
				}
				else if (key > kof(cur->_data)) // --------------------------------------------
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

		pair<iterator, bool> insert(const T& data)
		{
			if (!_root)
			{
				_root = new node(data);
				_root->_col = BLACK;
				return std::make_pair(iterator(_root), true);
			}
			
			keyOfT kof;

			node* cur = _root;
			node* parent = nullptr;
			while (cur)
			{
				if (kof(data) > kof(cur->_data)) // --------------------------------------------
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (kof(data) < kof(cur->_data)) // --------------------------------------------
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return std::make_pair(iterator(cur), false);
				}
			}
			cur = new node(data);
			if (kof(data) > kof(parent->_data)) // --------------------------------------------
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			cur->_parent = parent;

			//调整/旋转
			node* newnode = cur;//调整过程cur会发生变化,将cur结点记住 -- 记住原来key的位置
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
			return std::make_pair(iterator(newnode), true);
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
			keyOfT kof;
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

			if (root->_col == RED && root->_parent->_col == RED)
			{
				cout << kof(root->_data) << " 错误,与父节点同时为红色"; // --------------------------------------------
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
			keyOfT kof;
			if (root == nullptr)
			{
				return;
			}
			_InOrderTraversal(root->_left);
			cout << kof(root->_data) << " "; // --------------------------------------------
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

}




