#pragma once



//���캯��
/**
 * 1.string();  //�޲ι���
 * 2.string(const string& str);//��������
 * 3.string(const string& str,size_t pos,size_t len = npos); //	�Ӵ���������
 *	 ע��:posΪ��ʼλ��(��0��ʼ),nposΪ�λ��,�������ʵ��λ��,��ȡ���,nposĬ��Ϊ�޷���-1,������int 
 * 4.string(const char* s);//�ַ�����������
 * 5.string(const char* s ,size_t n);//���ַ���������ǰn�����й���
 * 6.string(size_t n , char c);//��n��һ�����ַ����й���
 * 7.������...
 */

//����
/**
 * string s1("hello");
 * string s2 = "hello";//��ʽ����ת��:����+�������� = ����//(const char*)ת��string
 * .
 */


//���������
/**
 * ��ֵ���������:3��
 * 
 * ���������������
 * 
 * .
 */

//Capacity(vs��������'\0')
/**
 * 1.size��length:һ��,��ʷ��������,������length,������size(Ϊ�˺��������ݽṹ����һ��)
 * ����:�����ַ����ĳ���
 * 
 * 2.max_size:
 * ����:�ַ�����󳤶�,ʵ����ûʲô��ֵ
 * 
 * 3.resize,��������
 * ����:���µ����ַ�����С,
 * 
 * 4.capacity
 * 
 * 5.reserve
 * ����:�����޸�����
 * 
 * 6.clear
 * ����:����ַ���
 * 
 * 7.empty
 * 
 * 8.shrink_to_fit
 * ����:����������
 * 
 * 
 * 
 * .
 */
 




