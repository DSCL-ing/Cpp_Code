#pragma once

/** note
 * 简称:AVLT
 * AVL树,也叫高度平衡搜索二叉树
 * 
 * 
 * 
 * 命名:两位俄罗斯的数学家G.M.Adelson-Velskii和E.M.Landis在1962年发明解决二叉搜索树退化成单支树的方法
 * -- 所以AVL树以两位俄罗斯数学家的名的开头命名A.V.L.
 * 
 * 解决问题的方法:
 * 当向二叉搜索树中插入新结点后，如果能保证每个结点的左右子树高度之差的绝对值不超过1
 * (需要对树中的结点进行调整)，即可降低树的高度，从而减少平均搜索长度。
 * 
 * AVL树的定义
 * 一棵AVL树或者是空树，或者是具有以下性质的二叉搜索树：
 * $ 它的左右子树都是AVL树
 * $ 左右子树高度之差(简称平衡因子)的绝对值不超过1(-1/0/1)
 * balance factor(平衡因子/平衡系数) -- AVL树不一定有平衡因子(有些算法没有)
 * 
 * ? 为什么高度差不能绝对为0? 因为有些情况高度差绝对不可能为0 -- 如偶数个结点时
 * 
 * 搜索时间复杂度:log2n
 * 
 * AVL树的性能:
 * AVL树是一棵绝对平衡的二叉搜索树，其要求每个节点的左右子树高度差的绝对值都不超过1，这
 * 样可以保证查询时高效的时间复杂度，即log_2 (N)。但是如果要对AVL树做一些结构修改的操
 * 作，性能非常低下，比如：插入时要维护其绝对平衡，旋转的次数比较多，更差的是在删除时，
 * 有可能一直要让旋转持续到根的位置。因此：如果需要一种查询高效且有序的数据结构，而且数
 * 据的个数为静态的(即不会改变)，可以考虑AVL树，但一个结构经常修改，就不太适合。
 * -- 纯搜索很强
 * 
 */


//AVL树的旋转
/**
 * 1.右单旋(左左,-2-1):新结点插入在较高左子树的左树 -- (设为该左子树的根为"根",不一定是整棵树的根)
 * $ 插入前,AVL树是平衡的
 * 插入后,以根的父节点为根的这棵子树不平衡 -- 设为"父根"
 * 旋转:将父根取出,根代替父根的位置,而父根取代根的右子树.如果根有右子树,则根的右子树成为父根的左子树
 * 
 * 解释:>
 * $ 根位于父根的左子树,将父根和他的右子树一起取出.左子树(根)与父根断链,且链接上父根的父亲的左子树(如果不是整个树的根的话),替代父根称为新的父根 -- 称为上提
 * $ 由于父根的值是大于根的(搜索树左小右大),所以父根取代的是根的右子树,
 * $ 若之前根有右子树,因为根的原右子树比根大,而父根又比他的左子树大,即比根的原右子树还大,所以根的原右子树插在父根的左树(父根的左树必为空,因为刚与根断链)
 * 
 * $ 如果父根是整棵树的根,则调整完后需要更新根节点
 * 助记:原有位置有子树的,被取代的,按从根开始插入,得到的位置就是新位置
 * 
 * ? 为什么叫右单旋?  可以理解成右下旋  -- 右边高右边旋
 * 
 * 2.左单旋(右右+2+1): 和右单旋一样
 * 
 * $ 单旋：你的右变我的左，我的左变你的右（先断子树后父树）
 * 
 * 
 * 
 * 3.新结点插入较高左子树的右侧(左右) :
 * $ 先左单旋再右单旋(先左子树的子(两个绝对值为1的)树旋,后两个父(两个绝对值为2的)旋)
 * 
 * 4.新结点插入较高右子树的左侧 -- (右左)
 * $: 先右单旋再左单旋
 * 
 * 
 * 
 * 注::::::::::::::::::::::::::::::::::::::::::::
 * $ 在下述例子中,图像只为具象出来写代码,举例用.实际上旋转的多种情况主要是看平衡因子
 * $ 选出四种旋转方式的例子的图并不代表所有的情况都如图,但这四种方式对应的平衡因子是所有情况
 * $ 所以算法没有问题,图要多揣摩一下
 * 
 * 
 * 实际就四种：
 * 1. /       2. \          3.    /               4.   \
 *   /            \               \                    /
 * 右旋         左旋        先左旋后右旋           先右旋后左旋
 * 
 * 
 * 
 */


//模拟实现AVL -- map底层
/**
 * 
 * 
 * insert插入
 * 1.三叉链链接到位(链接上插入的结点,新结点也要链接上父亲)
 * 2.更新平衡因子
 * $ 如果更新后所有的平衡因子都为-1,0,1其中一个,则不需要调整平衡树
 * $ 如果更新后有平衡因子的绝对值>1,则需要调整平衡树
 * 3.调整平衡树
 * 
 * note:
 * $ 新增的结点,只会影响到他祖先的这一路径的结点
 * $ 往上更新爷爷结点取决于parent的高度是否发生变化.变了则往上更新(前提是平衡状态),不变则不再更新.
 *   parent._bf如果更新后为0,说明结点插在矮树这边,使左右子树平衡,即高度不变
 *   parent._bf如果更行后为-1或1,说明左子树高或右子树高了,高度变了
 * $ 如果parent-_bf为2,则需要先处理,不能再继续更新(不再平衡)
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


	template<class K, class V>
	struct AVLTreeNode
	{
		//三叉链: left right parent
		AVLTreeNode* _left;
		AVLTreeNode* _right;
		AVLTreeNode* _parent;
		std::pair<K, V> _kv;     //键值对
		int _bf;            //balance factor -- 平衡因子 :默认规定为右子树高度减去左子树高度

		AVLTreeNode(const std::pair<K, V>& kv)
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
	public:
		typedef AVLTreeNode<K, V> node;
	private:
		node* _root = nullptr;
	public:
		bool insert(const std::pair<K, V>& kv)
		{
			if (!_root)
			{
				_root = new node(kv);
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
			if (kv.first>parent->_kv.first)
			{
				parent->_right = cur;

			}
			else
			{
				parent->_left = cur;
			}
			cur->_parent = parent;
			//cur->_bf = 0;
			//cout << "插入后父亲的平衡因子:>"<<parent->_bf << " ";
			while (parent)
			{
				if (cur == parent->_left)
				{
					--(parent->_bf);
					//cout << "更新后父亲的平衡因子:>"<<parent->_bf << " ";
				}
				else 
				{
					++(parent->_bf);
					//cout << "更新后父亲的平衡因子:>" << parent->_bf << " ";
				}

				if (parent->_bf == 0)
				{
					break;
				}
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					parent = parent->_parent;
					cur = cur->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//
					if (parent->_bf == 2 && cur->_bf == 1)
					{
						//cout << "RotateL" << " ";
						RotateL(parent);
					}
					else if (parent->_bf == -2 && cur->_bf == -1)
					{
						//cout << "RotateR" << " ";
						RotateR(parent);
					}
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						//cout << "RotateLR" << " ";
						RotateLR(parent);
					}
					else if (parent->_bf == 2 && cur->_bf == -1)
					{
						//cout << "RotateRL" << " ";
						RotateRL(parent);
					}
					else
					{
						cout << " 错误的结点的父 " << parent->_kv.first << " 错误的结点的子 " << cur->_kv.first << " ";
						assert(false);
					}
					break;
				}
				else
				{
					assert(false);
				}

			}
			//cout << endl;
			return true;
		}
	public:
		void InOrderTraversal()
		{
			_InOrderTraversal(_root);
		}

		bool isBalanceTree()
		{
			return _isBalanceTree(_root);
		}

		int Height()
		{
			return _Height(_root);
		}

	private:

		bool _isBalanceTree(node* root)
		{
			if (!root)
			{
				return true;
			}
			//左右子树高度差的模或bf的模是否小于2
			int leftH = _Height(root->_left);
			int rightH = _Height(root->_right);
			int diff = rightH - leftH;
			int Hdiff_abs = abs(rightH - leftH);
			//if (abs(root->_bf) >2 || Hdiff_abs > 2)
			//{
			//	cout << "左右子树高度差的模或bf的模大于2,key为:>" << root->_kv.first << endl;
			//	return false;
			//}

			////左右子树的高度差的模是否为bf
			//if (diff != root->_bf)
			//{
			//	cout << "左右子树的高度差的模不等于平衡因子,key为:>"<<root->_kv.first <<" 平衡因子为: "<< root->_bf << endl;
			//	//return false;

			//}

			return abs(root->_bf) < 2
				&& Hdiff_abs < 2
				&& diff == root->_bf
				&& _isBalanceTree(root->_left)
				&& _isBalanceTree(root->_right);

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
			cout << "key:> " << root->_kv.first << " " << "bf:> " << root->_bf << endl;
			_InOrderTraversal(root->_right);
		}


		
		/**左单旋
		 * 设x 为   x           y为   y        z为 z
		 *        1   1             1                 1
		 * 
		 * 
		 * a,b,c一定是是x,y,z三种情况之一  
		 * 
		 * 当c为x情况下,在经过祖先c插入的一定是符合左单旋 -- 右右(右右分别为1,c)
		 * 
		 *           p(parent)
		 *       a        sR(subR)
		 *              b(subRL)  c
		 * 
		 * 左单旋操作
		 * 1.旋转
		 * $.将b链接到p的左边 然后更新b的_parent , _parent=p(前提是b不为空)
		 * $.将p链接到sR,然后更新p的_parent , _parent=sR
		 * 2.更新根
		 * $.如果是根(pparent==nullptr),则更新_root , _root=subR 
		 * $.如果不是根,判断是祖先结点的左还是右,然后再链接上,最后记得更新_parent
		 * 3.更新parent和subR的平衡因子_bf, 旋转后平衡因子都为0 
		 * 
		 */
		void RotateL(node* parent)//左单旋 -- parent是bf为2的结点
		{
			node* subR = parent->_right;//sR
			node* subRL = subR->_left; //b
			
			//1.将b链接到p的右边 然后更新b的parent=p(前提是b不为空)
			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}

			node* pparent = parent->_parent;

			//2.将p链接到sR,然后更新p的parent=sR
			subR->_left = parent;
			parent->_parent = subR;


			//3.更新根
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
			parent->_bf = subR->_bf = 0;

		}

		/**
		 * 
		 *            p(parent)
		 *        sL(subL)      c  
		 *       a   b(subLR)  
		 * 
		 */
		void RotateR(node* parent)//右单旋 -- parent是bf为-2的结点
		{
			node* subL = parent->_left;//sR	
			node* subLR = subL->_right; //b

			//1.将b链接到p的左边 然后更新b的parent=p(前提是b不为空)
			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}

			node* pparent = parent->_parent;

			//2.将p链接到sL,然后更新p的parent=sL
			subL->_right = parent;
			parent->_parent = subL;


			//3.更新根
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
			parent->_bf = subL->_bf = 0;

		}

		/**
		 * 
		 *                       p
		 *       sL                           |d--高度h
		 * |a|--高度h    sLR                   d 
		 *  a          b      c--高度h-1       d
		 *  a          b      c                         
		 * 
		 * 
		 * 
		 * 
		 * 
		 *  $ 在sLR处插入都会引发旋转,因为d矮了
		 *  
		 * 旋转:先左旋,后右旋
		 * 
		 * 1.先左旋sL结点,后右旋p结点
		 * 2.更新根
		 * 3.更新平衡因子
		 * $.插在右边,sL为-1
		 * $.插在左边,p为-1
		 * $,如果插入后sLR为0(刚好sLR是新插入的),即h=0，整棵树就3结点，平衡后都是0
		 *
		 * 
		 * 
		 * 
		 */
		void RotateLR(node*parent) //左右
		{
			node* subL = parent->_left;
			node* subLR = subL->_right;
			int bf = subLR->_bf;
			RotateL(parent->_left);
			RotateR(parent);
			if (bf == 1)
			{
				parent->_bf = 0;//虽然左旋和右旋已经置零，但是以防万一，安全一点，再次置零
				subLR->_bf = 0;//虽然左旋和右旋已经置零，但是以防万一，安全一点，再次置零
				subL->_bf = -1;//必须手动置零
			}
			else if (bf == -1)
			{
				parent->_bf = 1;//必须手动置零
				subLR->_bf = 0;//虽然左旋和右旋已经置零，但是以防万一，安全一点，再次置零
				subL->_bf = 0;//虽然左旋和右旋已经置零，但是以防万一，安全一点，再次置零
			}
			else if (bf == 0)
			{
				parent->_bf = 0;
				subLR->_bf = 0;
				subL->_bf = 0;
			}
			else//以防万一，安全一点
			{
				assert(false);
			}
		}

		/**
		 * 
		 *                       p
		 *    |a--高度h                  sR                          
		 *     a              sRL                 |d|--高度h  
		 *     a            b      c--高度h-1      d          
		 *                  b      c               d                     
		 * 
		 */
		void RotateRL(node* parent) //右左
		{
			node* subR = parent->_right;
			node* subRL = subR->_left;
			int bf = subRL->_bf;
			RotateR(parent->_right);
			RotateL(parent);
			if (bf == 1) //插在右边,右边平衡,左边不平衡
			{
				subR->_bf = 0;
				parent->_bf = -1;
				subRL->_bf = 0;
			}
			else if (bf == -1) //插在左边,左边平衡,右边不平衡
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
			else//以防万一，安全一点
			{
				assert(false);
			}
		}


	
	};

	void test_AVL1()
	{
		int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 }; //结点7:左右 结点9:右 结点26:左 结点18:右左 结点15:左右
		//int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 }; //只有一个右左,结点6
		test::AVLTree<int, int> t;
		for (auto i : arr)
		{
			cout << "i:>" << i << "\t";
			t.insert(std::make_pair(i,i));
			cout << endl;
		}
		t.InOrderTraversal();
		cout << "是否为AVL树? " << t.isBalanceTree() << endl;
	}

#include<time.h>
	void test_AVL2()
	{
		srand((size_t)time(0));
		const size_t N = 5000000;
		test::AVLTree<int, int> t;
		for (size_t i = 0; i < N; ++i)
		{
			size_t x = rand() + i;
			//size_t x = rand() * i - rand();
			//cout << "x:>" << x << "\t";
			t.insert(std::make_pair(x, x));
		}
		//cout << t.isBalanceTree()<<endl;
		cout << "AVLT高度:>" << t.Height() << endl;
	}
}