#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"Cpp_Demo.h"

#include"类.h"

using namespace std;

  

 inline void Swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}



 int main()
 {
	 Stack stack;
	 stack.Init();
	 stack.Init(1);
	 stack.Push(1);
	 cout << stack.a[0] << endl;
	 return 0;
 }

 ////C语言定义结构体
//typedef struct ListNode 
//{
   // int val;
   // struct ListNode* Node;//类型为struct ListNode
//}ListNode;
////C语言中typedef在此处后才起作用

////C++将结构体升级成了类
//struct ListNode
//{
   // int val;
   // ListNode* Node;		//类型为ListNode
//};

 //nullptr
 //void f(int)
 //{
	// cout << "int" << endl; 
 //}

 //void f(int*)
 //{
	// cout << "int *" << endl;
 //}

 //int main()
 //{
	// f(0);
	// f(NULL);
	// return 0;
 //}

 //auto
//inline void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}

/*int main() //5
{
	//auto a = 1, b = 2;
	//auto c = 3, d = 4.0;

	//int array[] = { 1,2,3,4,5,6 };
	//for (auto& x : array) //如果要影响原数组,可以使用引用
	//{
	//	x *= 2;
	//	cout << x << " ";
	//}
	//cout << endl;

	//int* a = 0;
	//auto b = &a;	//自动推导b为a类型
	//auto* c = &a;	//限定c为指针类型,只要是指针，不论二级三级指针
	//auto** d = &a;	//限定d为二级指针起步
	//auto& e = a;	//限定e为别名


	//int a = 1, b = 2;
	//auto c = &a;
	//auto d = b;
	//Swap(a,b);
	//cout << typeid(b).name() << endl;
	//cout << typeid(c).name() << endl;
	//cout << typeid(d).name() << endl;
	return 0;
}*/








	//ctrl是光标不动,往上插入一行
	//ctrl+shift(shift) 是往下插入一行,光标跟随

