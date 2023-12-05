﻿#pragma once

//Assembly

/*
汇编中，我们都知道div除法指令，要求被除数默认存放在ax,或者dx和ax中，而且要求被除数的位数，必须是除数的2倍，
    比如说，除数位8位，被除数就为16位.
为什么被除数的位数一定要为除数的2倍呢，有种解释是这样的：
    因为cpu只会做加法运算，把其它一切的算法都转换成加法，比如说，除数 就先转换加法，例如36/6  
    当cpu看到这个运算时，就会这样想，需要多少个6 相加才能得到36呢，然后cpu就从1个6 ，2个6...........这样一种算下去，
    终于最后发现原来是6个6啊，从这我们可以看出，cpu是不断的用除数相加，知道找到结果为止，
    这就出现问题了，如果被除数不是除数位数的2倍，再相加的过程中，就可能超出除数的位数所能表达的最大数值，从而越界，
    如果能保证 被除数是除数的2倍, 这问题就能解决了
*/


/*
多核CPU各自都有一套寄存器组
如0号CPU的EAX,1号CPU的EAX ...

多核:多个CPU共用一个内存

*/


//内存对齐
//1.数据的起始地址必须是其自身大小的整数倍
//2.结构体和对象的对齐值是其成员中占用内存最大的数据类型的大小---不是结构体的大小,就算结构体的大小是32,最大成员是double则对齐值就是8
/*
例:
struct s1
{
    double d1; //8 --- 最大,所以是对齐数
    char c1 ;  //1
    int  i1;   //4 --- (1+4)<8 , 且起始地址在+5小于8,所以c1,i在同一个字节
};
s1的默认大小是8+8([1+4]->8)=16

struct s2
{
    char c1;   //1 --> 8(最大对齐数)
    struct s1; //16 --- 其最大成员大小为8,所以对齐数为8
    int i1;    //4 --> 8(最大对齐数)
};

s2的默认大小是8+16+8 = 32;

*/





