#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"Cpp_Demo.h"

#include"��.h"

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

 ////C���Զ���ṹ��
//typedef struct ListNode 
//{
   // int val;
   // struct ListNode* Node;//����Ϊstruct ListNode
//}ListNode;
////C������typedef�ڴ˴����������

////C++���ṹ������������
//struct ListNode
//{
   // int val;
   // ListNode* Node;		//����ΪListNode
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
	//for (auto& x : array) //���ҪӰ��ԭ����,����ʹ������
	//{
	//	x *= 2;
	//	cout << x << " ";
	//}
	//cout << endl;

	//int* a = 0;
	//auto b = &a;	//�Զ��Ƶ�bΪa����
	//auto* c = &a;	//�޶�cΪָ������,ֻҪ��ָ�룬���۶�������ָ��
	//auto** d = &a;	//�޶�dΪ����ָ����
	//auto& e = a;	//�޶�eΪ����


	//int a = 1, b = 2;
	//auto c = &a;
	//auto d = b;
	//Swap(a,b);
	//cout << typeid(b).name() << endl;
	//cout << typeid(c).name() << endl;
	//cout << typeid(d).name() << endl;
	return 0;
}*/








	//ctrl�ǹ�겻��,���ϲ���һ��
	//ctrl+shift(shift) �����²���һ��,������

