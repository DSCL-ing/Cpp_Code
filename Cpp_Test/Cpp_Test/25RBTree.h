﻿#pragma once

//红黑树 Red-Black Tree
/**
 * 简称RBT
 * 
 * 红黑树是2-3-4树的特殊实现
 * 
 * 红黑树的性质/规则
 * 1. 每个结点不是红色就是黑色
 * 2. 根节点是黑色的 -- (root点要转成黑色)
 * 3. 如果一个节点是红色的，则它的两个孩子结点是黑色的 -- (不存在两个连续的红结点) (连红规则)
 * 4. 对于每个结点，从该结点到其所有后代叶结点的简单路径上，均 包含相同数目的黑色结点(黑同规则)
 * 5. 每个叶子结点都是黑色的(此处的叶子结点指的是空结点 -- NIL结点,不影响黑节点的数量) -- 为了与3不矛盾
 * 
 * ?如何保证最长路径为最短路径的两倍及以内? 
 * $ 最短是全黑
 * $ 最长是黑中插入不连续的红(规则3) -- 插满后是全黑(最短)的两倍
 * $ 由根结点和NIL结点为黑色(规则2和规则5)限制
 * 因此得以保证
 * 
 * ($ 走到空才算一条路径)
 * 
 * $ 结点和路径信息:
 * 设全部的黑色结点有N个,则最短路径长度为logN,
 * 整棵树的结点数量:[N,2N]之间,最长路径为2logN  -- 
 * 解释:是一种理想状态--插入红节点,并不填满树,插满后红节点数量等于黑结点数量--红黑相间的情况
 * 
 * $ 最长路径上的黑节点的数目和最短路径上的黑节点的数目相等
 * 
 * 理想情况下,AVL查找10个结点需要30次,RB最多查找60,两倍,但是对于计算机来说基本没有区别
 * 
 * 红黑树对比AVL树优点:
 * $ 旋转更少了 --红黑树的平衡性能比AVL的略差些，但是经过大量试验(别人)证明，实际上红黑树的效率还是很不错了，仍能达到O(logN)
 * 
 * C++/JAVA的容器底层需要的平衡搜索树基本都是红黑树,AVL树很少使用
 * 
 * 红黑树应用很广，大量应用在底层数据结构中，主要用于存储和查找。平日开发很少自己去写红黑树，
 * 因为我们大部分都是使用别人封装后的接口而已，但是深入了解数据结构和算法是非常必要的。
 * 
 * 
 * 经过测试,目前发现AVL和RB在冗余量大的情况下,高度有差异,冗余量小高度差异不大 -- 但量级基本相同,说明红黑树更优
 * 
 * 
 */


#include<assert.h>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
using std::pair;

namespace test
{

	enum Colour { RED, BLACK }; //...保证结点不是红色就是黑色

	template<class K, class V>
	struct RBTreeNode
	{
		//三叉链: left right parent
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

		bool insert(const std::pair<K, V>& kv)
		{
			//BST流程
			if (!_root)
			{
				_root = new node(kv);
				_root->_col = BLACK; //根结点给黑
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


			/** 红黑树的实现 -- 插入
			 *
			 *
			 *
			 * 红黑树默认插入的结点为红色 -- 规则3更容易实现,不冲突规则
			 * 注:不许修改新插入结点的颜色,规定吧,满足红黑树,待研究
			 *
			 * 1.如果插入位置的父亲是红色的处理:
			 * 插入后根据规则3,因为插入的结点是红色,所以parent必须变黑 -- 上黑下红规律
			 * $ 如果父亲变黑了,且叔叔存在且为红,则将叔叔也要跟则变黑(规则4),然后再将爷爷变红(规则4)
			 * -- 如果爷爷的父亲是黑的,则处理结束 . 否则循环,直至到根
			 * $ 如果经过处理后,根变为红色,则最终需要将根置为黑色
			 *
			 * 2.如果插入的位置没有叔叔的处理:旋转 -- 将祖父旋下来
			 * $ 插入在父亲的左边,则右旋
			 *
			 * 如果插入位置的父亲是黑色,则不需要处理
			 * ...
			 *
			 * ------------------------------------------------------------------------------------------
			 *
			 *  直接变色情形							     修改后
			 *             g(黑)						 |	            g(红)				
			 *    u(红)          p(红)				     |	    u(黑)         p(黑)			
			 *                        c(红)              |	                       c(红)      
			 *
			 * 情形1：该树为空树，直接插入根结点的位置，违反性质1，把根节点颜色由红改为黑即可。
			 * 情形2：插入节点N的父节点P为黑色，不违反任何性质，无需做任何修改。
			 * 情形3: 插入结点N的父节点P为红色,叔叔u为红色
			 * $ 操作: 把 u和p改成黑,G改成红,如果G为根,再改成黑(调整结束再改也无所谓)
			 * $ 解释:本来就一行黑,修改后如果G不改则会多了一个黑,与G的兄弟子树(有的话)不平衡.若G是根则无所谓
			 * 
			 * $ 需要旋转的情形(为了保持规则4(一样多的黑结点):
			 * 在不修改新插入结点颜色的情况下,无论怎么变色都不平衡,即不能维持规则4的情况下,只能进行旋转操作(降高度才能保持黑同规则) --
			 * $ 降高度其实是改变不同路径的长度,-- 维持黑同规则的最终手段
			 * 
			 * ? 双红且u为黑的情况下(双旋),为什么不能直接把p变黑? 
			 * $ 不能直接把p变黑,因为p的另一条子路可能会有黑,变的话可能会违反规则4(黑同) -- 必须保持双红,通过旋转调整 ->g变红,cur变黑
			 *
			 * 单旋情形									    旋转后
			 *            g(黑)							 |	           p(黑)
			 *   u(黑)           p(红) 				     |	   g(红)           c(红)
			 *                         c(红)			 | u(黑)	c的左(黑)
			 *
			 * 双旋情形                                      旋转后
			 *            g(黑)						     |                 c(黑)
			 *   u(黑)             p(红) 				 |     g(红)                  p(红)
			 *                 c(红)					 |  u(黑)  c的左(黑)
			 *
			 * 情形4/5: p为红,u为黑/或u不存在
			 * 操作: 旋转,直线单旋,折现双旋
			 * 变则:双旋(cur->黑,g->红)
			 *
			 * $ 注:
			 * 1.u为黑的情况是由子结点向上调整产生的(因为每次插入的结点都是红色,调整才能变黑) , 且cur结点原来是黑色的,红色是由下面结点调整的
			 * 2.u不存在(变色后叔叔路径会缺一个黑 ),说明cur一定是新增结点, -- ,插在红p则平衡不了,需要旋转
			 *
			 * 继续调整的跨度为cur->grandfather , 因为父亲位于中间位置,最后修改的是祖父,只有祖父对上面的结点有影响
			 *
			 *
			 * 综上,循环条件为parent的颜色(parent存在),如果父亲是黑色,简单,循环结束.如果父亲是红色,需要处理
			 *
			 */

			while (parent && parent->_col == RED) //parent==RED 说明parent一定不是根,即一定存在祖父
			{
				node* g = parent->_parent; //grandfather
				if (parent == g->_right)
				{
					node* u = g->_left; //uncle
					//uncle存在且为红
					if (u && u->_col == RED)
					{
						g->_col = RED;
						parent->_col = BLACK;
						u->_col = BLACK;
						//cur->_col = RED;

						//循环继续走:
						cur = g; //为什么? 因为grandfather 变红了
						parent = cur->_parent;
					}
					//uncle不存在或uncle为黑
					else
					{
						/**
						 * 祖父右单旋情形									    旋转后
						 *            g(黑)							 |	           p(黑)
						 *   u(黑)           p(红) 				     |	   g(红)           c(红)
						 *                         c(红)			 | u(黑)	c的左(黑)
						 */
						if (cur == parent->_right)
						{
							RotateL(g);
							parent->_col = BLACK;
							g->_col = RED;
							//u->_col = BLACK;
							//cur->_col = RED;
						}
						/**
						 * 双旋情形                                      旋转后
						 *            g(黑)						     |                 c(黑)
						 *   u(黑)           p(红) 					 |          g(红)		 p(红)         
						 *                c(红)        		    	 | 		u(黑) 			       x        
						 */
						else
						{
							RotateR(parent);
							RotateL(g);
							g->_col = RED;
							cur->_col = BLACK;
							//parent->_col = RED;
							/* u->_col = BLACK;*/ //可能不存在.

						}
						break;
					}

				}
				else
				{
					node* u = g->_right; //uncle
					//uncle存在且为红
					if (u && u->_col == RED)
					{
						g->_col = RED;
						parent->_col = BLACK;
						u->_col = BLACK;
						//cur->_col = RED;
						cur = g;
						parent = cur->_parent;
					}
					//uncle不存在或uncle为黑
					else
					{
						if (cur == parent->_left)
						{
							RotateR(g);
							parent->_col = BLACK;
							g->_col = RED;
						}
						/**
						 * 双旋情形                                      旋转后
						 *            g(黑)						     |                 c(黑)
						 *    p(红)             u(黑)				 |          p(红)		 g(红)         
						 *  x      c(红)        					 | 		x 			       u(黑)  
						 */
						else
						{
							RotateL(parent);
							RotateR(g);
							g->_col = RED;
							cur->_col = BLACK;
							//parent->_col = RED;
							/* u->_col = BLACK;*/ //不能放开,u可能不存在
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

		bool _check(node* root,int blackNum,int benchmark) //blackNum:该层已经过的黑色结点个数.   benchmark:基准值,随便一条路径的黑色结点的个数
		{
			if (!root) //
			{
				if (blackNum != benchmark)
				{
					cout << "错误:存在不同路径的黑色结点数量不相同" << endl;
					return false;
				}
				return true;//_root为空,递归结束. 非_root,路径递归结束 -- 很妙,不用再外面判空
			}

			if (root->_col == BLACK)
			{
				++blackNum;
			}

			if (root->_col == RED && /*root->_parent(由第一个if知parent一定存在)&&*/  root->_parent->_col == RED)//检查父子是否同时为红
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

		/**
		 *
		 *            p(parent)
		 *        sL(subL)      c
		 *       a   b(subLR)
		 *
		 */
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

	void test_RBTree1() //常规测试
	{
		int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 }; 
		//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		test::RBTree<int, int> t;
		for (auto i : arr)
		{
			t.insert(std::make_pair(i, i));
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
			size_t x = rand()+i;
			//size_t x = rand()*i - rand();
			//cout << "x:>" << x << "\t";
			t.insert(std::make_pair(x, x));
		}
		//cout << t.isBalanceTree() << endl;
		cout <<"RBT高度:>"<< t.Height() << endl;
	}

	void test_RBTree3()
	{
		int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
		//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		test::RBTree<int, int> t;
		for (auto i : arr)
		{
			t.insert(std::make_pair(i, i));
		}


			auto* ret = t.find(15);
			if (ret)
				cout << ret->_kv.first;


	}

}




