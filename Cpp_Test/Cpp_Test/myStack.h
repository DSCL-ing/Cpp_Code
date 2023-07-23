
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
#include<vector>
#include<deque>
namespace test
{

	//template<class T, class Containers=std::vector<T>>
	template<class T, class Containers=std::deque<T>>
	class stack
	{
	private:
		Containers con;
	public:
		void push(const T& val)
		{
			con.push_back(val);//尾插尾删
		}
		void pop()
		{
			con.pop_back();
		}
		const T& top()
		{
			return con.back();
		}
		bool empty()
		{
			return con.empty();
		}

		size_t size()
		{
			return con.size();
		}





	};




	//测试用例
	//stack的使用
	void test_stack1()
	{
		stack<int> st1;
		st1.push(1);
		st1.push(2);
		st1.push(3);
		while (!st1.empty())
		{
			cout << st1.top() << endl;
			st1.pop();
		}
	}

	void test_stack2()
	{
		stack<int,std::list<int>> st;
		st.push(1);
		st.push(2);
		st.push(3);
		while (!st.empty())
		{
			cout << st.top()<<endl;
			st.pop();
		}
	}
}






