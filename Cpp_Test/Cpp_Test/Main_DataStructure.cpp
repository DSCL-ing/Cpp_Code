#pragma once




#include<iostream>
#include<set>
using std::cout;
using std::endl;
using std::cin;
using std::set;
#include"25RBTree.h"
#include"24AVLTree.h" //性能比较测试 -- 高度
int main()
{
	//test::test_RBTree1();
	test::test_RBTree2();
	test::test_AVL2();  //性能比较测试 -- 高度

	return 0;
}




//#include"22BST.h"
//int main1()
//{
//	//key::test_BST1();
//	//key::test_BST2();
//	//key::test_BST3();
//	//key_value::test_BST1();
//	key_value::test_BST2();
//	return 0;
//}