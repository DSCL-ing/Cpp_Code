
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
        vv.push_back(vector<int>());
        if (!root)
        {
            return vv;
        }
        int levelNum = 0;
        queue<TreeNode*> q;
        q.push(root);
        int qSize = q.size();
        //int next_qSize = 0;
        while (!q.empty())
        {
            root = q.front();

            if (root)
            {
                //vv.push_back(vector<int>());
                vv[levelNum].push_back(root->val);
            }
            q.pop();
            --qSize;

            if (root->left)
            {
                q.push(root->left);
                //++next_qSize;
            }
            if (root->right)
            {
                q.push(root->right);
                //++next_qSize;
            }
            if (!qSize)
            {
                //vv.push_back(v);
                vv.push_back(vector<int>());
                ++levelNum;
                qSize = q.size();
            }
        }
        return vv;
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
    std::vector<vector<int>> vv = s.levelOrder(&A);

    auto it= vv.begin();
    while (it != vv.end())
    {
        auto iit = (*it).begin();
        while (iit != (*it).end())
        {
            cout << *iit << endl;
            ++iit;
        }
        ++it;
    }


	return 0;
}
