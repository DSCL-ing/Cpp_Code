#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>


//递归需要有记录,记住状态
//递归的终止条件

const int N = 16; //这是数组的空间数,比15大一位满足下标从1开始

int n;
int st[N];  //记录状态: 0表示还没考虑,1表示选了,2表示不选

void dfs(int u)
{
    if (u > n)
    {
        for (int i = 1; i <= n; i++)
            if (st[i] == 1)
                printf("%d ", i);  //从下标开始遍历,结果已经有序
        printf("\n");
        return;
    }

    //第一个分支
    st[u] = 2;//不选他X
    dfs(u + 1); //不能使用n++这种自增的,否则递归回来后n改变了 -- 递归回来应当是要恢复原来的状态(恢复现场)
    st[u] = 0; //(恢复现场)

    //第二个分支
    st[u] = 1;  //选他
    dfs(u + 1);
    st[u] = 0;
}

int main()
{
    std::cin>>n;
    dfs(1);

    return 0;
}