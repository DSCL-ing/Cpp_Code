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
	//const_iterator<T,const T&,const T*>
	//iterator<T, T&, T*>

	template<class T, class Ref, typename Ptr>
	struct __RBTree_iterator
	{
		typedef RBTreeNode<T> node;
		node* _node;
		__RBTree_iterator(node* node)
			:_node(node)
		{}

		//首先,<class T, class Ref, class Ptr>这种写法能够提高复用性和灵活性(实现不同类型的迭代器)等,,库里迭代器都这么写
		//其次,模板参数中,T用于获取类型,Ref用于返回引用,Ptr用于返回指针

		using Self           = __RBTree_iterator<T,Ref,Ptr>;            //自己--实例化出下面两种迭代器
		using iterator       = __RBTree_iterator<T,T&,T*>;              //普通迭代器
		using const_iterator = __RBTree_iterator<T,const T&,const T*>;  //const迭代器
		__RBTree_iterator(const iterator& it) 
			:_node(it._node)
		{}
		//这个构造函数的作用,
	    //a.当迭代器被实例化成iterator时,他就是拷贝构造函数.      __RBTree_iterator<T,T&,T*>
		//b.当迭代器被实例化成const_iterator时,他是支持隐式类型转换的带参构造函数. __RBTree_iterator<T,const T&,const T*> 

		//这样实现的目的
	    // 能够复用普通迭代器,可以通过类型转换后直接实现出const迭代器


		//Ref为 T& 或 const T&, Ptr为 T* 或 const T*
		//typedef __RBTree_iterator<T, Ref, Ptr> Self;

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
			keyOfT kot;//kot是个仿函数,根据不同参数返回不同的参数对象
			node* cur = _root;
			while (cur)
			{
				if (key < kot(cur->_data)) // -------------------------------------------- 只需要重载一个 '<' 或 '>' 就可以比较大小
				{
					cur = cur->_left;
				}
				else if (kot(cur->_data) < key) // --------------------------------------------只需要重载一个 '<' 或 '>' 就可以比较大小
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
			
			keyOfT kot;

			node* cur = _root;
			node* parent = nullptr;
			while (cur)
			{
				if (kot(cur->_data) < kot(data)  ) // --------------------------------------------只需要重载一个 '<' 或 '>' 就可以比较大小
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (kot(data) < kot(cur->_data)) // --------------------------------------------只需要重载一个 '<' 或 '>' 就可以比较大小
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
			if ( kot(parent->_data) < kot(data)) // --------------------------------------------
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
			keyOfT kot;
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
				cout << kot(root->_data) << " 错误,与父节点同时为红色"; // --------------------------------------------
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
			keyOfT kot;
			if (root == nullptr)
			{
				return;
			}
			_InOrderTraversal(root->_left);
			cout << kot(root->_data) << " "; // --------------------------------------------
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




