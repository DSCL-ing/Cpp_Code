
#include"��.h"
#include"Date.h"

int main()
{
	
	Date d1(2023,5,24);		 
	Date d2;				 
	Date d3;

	//��֤��=���͡�d+=100��
	d2 = d1 += 2000;		 
	d1.print();				 //2028/11/13
	d2.print();				 //2028/11/13
							 
	d1.Init();				 
	d2.Init();				 
						
	//��֤d+100 
	d3 = d2 + 2000;			 
	d2.print();				 //1/1/1
	d3.print();				 //6/6/24
				
	//��֤ǰ����++
	(++d1).print();			 //1/1/2
	(d2++).print();			 //1/1/1
	d2.print();				 //1/1/2
			
	d1.Init();				 
	d2.Init();				 
	
	//��֤ d -=	100			 				 
	(d1-=1).print();		 //0/12/31
	d1.print();				 //0/12/31		 
	d3.Init(2023, 5, 24);	 
	(d3 -= 2000).print();	 //2017/12/1

	d1.Init();
	d2.Init();

	//��֤ d - 100
	d2 = d1 - 1;
	d1.print();				 //1/1/1
	d2.print();				 //0/12/31
	
	d1.Init(2023,5,24);
	d2.Init(2000,6,25);
	//(d1 -= d2).print();
	

	return 0;
}


//��ֵ���������
//int main()
//{
//	Date d1;
//	Date d2(1, 1, 2);
//	Date d3(3, 3, 3);
//	cout << d1.operator<(d2) << endl;
//	d1 = d2 = d3;
//	d1.print();
//	d2.print();
//	d3.print();
//	return 0;
//}


//���������1
//bool operator==(const Date& d1, const Date& d2)
//{
//	return d1._day == d2._day &&
//		d1._month == d2._month &&
//		d1._year == d2._year;
//}
//
//int main()
//{
//	Date d1;
//	Date d2(1,1,1);
//	cout << operator==(d1, d2) << endl;
//	cout << (d1 == d2) << endl;
//	return 0;
//}



//int main()
//{
//
//	//���ù��캯��
//	Stack st;		//������д��.������������һ��,���췽��������������֮ͬ��
//	//Stack st();		//�ᾯ��,������ôд
//	//Stack st1(4);	//����д��
//
//	return 0;
//}

// inline void Swap(int& a, int& b)
//{
//	int tmp = a;
//	a = b;
//	b = tmp;
//}
//

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

