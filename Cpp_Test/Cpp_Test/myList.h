

//note
/**
 * List是个带头循环双向链表
 * 
 * begin是第一个元素的位置
 * end是最后一个元素的下一个位置,begin的前一个位置
 * 
 * 
 */

//clear不清头节点

#pragma once


namespace test
{
		//struct默认权限是public,一般也不会加权限,class才会(需要封装时使用class)
	template<class T>
	struct list_node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;

		//使用全缺省匿名对象(只要是模板,都得传对象,自定义类型接收的必须是实体对象)构造
		//list中使用是分配器分配空间,所以没写构造函数
		list_node(const T& x = T())//此处为方便,直接重写构造
			: _next(nullptr)
			, _prev(nullptr)
			,  data(x)
		{}


	};

	//这里声明的是list的迭代器,自己的
	//迭代器用于访问结点
	template<class T>
	struct __list_iterator
	{
		//成员类型
		typedef __list_iterator<T>* iterator;
		typedef list_node<T> node;
		//成员变量
		node* _node;

		//通过结点的指针来构造迭代器,模仿指针
		iterator(node* n)
			:_node(n)
		{}

		//指针操作运算符重载,模拟指针
		operator++()
		{
			_node
			return *this;
		}
		operator++(int)
		{

		}
		operator--()
		{

		}
		opratot--(int)
		{

		}
		operator!=()
		{

		}
		operator==()
		{

		}
		operator*()
		{

		}
		operator->()
		{

		}
	};

	template<class T>
	class list
	{
	public:
		typedef list_node<T> node;
		typedef __list_iterator<T> iterator;
	private:
		node* _head;
	public:
		//构造函数目前只写三个,1.无参,只创建头结点 2.迭代器构造 3.初始化n个结点 



		//只构造了一个头结点
		/*list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}*/

		//初始化多个结点
		list(size_t n = 0, const T& x = T())
		{
			empty_init();
		}

		//迭代器构造
		template <class InputIterator> //可以接收任意类型的迭代器,不只是自己的迭代器
		list(InputIterator first, InputIterator last)
		{
			empty_init();
		}

		void empty_init()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		//list操作这边和数据结构的带头双向循环链表差不多,重点是iterator.写操作前写将迭代器整出来


	};


}


