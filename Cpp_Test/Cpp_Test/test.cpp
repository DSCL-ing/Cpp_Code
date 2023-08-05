
#pragma once
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* treeToDoublyList(TreeNode* root) {
        return Convert(root);
    }
    void InOrderConvert(TreeNode* cur, TreeNode*& prev) {
        if (!cur)
            return;
        InOrderConvert(cur->left, prev);
        cur->left = prev;
        if (prev)
            prev->right = cur;
        prev = cur;
        InOrderConvert(cur->right, prev);
    }

    TreeNode* Convert(TreeNode* root) {
        if (!root)
            return nullptr;

        //第一个结点new一个或者为nullptr
        TreeNode* prev = nullptr;
        InOrderConvert(root, prev);
        TreeNode* head = root;

        while (head && head->left)
        {
            head = head->left;
        }
        return head;
    }
};

int main()
{
    int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
    TreeNode A(1);
    TreeNode B(2);
    TreeNode C(3);
    TreeNode D(4);
    TreeNode E(5);
    A.left = &B;
    A.right = &C;
    B.left = &D;
    C.right = &E;
    
    Solution s;
    //std::vector<vector<int>> vv = s.levelOrder(&A);
    s.treeToDoublyList(&A);




	return 0;
}
