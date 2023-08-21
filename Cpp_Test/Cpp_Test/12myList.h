

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
#include"16my_Itetator.h" //测试用
#include<iostream> //测试用
using std::cout;
using std::endl;
using std::cin;
namespace test
{
	//struct默认权限是public,一般也不会加权限,class才会(需要封装时使用class)
	//结点使用struct的好处是开放结点,可以直接访问.不用重载流插入(stl也没重载),
	
	template<class T>
	struct list_node
	{
		//一个完整的结点,包含前,后,和自己
		list_node<T>* _next;
		list_node<T>* _prev;
		T _data;//

		//使用全缺省匿名对象(只要是模板,都得传对象,自定义类型接收的必须是实体对象)构造
		//list中使用是分配器分配空间,所以没写构造函数
		list_node(const T& x = T())//此处为方便不使用分配器,直接初始化个匿名对象
			: _next(nullptr)
			, _prev(nullptr)
			, _data(x)
		{
			cout << "newnode" << endl;
		}

		//拷贝原理 
		
		/**
		 * 
		 *  list<int> lt(1) 初始化过程：
		 * 	先走拷贝构造，
		 * 	走init建一个头结点
		 * 	然后insert, insert中会建一个新结点, 值为1, 完成插入
		 * 
		 * 	list<list<int>> lt1 初始化过程
		 * 	走默认构造, 空初始化一个list<T>头结点的过程(newnode之前), 再走默认构造, 建一个list<int>结点的匿名对象, 走的是拷贝构造(匿名对象传给x),
		 *  将匿名对象拷贝进去.析构匿名对象, list<list<int>>默认构造完成
		 * 
		 * 	list<list<int>> lt2(lt1) 初始化过程
		 * 	走拷贝构造, empty(就是头结点过程), ... 和lt1初始化过程一样
		 * 	建一个临时变量(接收迭代器构造的list)走迭代器构造, empty(建一个lt1的头结点), push_back
		 * 	交换头和临时头的内容, 完成拷贝构造
		 * 
		 * 	在第一层迭代器构造中, 将lt1插进的过程有两层拷贝构造
		 * 	第一层拷贝构造 -- x == lt1
		 * 	push过程newnode(x == lt)->第二层拷贝构造:--通过初始化列表走的 解决问题
		 * 
		 * 	综合发现 : 多重结点类只需要完成第一层深拷贝, 即可完成多层深拷贝
		 * 	因为每次都会new新结点, 且初始化列表赋值过程不是值拷贝, 而是会调用类类型的构造函数
		 */



	};

	//这里声明的是list专用的迭代器 -- 实例化后能用于访问list
	//迭代器用于访问结点
	template<class T, class Ref, class Ptr>//Ref会接收参数
	struct __list_iterator
	{
		//成员类型
		typedef list_node<T> node;
		typedef __list_iterator<T,Ref,Ptr> self; //只管接收


		//成员变量
		node* _node; //成员变量只需要1个结点指针,通过这个结点指针的各种操作来模拟指针

		//通过结点的指针来构造迭代器,模仿指针
		__list_iterator(node* n)
			:_node(n)
		{}
		//不用写拷贝构造,直接值拷贝就行了,需要的就是值拷贝,指向同一个结点

		//list迭代器不用写析构函数,因为迭代器接收的是list结点,由list负责即可


		//指针操作运算符重载,模拟指针

		//解引用重载能够模拟指针返回的是结点的data,和string,vector迭代器一样
		//
		/**
		 * 模拟指针的方法
		 * 我们对list的迭代器来说,
		 * 为了符合习惯的指针用法
		 * 对于结构体,实体可以通过成员访问修饰符去访问成员
		 * 
		 * 设struct AA{_a1,_a2};如AA._a1 , (&AA)->_a1
		 * list<AA> iterator it = lt.begin();要想list<AA>能实现通过list迭代器实现上述功能,我们对迭代器运算符进行重载
		 * 由于我们迭代器模拟的是元素的指针,list中的元素是AA,所以让it模拟成AA的指针:&AA
		 * 我们希望迭代器能做到和基本类型一样有(*it)._a1 ,it->_a1;
		 * 所以,我们将迭代器重载为
		 * *it  返回 AA   //然后it便可以实现(*it)._a1;
		 * it-> 返回 &AA  //目的是it可以实现it->_a1 ，实际上要访问_a1的过程是it->->_a1,但这样并不协调,为了可读性,所以编译器会将其优化成为it->_a1;
		 * 
		 * 可以发现,要实现it->并不容易,it毕竟是个结构体,这么实现是个很好的思路
		 * 
		 * 运算符重载的其中一个目的是可读性要强
		 * 
		 */

		Ref operator*()
		{
			return _node->_data;
		}
		//箭头重载很难理解,编译器做了一定优化,后续再学习
		//这个重载是会有编译器优化的

		Ptr operator->()
		{
			return &(_node->_data);
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
			_node = (*_node)._prev;
			return *this;
		}
		self operator--(int)
		{
			self tmp = *this;
			_node = _node->_prev;
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

//list_const_iterator : const迭代器需要另写一个类 -- 优化:增加模板参数
	//template<class T>
	//struct __list_const_iterator
	//{
	//	typedef list_node<T> node;
	//	typedef __list_const_iterator<T> self;
	//	node* _node; 
	//	__list_const_iterator(node* n)
	//		:_node(n)
	//	{}

	//	const T& operator*()
	//	{
	//		return _node->_data;
	//	}
	//	const T* operator->()
	//	{
	//		return &(_node->date);
	//	}

	//	self& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}
	//	self operator++(int)
	//	{
	//		self tmp = *this;
	//		_node = _node->_next;
	//		return tmp;
	//	}
	//	self& operator--()
	//	{
	//		_node = (*_node)._next;
	//		return *this;
	//	}
	//	self operator--(int)
	//	{
	//		self tmp = *this;
	//		_node = _node->_next;
	//		return tmp;
	//	}
	//	bool operator!=(const self& x) 
	//	{
	//		return _node != x._node;
	//	}
	//	bool  operator==(const self& x)
	//	{
	//		return _node == x._node;
	//	}
	//};



	template<class T>
	class list
	{
	private:
		typedef list_node<T> node;
	public:
		//正向迭代器类型重命名
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,const T&,const T*> const_iterator; 

		//反向迭代器类型重命名
		typedef ReverseIterator<iterator, T&, T*> reverse_iterator;
		typedef ReverseIterator<iterator, const T&, const T*> const_reverse_iterator;
//tese
//static int Swap;
//static int destruct;
//static int itstruct;
//static int cpstruct;

		//iterator
//返回迭代器,目的是按规范通过迭代器访问结点
//虽然迭代器不是原生指针,但是list迭代器重载了解引用运算符*,可以和指针一样解引用就能得到数据
		iterator begin()
		{
			//不能直接返回链表头结点的下一个的指针,因为链表的存储空间不连续,不能对指针直接加加减减,所以需要迭代器

			
			//需要实例化迭代器后才能使用迭代器
			//iterator it(_head->_next);
			//return it;

			//可以使用C++提供的匿名对象来简化代码
			return iterator(_head->_next);//正向迭代器类接收链表指针构造出正向迭代器实体
		}
		const_iterator begin() const //const修饰的*this,也就是链表,所以链表不能修改
		{
			return const_iterator(_head->_next);
		}
		iterator end()
		{
			//返回链表头结点的迭代器
			return iterator(_head);
		}
		const_iterator end()const
		{
			return const_iterator(_head);
		}

		//反向迭代器
		reverse_iterator rbegin() //
		{
			return reverse_iterator(end());//返回反向迭代器(适配器)接收正向迭代器的对象构造出反向迭代器
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() 
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		//list操作这边和数据结构的带头双向循环链表差不多,重点是iterator.写操作前写将迭代器整出来
	private:
		node* _head;//链表的操作就是从一个头开始,所以链表的成员就一个头指针
	public:
		//构造函数目前只写三个,1.无参,只创建头结点 2.迭代器构造 3.初始化n个结点 (不想写)

		//只构造了一个头结点
		list()
		{
			//cout << "list(" << this <<")" << endl;
			empty_init();
		}
		list(const T& x)
		{
			empty_init();
			push_back(x);
		}
		//list(const T& x)
		//{
		//	empty_init();//建一个头结点
		//	//...
		//		push_back(x);
		//}

//全缺省多个结点构造
		//list(size_t n , const T& x = T())
		//{
		//	cout << "list(size_t n , const T& x = T(" << this << ")))" << endl;
		//	empty_init();//建一个头结点
		//	//...
		//	while (n)
		//	{
		//		push_back(x);
		//		--n;
		//	}
		//}
		//list(int n , const T& x = T())
		//{
		//	cout << "list(int n , const T& x = T(" << this << ")))" << endl;
		//	empty_init();//建一个头结点
		//	//...
		//	while (n)
		//	{
		//		push_back(x);
		//		--n;
		//	}
		//}

//迭代器构造
		//深拷贝核心:只要进迭代器,就可以深拷贝
		template <class InputIterator> //可以接收任意类型的迭代器,不只是自己的迭代器
		list(InputIterator first, InputIterator last)
		{
			//cout << "list(InputIterator first, InputIterator last) " << this << ")" << endl;
			empty_init();//建一个头结点
			while (first != last)
			{
				push_back(*first);//"new"一个结点,拷x进来,++first,再new一个结点,拷x进来,通过这样实现了深拷贝,new关键字容易忽略,就是malloc
				++first;
			}
		}
		void swap(list<T>& tmp)
		{
			//cout << "list(InputIterator first, InputIterator last)" << this << ")" << endl;
			std::swap(_head, tmp._head);
		}
//拷贝构造
		list(const list<T>& lt)
		{
			//深拷贝时,第一次拷贝构造是list<list<int>>,因为构造一个匿名对象,此时x是list<int> , 第二次是list<int>,拷贝构造给此时
			cout << "list(const list<T>& lt)" << this << ")"<<endl;
			empty_init();
			list<T> tmp(lt.begin(), lt.end()); //深拷贝
			swap(tmp);
		}
		
		//此处不是深拷贝核心
		list<T>& operator=(list<T> lt) //:传值传参->拷贝构造+迭代器构造,深拷贝
		//赋值运算符重载：操作数是list<list<>>,在非初始化时走这里,lt1 = lt2
		//使用到的场景，直接赋值给另一个对象：lt1 = lt2 :
		{
			//cout << "operator="<<endl;
			swap(lt);
			return *this;
		}

		void empty_init()
		{
			//cout << "empty_init()" << this << ")" << endl;
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		~list()
		{
			//cout << "~list()" << this << ")"<<endl;
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
				//it = erase(it);
				erase(it++);
			}
		}



		//Capacity
		//size实现需要迭代器计算链表长度会用就行


		//modifiers
		//插入
		//这里的传进来的迭代器是list的迭代器
		void insert(iterator pos , const T& x ) //insert没有迭代器失效问题,pos依然指向同一个结点
		{
			//cout << "insert" << *this << ")" << endl;
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* new_node = new node(x);  //new阿！！！！！！！！！！！！！！！！！new是开辟新结点，然后再把x赋值进去--直接实现了深拷贝6666

			prev->_next = new_node;
			new_node->_prev = prev;
			new_node->_next = cur;
			cur->_prev = new_node;
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
		void push_back(const T& x) //插入必须有具体值,总不能插入一个匿名对象
		{
			//cout << "push_back" << this << ")" << endl;
			//node* n = new node(x);
			//node* tail = _head->_prev;
			//n->_prev = tail;
			//tail->_next = n;
			//n->_next = _head;
			//_head->_prev = n;
			insert(end(), x);
		}
		//头插
		void push_front(const T& x)
		{
			//node* n = new node(x);
			//
			//n->_next = _head->_next;
			//_head->_next->_prev = n;
			//n->_prev = _head;
			//_head->_next = n;
			insert(begin(), x);
		}
		//头删
		void pop_front()
		{
			//node* cur = _head->_next ; //记录要删除的当前结点
			//cur->_next->_prev = _head;
			//_head->_next = cur->_next;
			//delete cur;
			erase(begin());
		}
		//尾删
		void pop_back()
		{
			//node* cur = _head->_prev;
			//cur->_prev->_next = _head;
			//_head->_prev = cur->_prev;
			//delete cur;
			erase(--end());
		}

	};
	//std::ostream& operator<<(std::ostream& out ,list<> )
	//{

	//}



	//测试用例


	//深拷贝验证
	void test_list1()
	{
		//using namespace std;
		list<int> lt(1);
		lt.push_back(2);
		//lt.push_back(3);
		//lt.push_back(4);
		//for (auto x : lt)
		//{
		//	cout << x << endl;
		//}
		//list<int>::iterator it = lt.begin();
		//while (it != lt.end())
		//{
		//	cout << *it << endl;
		//	++it;
		//}
		list<list<int>> lt1;
		lt1.push_back(lt);
		//lt1.push_back(list<int>(1,1));
		//lt1.push_front(list<int>(1));
		//list<list<int>>::iterator it = lt1.begin();
		//lt1.insert(it, list<int>(2));
		//lt1.erase(it);
		//list<list<int>> lt2(lt1);
		//list<list<int>> lt2 = lt1;
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

	//迭代器const 运算符重载 
	void print_list(const list<int>& lt)
	{

		list<int>::const_iterator it = lt.begin();
		while (it != lt.end())
		{
			//++(*cit);

			std::cout << *it << std::endl;
			++it;
		}
	}
	void test_list2()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		print_list(lt);
	}


	//迭代器运算符*,->重载,多模板参数
	struct AA
	{
		int _a1;
		int _a2;

		AA(int a1 = 0, int a2 = 0)
			:_a1(a1)
			, _a2(a2)
		{}
	};
	void test_list3()
	{
		list<AA> lt;
		lt.push_back(AA(1, 1));
		lt.push_back(AA(2, 2));
		lt.push_back(AA(3, 3));

		// AA* ptr
		list<AA>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//cout << (*it)._a1 << ":" << (*it)._a2 << endl;		
			std::cout << it->_a1 << ":" << it->_a2 << std::endl;
			//cout << it.operator->()->_a1 << ":" << it.operator->()->_a1 << endl;
			++it;
		}
		std::cout << std::endl;
	}

	void test_list4()
	{
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		//list<int>::iterator it = lt1.begin();
		//while (it != lt1.end())
		//{
		//	cout << *it << " ";
		//	++it;
		//}
		cout << endl<< "=============" << endl;
		list<int>::reverse_iterator rit = lt1.rbegin();
		while (rit != lt1.rend())
		{
			cout << *rit << " ";
			++rit;
		}

	}
	
}




