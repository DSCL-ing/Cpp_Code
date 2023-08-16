#pragma once

/** note
 * 
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
 * 搜索时间复杂度:
 * 
 */


//AVL树的旋转
/**
 * 1.右单旋(左左):新结点插入在较高左子树的左树 -- (设为该左子树的根为"根",不一定是整棵树的根)
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
 * ? 为什么叫右单旋?  可以理解成右下旋
 * 
 * 2.左单旋(右右): 基本和右单旋一样
 * 
 * 3.新结点插入较高左子树的右侧(左右) :
 * $ 先左单旋再右单旋(先左子树的子(两个绝对值为1的)树旋,后两个父(两个绝对值为2的)旋)
 * 
 * 4.新结点插入较高右子树的左侧 -- (右左)
 * $: 先右单旋再左单旋
 * 
 * 
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

namespace test
{


	template<class K, class V>
	class AVLTreeNode
	{
		//三叉链: left right parent
		AVLTreeNode* left;
		AVLTreeNode* right;
		AVLTreeNode* parent;
		pair<K, V> _kv;     //键值对
		int _bf;            //balance factor -- 平衡因子 :默认规定为右子树高度减去左子树高度

		AVLTreeNode(const pair<K, V>& kv)
			:left(nullptr)
			, right(nullptr)
			, parent(nullptr)
			, pair(kv)
			, bf(0)
		{}

	};

	template<class K, class T>
	class AVLTree
	{
	public:
		typedef AVLTreeNode<K, V> node;
	private:
		node* _root;
	public:
		bool Insert(const pair(K, V > & kv)
		{
			if (!root)
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
					cur = cur->right;
				}
				else if (kv.first < cur->_kv.first)
				{
					parent = cur;
					cur = cur->left;
				}
				else
				{
					return false;
				}
			}
			cur = new node(kv);
			if (kv > parent->_kv.first)
			{
				parent->right = cur;

			}
			else
			{
				parent->left = cur;
			}
			cur->_parent = parent;
			cur->_bf = 0;
			
			while (parent)
			{
				if (cur == parent->left)
				{
					--parent->_bf;
				}
				else 
				{
					++parent->_bf;
				}

				if (parent->_bf == 0)
				{
					break;
				}
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//
				}
				else
				{
					assert(false);
				}

			}

			return true;
		}
	};

	void test_AVL1()
	{

	}
}