#pragma once


//适配器 - priority_queue
/**
 * #include<queue>
 *
 * 底层是vector的堆,完全二叉树,大堆,大的优先级高(top返回最大的)
 *
 *
 * 使用
 * #include<functional> //仿函数或函数对象 
 * priority_queue<int,vector<int>,greator<int>> pq; //设计不太合理
 * 
 * 
 *
 */

//仿函数
/**
 * 功能:
 * 1.用于在有比较的场景下,翻转比较对象 
 * 如,升序逆序,大小比较
 * 
 * 特点:
 * 1.支持基本类型
 * 2.支持自定义类型(需要重载 '<' 和 '>' )
 * 3.//允许用户写仿函数来控制
 * 
 */

#include<deque> //测试用
#include<vector>//测试用
#include"Date.h"//测试用
namespace test
{

template <class T >
struct less
{
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};

template<class T>
struct greater
{
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};

template<class T, class Containers = std::vector<T>, class Compare = less<T> >
class priority_queue
{
private:
	Containers _con;
	Compare _com;//或者换成匿名对象,感觉更爽
public:
	void adjust_up(int child)
	{
		/**
 * 向上调整算法(大堆)
 * 计算父亲下标
 * 如果孩子大于父亲,交换孩子和父亲,计算新父亲下标
 * 如果孩子小于父亲,结束循环
 * 相等换不换都行
 *
 *
 */

		/**
		 * 计算堆的parent方法：
		 * 写一个有序值为下标的数组小堆，0-4五个数刚好，计算3和4通过什么方法得到1
		 * 
		 * 			0
		 *       1      2
		 *     3   4 
		 * 
		 * (4-1)/2 = 3/2 = 1
		 * 4/2 - 1 = 2-1 = 1
		 * (3-1)/2 = 2/2 = 1
		 * 3/2 - 1 = 1-1 = 0;
		 * 所以parent = (child-1)/2
		 */

		int parent = (child - 1) / 2;
		while (child > 0) //child为0就不用再换了
		{
			if (_com(_con[parent] ,_con[child])) 
			//if (Compare()(_con[parent] ,_con[child])) 
			{
				swap(_con[parent], _con[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}

	}
	void push(const T& x)
	{
		_con.push_back(x);
		adjust_up(_con.size()-1);
	}
	void adjust_down(int parent)
	{

		/**
 * 向下调整算法(大堆):
 * 计算孩子下标
 * 计算最大的孩子
 * 比较孩子和父亲
 * 如果父亲小于最大孩子,交换父亲和孩子,计算新孩子
 * 如果父亲大于于最大孩子,结束循环
 * 相等换不换都行
 *
 * 循环条件:左孩子下标不能超过数组大小
 *
 *
 */

		/**
		 * 计算堆的child方法
		 * 写一个有序值为下标的数组小堆，0-4五个数刚好，计算
		 * 			0
		 *       1      2
		 *     3   4 
		 * 0*2+1 = 0+1 = 1 left
		 * 0*2+2 = 0+2 = 2 right
		 * 1*2+1 = 2+1 = 3 left
		 * 1*2+2 = 2+2 = 4 right
		 * 所以  left child = parent*2 + 1;
		 * 所以 right child = parent*2 + 2;
		 * 实际 right_child = left_child+1
		 */

		//方法一
		/*
		int left_child = parent * 2 + 1;
		//int right_child = parent * 2 + 2;
		int right_child = left_chile + 1;
		int min_child = left_child;

		while (left_child < _con.size() )  
		//不能限制右孩子,在没有右孩子,但有左孩子更小的情况,parent需要和左孩子交换,如果右孩子限制了,那可能会丢失一个左孩子
		{
			if (right_child < _con.size() && left_child > right_child)
			{
				min_child = right_child;
			}
			if (_con[parent] < _con[child])
			{
				swap(_con[parent], _con[min_child]);
				left_child = parent * 2 + 1;
				//right_child = parent * 2 + 2;
				right_child = left_child + 1;
				min_child = left_child;
			}
			else
			{
				break;
			}	
		}
		*/
		///优化方案
		size_t child = parent * 2 + 1;
		while (child < _con.size())
		{
			//if ((child + 1 )< _con.size() && _con[child]<_con[child + 1] )
			if ((child + 1 )< _con.size() && _com(_con[child],_con[child + 1]) )
			{
				child = child + 1;
			}
			if (_com(_con[parent] , _con[child]))
			{
				swap(_con[parent], _con[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}



	}
	void pop()
	{
		swap(_con[0], _con[_con.size() - 1]);
		_con.pop_back();
		adjust_down(0);
	}
	const T& top()
	{
		return _con[0];
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

//测试用例

void test_priority_queue1()
{
	priority_queue<int , std::deque<int>,greater<int>> pq;
	//priority_queue<int> pq;
	pq.push(2);
	pq.push(4);
	pq.push(1);
	pq.push(3);
	pq.push(6);
	pq.push(5);

	while (!pq.empty())
	{
		cout << pq.top() << endl;
		pq.pop();
	}
}

//struct DateLess //这个不需要重载,我们在上方写了模板,参数T可以支持了
//{
//	bool operator()(const Date& x, const Date& y)
//	{
//		return x < y;
//	}
//};
struct PDateLess
{
	bool operator()(const Date* p1, const Date* p2)
	{
		return (*p1) < (*p2);
	}
};
void test_priority_queue2()
{
	//priority_queue<Date> pq1;
	//pq1.push(Date(2001, 1, 1));
	//pq1.push(Date(2001, 1, 2));
	//pq1.push(Date(2001, 1, 3));
	//cout << pq1.top() << endl;
	cout << "=================" << endl;
	priority_queue<Date*,vector<Date*>,PDateLess> pq2; //显式指定才会调用PDateLess,不然会调用模板的用于比较地址
	pq2.push(new Date(2001, 1, 1));
	pq2.push(new Date(2001, 1, 2));
	pq2.push(new Date(2001, 1, 3));
	cout << *(pq2.top()) << endl;
}



}