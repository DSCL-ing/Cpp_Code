#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<stack>

#if 1
const int N = 20;       //要跑20圈
int size = 0;           //方案数

void Print(const std::vector<int>& v) {
    for (int i = 1 ; i<v.size();i++) {
        if (v[i] == 1) std::cout << i << " " ;
    }
    std::cout<<std::endl;
}

//dfs(下一次待跑圈数,已跑圈数)
void dfs(int cnt, int ans, std::vector<int>& v) {
    if (ans + cnt  > 20)     //
    {
        return ;
    }
    if (ans + cnt == 20) 
    {
        v[cnt] = 1;
        Print(v);
        v[cnt] = 0; //回溯
        size++;
        return ;
    }

    v[cnt] = 1; //可以跑
    for (int i = cnt+1; i < N-ans; i++)      
    /*
     i<N-ans,规律
     (more) (next)
      1  --  19    1,2 -- 17      1,2,3 -- 14  即 ans(已跑圈数) <--> N-ans(要跑圈数)
      2  --  18 
      3  --  17
      ...
    */
    {
        dfs(i, ans+cnt, v); //下一次执行(待跑圈数,已跑圈数);
    }
    v[cnt] = 0; //回溯
}

int main() {
    std::vector<int> v;
    v.resize(21, 0);

    //第一步的圈数,范围1到20圈
    for (int i = 1; i <= N; i++) {
        dfs(i, 0, v);
    }
    std::cout<<"总方案数: "<<size << std::endl;
    return 0;
}

//using namespace std;
//
//// 用于存储所有方案
//vector<vector<int>> vv;
//
//// 暴力递归生成所有分配方案
//void solution(int n, vector<int>& v) {
//    if (n == 0) {
//        // 如果圈数已经跑完，则检查是否满足递增条件
//        bool flag = true;
//        for (int i = 1; i < v.size(); ++i) {
//            if (v[i] <= v[i - 1]) {
//                flag = false;
//                break;
//            }
//        }
//        // 如果满足条件，保存该方案
//        if (flag) {
//            vv.push_back(v);
//        }
//        return;
//    }
//
//    // 遍历剩余圈数，生成所有可能的圈数组合
//    for (int i = 1; i <= n; ++i) {
//        v.push_back(i);  // 添加当前跑的圈数
//        solution(n - i, v);  // 递归处理剩余的圈数
//        v.pop_back();  // 移除当前圈数
//    }
//}
//
//int main() {
//    const int N = 20;  // 总圈数
//    vector<int> v;
//
//    // 生成所有跑完 20 圈的暴力方案
//    solution(N, v);
//
//    // 输出总方案数
//    cout << "总方案数: " << vv.size() << endl;
//
//    // 输出每种方案
//    for (const auto& e : vv) {
//        for (size_t i = 0; i < e.size(); ++i) {
//            cout << e[i] << (i == e.size() - 1 ? "" : ",");
//        }
//        cout << endl;
//    }
//    return 0;
//}



#elif 0
#include <cstring>
#include <iostream>
#include <thread>

class my_string {
public:
    using Self = my_string;

    // 左值 带参构造函数
    my_string(const char* str = "")
        : _size(strlen(str)),  // 依据_size的大小是0还是非0,决定如何分空间
        _capacity(0),
        _str(nullptr) {
        if (_size == 0) {
            _capacity =
                3;  // msvc缺省值是15,不过我们这个用来学习的,小一点可以测试结果
        }
        else {
            _capacity = _size;
        }

        _str = new char[_capacity];
        strcpy(_str, str);
    }

    ~my_string() {
        _size = 0;
        _capacity = 0;
        delete[] _str;
    }

    void Swap(my_string& str) {
        std::swap(str._size, _size);
        std::swap(str._capacity, _capacity);
        std::swap(str._str, _str);
    }

    my_string(const my_string& str) {
        my_string tmp(str._str);
        Swap(tmp);
    }

    Self& operator=(my_string str) { Swap(str); }

    char* _str;
    size_t _capacity;  // 总容量
    size_t _size;      // 有效字符串长度
};

int main() {
    return 0;
}
#endif
