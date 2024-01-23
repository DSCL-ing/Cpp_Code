#pragma once


/*
$ 时间接口
1.time
2.gettimeofday
3.localtime

static std::string getTime()
{
//struct tm
//  int tm_sec;			 Seconds.	[0-60] (1 leap second)
//  int tm_min;			 Minutes.	[0-59] 
//  int tm_hour;		 Hours.	[0-23] 
//  int tm_mday;		 Day.		[1-31] 
//  int tm_mon;			 Month.	[0-11] 
//  int tm_year;		 Year	- 1900.  
//  int tm_wday;		 Day of week.	[0-6]
//  int tm_yday;		 Days in year.[0-365]
//  int tm_isdst;		 DST.		[-1/0/1]


time_t curr = time(nullptr);
struct tm* tmp = localtime(&curr); //参数事time_t类型的时间戳
char buffer[128];
snprintf(buffer, sizeof(buffer), "%d-%d-%d %d:%d:%d", tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
return buffer;
}


*/


//srand()只对当前线程有效 多线程要注意,可能不生效,默认都是srand(1)


//1.sizeof 变量 --- 证明sizeof不是函数,而是关键字
//2.sizeof(关键字)
//  sizeof(变量)


/*
mode_t; //就是unsigned int == uint32_t 
uint32_t; // usigned int
uint64_t; // usigned long int
int64_t   //long int 或 long long int
int32_t   //int
int16_t   //short
int8_t    //char
size_t    // usigned long  int
ssize_t   // signed long int
time_t    //long int 
*/

//堆栈 == 栈


//野指针：指向垃圾内存的指针；（1）指针变量没有初始化（2）指针被delete或者free之后没有置为空（3）指针操作超越了变量的范围
//悬垂指针：指向曾经存放对象的内存，但是该对象已经不存在了；delete操作完成后的指针就是悬垂指针，此时需要将指针置为0变为零值指针；




//关键字 volatile [ˈvɒlətaɪl] 
/*
{
关键字 volatile [ˈvɒlətaɪl] 
作用:内存可见 --- 拒绝CPU将内存变量优化到寄存器
	编译器将内存变量优化到寄存器后,对内存不可见 --- 多执行流问题,可重入/不可重入问题
(其他语言未知)

# objdump -S 可执行程序 // 反汇编

[chj@hecs-282967 ~ 17:32:15]$ gcc --version
gcc (GCC) 4.8.5 20150623 (Red Hat 4.8.5-44)
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

-O0 -O1  -O2  -O3 //gcc有四种优化等级 -- //第一个是字母O,不是零0

$ 演示: 寄存器优化 gcc -O1或-O2或-O3(是欧不是零)
[[[[[[[[[[[[[[[[[[[[[

volatile int quit = 0;  //定义一个全局的quit

static void handler(int signo)
{
  (void)signo;
  printf("change quit from 0 to 1\n");
  quit = 1;                                    //发送信号后,quit改为1
  printf("quit %d\n",quit); //此处编译器没有优化,printf打印的是内存中的quit,所以是正确的
}

int main()
{
  signal(2,handler);
                                                                         
  while(!quit);//不加括号,高频访问,骗编译器优化 //给main发送信号,发现执行了handler,但是循环还在继续

  printf("man quit 正常");

  return 0 ;
}

]]]]]]]]]]]]]]]]]]]]]

$ while不退出的原因是,
1.while(!quit);这样的语句会一直运算,会消耗很多CPU资源.编译器发现quit是循环条件,且while语法体为空,就识别成了一个不易改变的量,所以就修改代码,
	从汇编层次,将quitmov到寄存器,修改代码成每次判断quit改为只判断一次,之后就不再判断.
2.因此执行信号执行流时,将quit从内存上修改了,但是while只判断寄存器的quit,所以不会退出

$ 解决方法:
1.使用volatile关键字,然变量不要加载到寄存器,保证变量的内存可见性
2.不使用gcc优化

程序执行原理:进程的数据加载到内存中,但是运算要加载到CPU中 --- 越靠近CPU越快

优化原理:将频繁访问而不作修改的数据加载(拷贝)到寄存器,内存中的数据还在,只是屏蔽了.
	CPU会优先读取寄存器中的数据,提高访问速率 ---- 就近原则

编译器优化:实际是修改代码,在汇编层次上修改
	---> 编译器优化不一定是好的,可能会导致意想不到的问题
}
*/



//宏可以没有值

//条件编译  -- 就是一个宏版本的if-else
#ifdef 宏    --如果该宏被定义,则执行 -- #define (宏)关键字..
   //...
#else        --否则执行这条 
   //...
#endif

//ifndef 是如果宏没有定义 ,即ifdef的否定







