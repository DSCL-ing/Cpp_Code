#define  _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"Cpp_Test.h"

#include"��.h"

using namespace std;


int main()
{
	//���ù��캯��
	Stack st;		//������д��.������������һ��,���췽��������������֮ͬ��
	//Stack st();		//�ᾯ��,������ôд
	Stack st1(4);	//����д��

	return 0;
}

// inline void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//
// class Date
// {
// public:
//	 void Init(int year, int month, int day)
//	 {
//		 _year = year;
//		 _month = month;
//		 _day = day;
//		 cout << this << endl;
//	 }
// private:
//	 int _year; // ��
//	 int _month; // ��
//	 int _day; // ��
// };
//
// int main()
// {
//	 Date d1, d2;
//	 d1.Init(2022, 1, 11);
//	 d2.Init(2022, 1, 12);
//
//	 return 0;
// }

 //// ���м��г�Ա���������г�Ա����
 //class A1 {
 //public:
	// void f1() {}
 //private:
	// int _a;
 //};
 //// ���н��г�Ա����
 //class A2 {
 //public:
	// void f2() {}
 //};
 //// ����ʲô��û��---����
 //class A3
 //{};
 //int main()
 //{
	// cout << sizeof(A1) << endl; //4
	// cout << sizeof(A2) << endl; //1
	// cout << sizeof(A3) << endl; //1
	// return 0;
 //}

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

