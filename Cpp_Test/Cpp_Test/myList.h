

//note
/**
 * List是个带头循环双向链表
 * 
 * begin是第一个元素的位置
 * end是最后一个元素的下一个位置,begin的前一个位置
 * 
 * 成员类型重命名现在先不带指针(stl带指针和不带指针),统一规范一下,可读性好点,容易理解
 */

//clear不清头节点

//list的使用
/**
 * 1.需要std展开
 * 2.定义list时需要带模板参数
 * 
 * 
 * .
 */

#pragma once


namespace test
{
	//struct默认权限是public,一般也不会加权限,class才会(需要封装时使用class)
	//结点使用struct的好处是开放结点,可以直接访问.不用重载流插入(stl也没重载),
	
	template<class T>
	struct list_node
	{
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;//

		//使用全缺省匿名对象(只要是模板,都得传对象,自定义类型接收的必须是实体对象)构造
		//list中使用是分配器分配空间,所以没写构造函数
		list_node(const T& x = T())//此处为方便不使用分配器,直接初始化个匿名对象
			: _next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{}


	};

	//这里声明的是list专用的迭代器 -- 实例化后能用于访问list
	//迭代器用于访问结点
	template<class T>
	struct __list_iterator
	{
		//成员类型
		typedef __list_iterator<T> self;
		typedef list_node<T> node;
		//成员变量
		node* _node; //成员变量只需要1个结点指针,通过这个结点指针的各种操作来模拟指针

		//通过结点的指针来构造迭代器,模仿指针
		__list_iterator(node* n)
			:_node(n)
		{}

		//不用写拷贝构造,直接值拷贝就行了,需要的就是值拷贝,指向同一个结点

		//指针操作运算符重载,模拟指针

		//解引用重载能够模拟指针返回的是结点的data,和string,vector迭代器一样
		T& operator*()
		{
			return _node->_data;
		}
		//箭头重载很难理解,编译器做了一定优化,后续再学习
		T* operator->()
		{
			return &(_node->date);
		}

		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//后置++返回的是一个拷贝,对原数据没有影响,安全
		self operator++(int)
		{
			self tmp = *this;//将原数据拷贝一份
			_node = _node->_next;
			return tmp;//返回拷贝
		}
		self& operator--()
		{
			_node = (*_node)._next;
			return *this;
		}
		self operator--(int)
		{
			self tmp = *this;
			_node = _node->_next;
			return tmp;
		}
		bool operator!=(const self& x)
		{
			return _node != x._node;
		}
		bool  operator==(const self& x)
		{
			return _node == x._node;
		}
	};

	template<class T>
	class list
	{
	public:
		typedef list_node<T> node;
		typedef __list_iterator<T> iterator;
		typedef const __list_iterator<T> const_iterator;
	private:
		node* _head;
	public:
		//构造函数目前只写三个,1.无参,只创建头结点 2.迭代器构造 3.初始化n个结点 (不想写)

		//只构造了一个头结点
		list()
		{
			empty_init();
		}

//全缺省多个结点构造
		list(size_t n , const T& x = T())
		{
			empty_init();//建一个头结点
			//...
		}
		list(int n , const T& x = T())
		{
			empty_init();//建一个头结点
			//...
			while (n)
			{
				push_back(x);
				--n;
			}
		}

//迭代器构造
		template <class InputIterator> //可以接收任意类型的迭代器,不只是自己的迭代器
		list(InputIterator first, InputIterator last)
		{
			empty_init();//建一个头结点
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		void swap(list<T>& tmp)
		{
			std::swap(_head, tmp._head);
		}
//拷贝构造
		list(const list<T>& lt)
		{
			cout << "list(const list<T>& lt)"<<endl;
			empty_init();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}
		
		list<T>& operator=(list<T> lt) 
		//赋值运算符重载：操作数是list<list<>>,在非初始化时(初始化时时拷贝构造)走这里
		//传值传参，v是拷贝，所以是再次调了拷贝构造,新空间了,所以相当于深拷贝
		//走拷贝构造会调用=重载.
		{
			cout << "list<T>& operator=(list<T> lt)"<<endl;
			swap(lt);
			return *this;
		}

		void empty_init()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		~list()
		{
			cout << "~list()"<<endl;
			clear();
			delete _head;
			_head = nullptr;
		}
		//clear:保留头结点,其他全部清空
		void clear()
		{
			iterator it = begin(); //begin用于初始化it,调用默认生成的值拷贝拷贝构造
			while (it!=end())
			{
				erase(it++);
			}
		}


		//iterator
		//返回迭代器,目的是按规范通过迭代器访问结点
		//虽然迭代器不是原生指针,但是list迭代器重载了解引用运算符*,可以和指针一样解引用就能得到数据
		iterator begin()
		{
			//不能直接返回链表头结点的下一个的指针,因为链表的存储空间不连续,不能对指针直接加加减减,所以需要迭代器
			
			//需要实例化迭代器后才能使用迭代
			//iterator it(_head->_next);
			//return it;
			
			//可以使用C++提供的匿名对象来简化代码
			return iterator(_head->_next);
		}
		const_iterator begin() const
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			//返回链表头结点的迭代器
			return iterator(_head->_next);
		}
		const_iterator end()const
		{
			return iterator(_head->_next);
		}


		//list操作这边和数据结构的带头双向循环链表差不多,重点是iterator.写操作前写将迭代器整出来

		//Capacity
		//size实现需要迭代器计算链表长度会用就行


		//modifiers
		//插入
		//这里的传进来的迭代器是list的迭代器
		void insert(iterator pos , const T& x ) //insert没有迭代器失效问题,pos依然指向同一个结点
		{
			node* n = new node(x); //深拷贝赋值运算符重载处
			node* cur = pos._node;
			node* prev = cur->_prev;
			n->_prev = prev;
			prev->_next = n;
			n->_next = cur;
			cur->_prev = n;
		}
		//删除
		iterator erase(iterator pos) //迭代器失效(野指针),返回链表下一个位置的迭代器
		{
			node* prev = pos._node->_prev;
			node* next = pos._node->_next;

			prev->_next = next;
			next->_prev = prev;
			delete pos._node;
			return iterator(next);
		}
		//尾插
		void push_back(const T& x) //插入必须有具体值,库中也没有
		{
			node* n = new node(x);
			node* tail = _head->_prev;
			n->_prev = tail;
			tail->_next = n;
			n->_next = _head;
			_head->_prev = n;
		}
		//头插
		void push_front(const T& x)
		{
			node* n = new node(x);
			
			n->_next = _head->_next;
			_head->_next->_prev = n;
			n->_prev = _head;
			_head->_next = n;
		}
		//头删
		void pop_front()
		{
			node* cur = _head->_next ; //记录要删除的当前结点
			cur->_next->_prev = _head;
			_head->_next = cur->_next;
			delete cur;
		}
		//尾删
		void pop_back()
		{
			node* cur = _head->_prev;
			cur->_prev->_next = _head;
			_head->_prev = cur->_prev;
			delete cur;
		}

	};

	void test_list()
	{

		//using namespace std;
		list<list<int>> lt1;
		lt1.push_back(list<int>(1));
		lt1.push_front(list<int>(1));
		list<list<int>>::iterator it = lt1.begin();
		lt1.insert(it, list<int>(2));
		lt1.erase(it);
		list<list<int>> lt2(lt1);
		//lt2.push_back(list<int>(2));
		//lt2.push_back(list<int>(2));
		//lt2.push_back(list<int>(2));
		//lt2.pop_back();
		//lt2.pop_front();


		//list<int> lt1(1,1);
		//lt1.push_back(2);
		//list<int>::iterator it = lt1.begin();
		//cout << *it;

	}
}




