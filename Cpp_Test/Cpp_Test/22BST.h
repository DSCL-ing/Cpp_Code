#pragma once

//BST binary search tree /binary sort tree
/**
 * 中文名:二叉搜索树或二叉排序树
 *
 *
 *
 * 注:空树也是BST
 * 性质:
 * 左子树的所有键值小于根,根小于右子树的所有键值
 *
 * 特点
 * 1.BST的中序/中根遍历的结果是升序排序
 *
 * 2.默认的BST不允许冗余 -- 即不允许有重复的值
 *
 * 3.插入的第一个值就是根
 *
 * 4.删除
 * a.叶子结点:直接删
 * b.单路:续接
 * c.多路:尾删除法:用左子树的最大结点或右子树的最小结点
 * $ 叶子结点可以并到单路去,总共有4种独立情况
 * $ 多路有两种情况
 * 
 * 5.树的最大最小结点
 * a.一棵树中最大结点是最右结点(是右结点,且是最右边)
 * b.一棵树中最小结点是最左结点(是左结点,且是最左边)
 *
 * 拓展:平衡二叉树,红黑树,AVL树
 */


namespace test
{
	template<class K>
	struct BSTreeNode
	{
		BSTreeNode* _left;//左子树
		BSTreeNode* _right;//右子树  
		K _key; //key接收任何类型,所以key类型K,所以引出模板

		//没写构造函数报的错
		//无法将参数 1 从“const K”转换为“const BSTreeNode<K> &”
		BSTreeNode(const K& key)
			:_key(key)
			, _left(nullptr)
			, _right(nullptr)
		{}
	};

	template<class K>
	class BSTree
	{
	public:
		typedef BSTreeNode<K> node;
	private:
		node* _root = nullptr;
	public:

		~BSTree()
		{

		}

		bool insert(const K& key)
		{
			//插入
			/**
			 * 1.空树
			 *	插入的第一个键 就是根
			 *
			 * 2.非空树
			 * 如果比键小,往左走
			 * 如果比键大,往右走
			 * (键目前不允许相等)
			 * 走到空就可以插入
			 *
			 * 结束条件:cur为空 插入
			 * //循环条件:cur不为空 继续走
			 *
			 */

			if (_root == nullptr)
			{
				_root = new node(key);
				return true;
			}
			node* parent = _root;
			node* cur = _root;
			while (cur != nullptr)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			cur = new node(key);
			if (parent->_key > key)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			return true;
		}

		bool find(const K& key)
		{
			//if (_root == nullptr)
			//{
			//	return false;
			//}
			node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else
				{
					return true;
				}
			}
			return false;
		}

		bool erase(const K& key)
		{
			//删除
			/**
			 * 1.叶子 直接null
			 * 2.单路 续接 -- 需要parent;
			 * 3.双路 尾删除法?找左子树的最大结点或右子树的最小结点
			 *  结束条件:cur为空或cur._key == key
			 * 循环条件:cur不为空
			 *
			 * 叶子和单路可以合并
			 *
			 * 删除后不需要置空,因为删除最后都会去链接下一个结点,而叶子结点下面都为空,最终一定会为空
			 *
			 */
			node* parent = _root;
			node* cur = _root;

			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{

					/**
					 * 单路模拟图
					 *          0				       0
					 *        /    \			     /    \
					 *       1      1			    1      1
					 *      / \    / \			   / \    / \
					 *     n   0  0   n			  0   n  n   0
					 *
					 * 1为要删除的结点 ,0为结点 ,n为null
					 *
					 * 	1.左子树为空           2.右子树为空
					 *            0	  0			        0  0
					 * 	         /     \		       /     \
					 * 	        1       1		      1       1
					 * 	       / \     / \		     / \     / \
					 * 	      n   0   n   0 	    0   n   0   n
					 *
					 * //只需要将删除结点的非空子树接到父亲上即可 --
					 *
					 */

					 //必须先从删除结点的左子树或右子树为空开始,然后再反向向上判断父亲

					 //要删除的结点的左子树为空
					if (cur->_left == nullptr)
					{
						//要删除的结点是根结点
						if (cur == _root)
						{
							//结点的左子树为空,就让根节点的右为新根
							_root = cur->_right;
						}
						else//互斥:要删除的结点不是根结点
						{
							//删除的结点是父亲的左孩子
							if (cur == parent->_left)
							{
								//由于要删除的结点的左子树为空,把右子树接上去成为父亲的新左孩子
								parent->_left = cur->_right;
							}
							else //删除的结点是父亲的右孩子
							{
								//由于左子树为空,把右子树接上去成为父亲的新右孩子
								parent->_right = cur->_right;
							}
						}
						delete cur;
					}
					else if (cur->_right == nullptr)//要删除的结点的右子树为空
					{
						//删除的结点是根
						if (cur == _root)
						{
							//根节点的右为根,就让根节点的左为新根
							_root = cur->_left;
						}
						else//互斥:删除的结点不是根
						{
							//删除的结点是父亲的左孩子
							if (cur == parent->_left)
							{
								//要删除的结点的右子树为空,就把要删除的结点的左子树接上成为父亲的新左孩子
								parent->_left = cur->_left;
							}
							else //互斥:删除的结点不是左孩子,是父亲的右孩子
							{
								//要删除的结点的右子树为空,就把要删除的结点的左子树接上成为父亲的新右孩子
								parent->_right = cur->_left;
							}
							delete cur;
							//cur = nullptr;
						}
					}
					else
					{
						/**
						 * 
						 * 用左子树的最大结点或右子树的最小结点替代法(默认右子树)
						 *
						 * mr:右子树最小结点,1要删除的结点
						 * 多路情况下与头结点无关,因为让代替的结点的key直接赋值给要删除的结点,最终删除的实际是替代结点
						 * 通过key赋值从而达到删除
						 *
						 * 情况一 正常情况:右子树的最小结点是左孩子
						 *        0                      1
						 *       / \                    / \
						 *      0   1                  0   0
						 *         / \                    / \
						 *        0   0                  mr  0
						 *           / \                      \
						 *          mr  0                      0
						 *
						 * 情况二  特殊情况:右子树的最小结点是右孩子,且是要删除的结点的右孩子
						 * 	     0				         1
						 * 	    / \				        / \
						 * 	   0   1			  	   0   mr
						 * 	      / \			  	        \
						 * 	     0   mr			  	         0
						 * 		 	  \       	  	        / \
						 * 		 	   0
						 *
						 *
						 */
						node* pminRight = cur; //要删除的结点的右子树的最小结点的父亲
						node* minRight = cur->_right;//要删除的结点的右子树的最小结点
						//找右子树最小结点
						while (minRight->_left)
						{
							pminRight = minRight;
							minRight = minRight->_left;
						}
						//找到右子树最小结点后直接赋值 -- 完成替代
						cur->_key = minRight->_key;//

						//替代完成后,需要回收minrRight结点 -- 回收处理
						if (pminRight->_right == minRight)//如果循环没有进去,即第一个minRight->_left为空,right可能不为空
						{
							//右子树的最小结点成为父结点的新右子树
							pminRight->_right = minRight->_right;
						}
						else //循环进入了
						{
							//右子树的最小结点成为父结点的新右子树
							pminRight->_left = minRight->_right;
						}

						delete minRight;
					}
					return true;
				}

			}
			return false;
		}

		//无参递归常用方法：套壳：
		/**
		 * 由于递归需要访问到私有成员,而外界访问私有成员需要友元或使用接口get什么什么
		 *
		 * C++一般不喜欢使用get,所以引出了套壳
		 *
		 * 套壳:壳面向对象,壳内调用私有,面对对象隐藏细节
		 *
		 * 能不能用缺省参数root? 我的理解是,缺省参数在传在this之前,即先传缺省再传this,接收此时的缺省参数root没有this
		 * //不行,因为缺省参数访问成员需要this,但是this不可以作为缺省参数,缺省参数需要是全局变量或是常量,
		 */
		void InOrderTraversal()
		{
			_InOrderTraversal(_root);
		}

	private:

		void _InOrderTraversal(node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrderTraversal(root->_left);
			cout << root->_key << " ";
			_InOrderTraversal(root->_right);
		}
	};


	void test_BST1()
	{

		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		BSTree<int> bst;

		//测试插入
		for (auto i : a)
		{
			bst.insert(i);
		}
		bst.InOrderTraversal();


		//测试find
		cout << endl;
		for (auto i : a)
		{
			if (bst.find(i))
			{
				cout << "找到了" << endl;
			}
			else
			{
				cout << "没找到" << endl;
			}
		}

		////删除单路和叶子测试
		//bst.erase(10);
		//bst.erase(14);
		//bst.erase(13);
		//bst.erase(1);
		//bst.erase(4);
		//bst.erase(6);
		//bst.erase(3);
		//bst.erase(8);  // 根没处理好前先别删
		//bst.erase(7);
		//bst.InOrderTraversal();

		//删除多路测试
		bst.erase(8);
		bst.erase(10);
		bst.erase(3);
		bst.erase(14);
		bst.erase(1);
		bst.InOrderTraversal();

	}


}

