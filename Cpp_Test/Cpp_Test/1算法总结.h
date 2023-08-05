#pragma once


//实现某功能
/**
 * 1.先描述所有应用此功能的场景
 * 
 * 2.寻找特征,分类
 * 
 * 
 */

//空间利用率
/**
 * 
 * 
 * 追求效率而空间浪费过多
 * 
 * .
 */

//时间效率
/**
 * 循环次数是否有限个，有限个则为n(1)
 * 
 * 空间换时间
 * 
 */

//一些技巧
/**
 * 命题和否命题.
   bool pInLeft = isInTree(root->left,p);
   bool pInRight = !pInLeft;
   bool qInLeft = isInTree(root->left,q);
   bool qInRight = !qInLeft;
   //都在左->递归左子树
   if(pInLeft&&qInLeft)
       return lowestCommonAncestor(root->left,p,q);
   //都在右->递归右子树
   else if(pInRight&&qInRight)  
       return lowestCommonAncestor(root->right,p,q);
   //一左一右 --> 性质:最近的公共祖先
   else     
       return root;
 * .
 */



//一些算法
/**
 * BF暴力匹配match ,还有KMP(纸老虎) , BM(最实用)
 * 
 * .
 */

//一些语法问题
/**
 * 1.while迭代的问题
 * 迭代前看循环能不能进去,我们主要思维和逻辑都在循环体内,单往往特殊情况是循环没进去,如果前置条件没处理好的话就会出问题
 * 例:BST的erase
 * 
 * 2.if-else问题
 * 如果if内带了return,那么下一句else可加可不加.
 * $ 但如果if内没有return之类,则就要考虑else
 * a.如果else内容是必须执行的,则可以不加else
 * b.如果else内容是和if互斥的,则必须加eles
 * $ 一般以并列排斥为同一组ifelse
 * 
 */


//栈的使用场景
/**
 * 如果是想从后往前,可以考虑栈.如二叉树非递归,或者模拟递归都是后往前的例子
 * .
 */

//队列的使用场景
/**
 * 先进先出 的有序场景 时使用得多,如层序遍历
 * 
 */





