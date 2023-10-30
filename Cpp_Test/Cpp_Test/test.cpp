#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

//#include <ctime>
//#include <random>
#include <iostream>
using std::cout;
using std::endl;
#include<string.h>
#include<algorithm>

struct TreeNode
{
	TreeNode* leff;
	TreeNode* right;
	int data;
};

int TreeSize(TreeNode* root )
{
	if (root != nullptr) return 1;
	return TreeSize(root->leff) + TreeSize(root->right) + 1;
}

int main()
{
	TreeNode* root;
	TreeSize(root);


	return 0;
}

 