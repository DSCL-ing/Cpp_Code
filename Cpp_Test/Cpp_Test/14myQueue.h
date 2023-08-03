#pragma once

//note
/**
 * 
 * queue是尾插头删,尾进头出
 * 
 * queue不适合适配list,强行适配也是可以,但是效率很低.适配的话需要用erase进行头删
 * 
 * 
 * 
 * 
 */

#include<list>
#include<assert.h>
#include<deque>
#include<iostream>
using std::cout;
using std::endl;
using std::cin;
namespace test
{
	//template<class T, class Containers = std::list<T>>
	template<class T, class Containers = std::deque<T>
>
	class queue
	{
	private:
		Containers _con;
	public:
		void push(const T& x)
		{
			_con.push_back(x);//尾插
		}
		void pop()
		{
			_con.pop_front();//头删
		}
		const T& front()
		{
			return _con.front();
		}
		const T& back()
		{
			return _con.back();
		}
		bool empty()
		{
			return _con.empty();
		}
		size_t size()
		{
			return _con.size();
		}
		
	};

	void test_quque1()
	{
		queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		while (!q.empty())
		{
			std::cout << q.front() <<" ";
			q.pop();
		}
	}



}
