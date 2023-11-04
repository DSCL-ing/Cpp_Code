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
	TreeNode* left;
	TreeNode* right;
	int data;
};
						
int TreeSize(TreeNode* root )											
{
	if (root == nullptr) return 0;
	if ((root->left == nullptr && root->right == nullptr)) return 1;
	return (TreeSize(root->left) + TreeSize(root->right));
	
}
				
int main()
{
	TreeNode* root;
	TreeSize(root);


	return 0;
}

 