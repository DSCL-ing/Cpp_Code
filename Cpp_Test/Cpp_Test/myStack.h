
//note
/**
 * 
 * 
 * 栈不是容器,栈是一个容器适配器 
 * 容器适配器: containers adaptors
 * 
 * 特点:
 * 1.栈没有迭代器(不能保证后进先出)
 * 
 * 
 * 
 * .
 */


#pragma once


#include<assert.h>

namespace test
{








	//测试用例

#include<stack>
	//stack的使用
	void tese_stack1()
	{
		std::stack<int> st1;
		st1.push(1);
		st1.push(2);
		st1.push(3);
		while (!st1.empty())
		{
			cout << st1.top() << endl;
			st1.pop();
		}
	}

}


