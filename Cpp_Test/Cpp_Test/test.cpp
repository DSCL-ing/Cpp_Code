
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
        TreeNode* front = root;
        vector<vector<int>> vv;
        if (!front)
        {
            return vv; //按题目要求,空结点需要返回没有空间的vv
        }
        queue<TreeNode*> q;
        q.push(front);
        int levelSize = 1;
        while (!q.empty())
        {
            vector<int> v;
            while (levelSize > 0)
            {
                --levelSize;
                 front = q.front();
                q.pop();
                v.push_back(front->val);
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            vv.push_back(v);
            levelSize = q.size();
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
