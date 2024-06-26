/*****************************************************************//**
 * \file   Note.h
 * \brief  
 * 
 * \author 26390
 * \date   May 2023
 *********************************************************************/
//



/**	note
 * 
 * 与scanf有关,项目属性->配置属性->C/C++->SDL检查，选测是或者否
 * 
 * 效率:1.编译速度 2.运行速度
 * 编译速度一般不会影响,实际影响是运行速度
 * 重载影响的是编译速度,不影响运行速度,怎么影响编译速度? 寻找过程
 * 
 * C++中习惯用const和enum枚举来替代宏,用inline去替代宏函数
 * 
 * 定义是开辟实际实内存空间,声明没有开辟空间(定义有设定含义和开辟空间两种说法,按语境区分)
 * 
 * 形参和局部变量放在栈上,代码段是存放指令的空间
 * 栈是数据存放位置,代码段是存放指令的空间,一个是数据,一个是指令 --- 《深入理解操作系统》
 * 如果对象是new出来的，则对象，对象的成员变量保存在堆区;直接定义的在栈上
 * 
 * 返回值与返回类型有关,如果返回值是指针,则返回地址(可能会返回已销毁地址)
 * --- 如果返回值是具体类型,则返回返回值对应空间的拷贝(一个返回一个,一块返回一块)
 * --- 如果返回值是引用类型,则返回值是指针.
 * 
 * C++类型分成内置类型和自定义类型
 * 1.内置类型为int/char/double/.../还有指针,所有的指针都是内置类型
 * 2.自定义类型为class/struct/union等定义的
 * 
 * switch基本不会用了,一般能用数组代替就用数组,短小精悍 
 * 
 * bool值大小,true真值为1,false真值为0,sizeof(bool)==1
 * 
 * 静态变量只会初始化一次
 * 
 * ctrl+enter :向上插入一行,并且光标跳到上一行(新行)
 * shift+enter:在光标后插入一行
 * ctrl+shift+enter:向下插入一行,并且光标跳到下一行
 * 
 * 类和对象的理解:引申:所有访问对象的操作,都是通过this来完成的.即:先到类,然后通过this再去找对象
 * 
 * iostream头文件很牛逼,包含了很多C(重点)和C++的函数,一个顶1万
 * 
 * C++只有相近类型才能发生隐式类型转换,如int double这些才可以.-- 看有没有相应的构造函数
 * 
 * 成员访问运算符 ->和.不一样.后者是对象直接访问成员, ->是编译器特殊处理后才能访问成员.(指针没有明确对象范围,需要特殊处理)
 * -- 重点是访问 , 是编译器特殊处理过的直接访问成员,并不是解引用什么的(看箭头运算符重载).需要学习编译器底层
 */

//编译器
/**
 * 1.编译器不编译.h文件,.cpp才会被编译,不然.h也会报错,所以.h可以不包含必要的头文件
 * 2.模板先不要定义和声明分离 :麻烦 .先都写在头文件
 * 3.对于头文件,包含在.cpp的头文件会向上寻找需要的头.所以头文件的位置是需要注意的  (代码向下走,寻找往上走)
 * 
 * 4.如果要声明与定义分离,则一般会把需要的头文件包含在.h文件里,然后再包含到各个.cpp里,这样就能防止不同cpp没有包到需要的头文件
 * 
 * 编译器对函数参数匹配原则:匹配最接近的 --> 先走一模一样,没有再走近似的 --> 直到不匹配
 * 所以有些情况下,加了const编译器不会匹配(模板)或不优先匹配
 * 
 * .
 */








//关键字:namespade 命名空间 -- 命名空间域,只影响使用,不影响生命周期
/**
 * 引入:
 * 自己定义的名字和库里的名字冲突
 * 项目组，多个人之间定义的名字冲突
 * 
 * 使用:将定义的完整语句放入命名空间内(类型,变量)
 * 调用:命名空间名::变量名; 
 * 注意1:命名空间必须放在名字的前面,类型的后面.例:struct namespace_name A;
 * 注意2:在多个文件定义同名的命名空间会被合并->认定为同一个命名空间->可能会同名冲突
 * 注意3:命名空间可以多层嵌套 name1::name2::name3::name4...nameK::A;
 *		顺序:外到内:1->2->3...->A
 * 
 * 问题1:繁琐,每次使用都要在前面使用域作用限定符
 * 解决1:全局展开:using namespace A; 
 * 用途:将命名空间扩展到全局  ;( 正式项目不建议展开 ,也有命名冲突风险;一般在小练习时方便使用才展开)
 * 特别:有一些标准库被C++放入命名空间,有标准库std 
 * 解决2:部分展开,把常用的部分展开: using std::cout; using std::endl
 * 
 * 总结:实际开发的项目工程:1.指定命名空间访问,2.常用部分展开
 * using不是关闭命名空间,而是改变查找规则,在执行时候查找的范围
 * 
 * 
 * 小总结:
 * 1.在头文件中不使用using ,a.头文件写给别人用,容易命名冲突,b.冲突时容易有多层嵌套,回溯要找很多层
 * 2.CPP文件可以少用,我还没发现问题,之后再总结
 * 
 * 
 */

//关键字:cout
/** 
 * 目前先理解成控制台输出
 * 特点:可以自动识别类型
 * (补)原因:cout,cin是类对象,而自动识别类型就是运算符重载(C++库已将常用的类型都重载好了)
 * cout是ostream类型的对象,头文件包在<iostream>里
 */

//关键字:cin
/**
 * 目前可以先理解成控制台提取(输入)
 * 特点:可以自动识别类型(不像c语言scanf一样需要格式符)
 * 可以控制精度,但比较复杂,可以用c语言代替
 * 默认分隔符:\t,space,enter
 * 
 * 结束流提取循环的方法
 * 1.ctrl+C强行终止程序--杀进程
 * 2.ctrl+Z+回车,输入结束命令,柔和
 * 
 */

//::域作用限定符
/**
 * 左边::右边,二元运算符,左边是选择的域(空为全局域),右边是变量
 */

/**
 * << 流插入运算符(也是运算符中的一种,和其他运算符在一起时要注意优先级,加上合适的括号)
 * 目前先理解为流向,将字符串流向控制台cout,将字符流向前面的尾巴.cout << "a" << "1"; (输出结果为a1)
 */

/**
 * >> 流提取运算符
 * 也理解成流向,从cin流出来
 */

//缺省参数
/**
* 举例:
 * void fun(int a = 99)
 * {
 *    //函数体;    
 * } 
 * 
 * fun(1); // 形参a = 1;
 * fun();  // 形参a = 99;  --- 使用缺省参数可以在调用函数时不用传参,使用函数内部的默认参数 
 * 
 * 
 * 全缺省:所有形参都有缺省值,在调用时可以给部分参数传参或不传参 
 * 
 * 半缺省:一部分参数有缺省值,必须从右往左依次连续<==========
 * 
 * 注意:参数必须按顺序传
 * 1.使用缺省值,规定必须从右往左连续使用
 * 2.传参,必须从左往右依次传参,不能跳跃,如fun(,1,)和(,,1)和(,1,1) 
 * 如果有形参没缺省,则该形参必须赋值,此时可以跳过缺省的形参
 * 
 * 原因理解:当func(int a = 0 ,int b = 0 , int c){} ,如果传func(1,1),则无法判定传参传给谁.
 *			** 或者是默认传参从左往右,让缺省值有用
 * 
 * 缺省参数的使用场景:在需要有参数,但参数未知时(不知多少也不想随便给一个值)
 * 如:栈的初始化:开辟空间使用缺省参数default=4,在外界不知道大小时可以不传参,使用默认值---
 *	  ---在外界知道大小时可以传参控制.
 * 
 * 注意:缺省不能在声明和定义中同时出现(不论值相同还是不同),会报错.---
 *      --- 如果声明和定义分离,则缺省在声明中给,因为主函数只展开头文件中的声明,定义中给会报错
 * 
 * 缺省参数必须是常量或者是全局变量或者静态变量,,能够访问到的(有时报错就是用了错误的缺省值),//但一般都不会使用全局变量(还没遇到)
 * 
 * C不支持缺省参数
 * 
 * 缺省值的使用场景:
 * 1.如果函数有有参和无参的重载,在无参的位置使用缺省值,可以减少一个重载函数
 * size_t find(const string& str,size_t pos = 0);//
 * 
 * 
 * 
 */

//函数重载 function overload
/**
 * 修订:重载的条件
 * a.参数类型不同
 * b.函数名相同
 * c.同一作用域
 * 
 * 特性:返回值,参数个数,顺序,缺省值,形参名
 * 1.返回值没有影响
 * 2.参数个数没有影响
 * 3.参数顺序没有影响
 * 4.缺省值没有影响
 * 5.形参名没有影响
 * 
 * 
 * 重点:返回值不能作为识别重载的必要条件,(java的可以) ,而且不以函数名修饰规则有关 --->
 * --->在调用时只写函数名和参数,无法识别出返回值,所以与函数名修饰规则无关
 * --->参数列表不同时,返回值可以不一样
 * 
 * 范围:同一作用域
 * 
 * 特别:浮点默认为double,要用float需要在后面加f,long需要加l
 * 
 * 原理简要:以ADD为例,C++在调用重载函数时,给函数名做了修饰规则(C语言是直接找函数名)
 * Add(int,int)在汇编中的修饰规则(linux下的,windows的很复杂)为:_Z3Addii ,其中_Z为前缀,3为函数名长度,--->
 * ---> Add为函数名,ii为类型int,int. 因此可以在编译时区分重载函数(char则为_Z3Addcc)		 --->
 * ---> 故形参数量和类型相同则会报错(修饰名一样,肯定错),
 * ---> 报错一般会有:     无法声明的外部符号..
 * ---> 如果是指针则类型符号为Pi,Pc,Pd等...
 * 
 * 
 * 注意:编译器一般调用最匹配用户原型的,不会说哪个更好就调用哪个
 * 
 */


//引用
/**
 * 
 * JAVA的引用类似int* const（和C++不一样：JAVA绑定对象后可以重新绑定）
 * C++中的引用就是取别名.（是int* const，指针绑定对象后不能解绑，不能重新绑定）
 * 编译器不会给引用变量开辟内存空间(语法层面),它和它引用的变量共用同一块内存空间(实际底层有空间)
 * 引用在汇编层面上和指针基本一致
 * 
 * 作用:在需要形参能改变实参的情况下使用(输出型参数)
 * 
 * C++的引用是不能改变指向的,赋变量名和赋值都只是改变对象的值,不能改变指向 ;--->
 * ---> java可以,赋变量名就是改变引用的对象,赋值就是改变对象的值,可以改变指向.
 * 
 * 引用特性:
 * 1.引用在定义时必须初始化,					指针可以不初始化
 * 2.一个变量可以有多个引用,
 * 3.引用所引用的实体不能再改变,				指针可以改变
 * 4.没有NULL引用,								有NULL指针
 * 5.sizeof,引用为引用类型的大小,				指针大小始终是地址空间所占字节数
 * 6.自增,引用为对象实体增加1,					指针自增为向后偏移一个类型大小
 * 7.没有多级引用,引用的引用还是实体的别名		有多级指针
 * 8.访问实体方式不同,引用编译器自己处理		指针需显示解引用
 * 9.引用更安全	
 * 10.常量不允许引用 -- 不能修改	
 * 11.const没有在&右边的语法 -- 报错 , const在类型的左边或右边都可以,只要在&左边即可;
 * 
 * 
 * tips:引用替代不了指针,大部分是用引用,小部分指针更合适则用指针,且只用简单的足以
 * 参数是指针的话有时可以不传引用
 * 
 * 代码:
 void Swap(int& a, int& b) //
{
	int tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int a;
	int& i = a; //i ,a指向同一个对象
	
	int* j;
	int*& rj = j;//指针引用

	int a = 1;
	int b = 2;
	Swap(a, b);	//直接改变实参
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	return 0;
}}
 * 
 * 作用2:作返回值 //
 * 
 * c语言中返回值原理简要:
 *	 int fun()   { int n;  return n;} 
 *	 void main() { ret=fun; }
 *	 其中,在ret接收n时(return后),fun中的栈帧已经被回收使用权了(不是真销毁,而是没有使用权)--->
 * --->而在之前,传n是通过return语句,将n传给main(通常)中临时创建的临时变量(临时变量小内存一般是寄存器,--->
 * --->大可能是别的),在fun销毁前(return结束前)将n传给临时变量,然后再通过临时变量将值传给ret
 * 
 * 注:函数中的static也一样,虽然在函数中声明的static在函数结束后不会销毁,但返回static的值还是--->
 * --->要借助临时变量来给ret接收
 * 
 * 引入:上面方式称为'传值返回',其中返回值类型是临时变量的类型
 * 
 * C++中支持传引用返回
 * 顾名思义:就是将返回值的引用传回来
 * 使用场景:出了作用域后,要返回的对象还在(不受被调函数生命周期影响的)
 * 效果:
 * 1.减少拷贝,提高执行效率
 * 2.调用者可以修改返回对象
 * 代码1：错误返回值使用
int& Add(int a, int b)
{
	int c = a + b;
	return c;
}

int main4()
{
	//错误演示
	int& ret = Add(1, 2); //如果ret不是引用,可以接收地址,会警告,但编译器会转换
	Add(3, 4);
	cout << ret << endl;//无论如何,结果都是未定义的
	return 0;
}

 * 代码2:修改返回对象
typedef struct Array
{
	int arr[10];
	int size;
}AY;	

int& posAlter(AY& ay,int i)
{
	return ay.arr[i];
}

void main()
{
	AY ay;
	for (int i = 0; i < 10; i++)
	{
		posAlter(ay, i) = i;
		cout << ay.arr[i] << " ";
	}
}
 * 
 * 权限: 指针和引用,赋值/初始化 权限可以保持(平移)和缩小,但是不能放大
 * 放大:
 * 错误例子1:const int c = 2; int& d = c;   //典型放大权限
 * 错误例子2:const int* p1 =NULL; int* p2 = p1; //也是会报错,因为p2权限大于p1,(会放大权限)
 * 
 * 保持/平移:
 * const int c = 2; const int& d = c;
 * const int* p1 = NULL; const int* p2 = p1;
 * 
 * 缩小:
 * int c = 2; const int& d = c;
 * int*p1 = NULL; const int* p2 = p1;
 * 
 * 特别1:函数返回值是具体类型(如int)的临时变量具有常性,权限类似const不可修改.--->
 * --->如果用int&接收会报错(权限放大)
 * 编译报错: int fun(){int n,return n }   void main(){ int& ret = fun(); return 0} 
 * 编译通过: int fun(){int n,return n }   void main(){ const int& ret = fun(); return 0} //加const修饰 
 *   
 * 特别2:类型转换会产生临时变量,显式隐式都会
 * 如果给类型转换的类型起别名,必须使用const,用于保持权限不被放大
 * 原因:类型转换会产生临时变量,临时变量是具有常性的(const),而起别名的对象不是原类型,而是临时变量,--->
 * --->因此需要const修饰
 * 如：
 * 	int d = 1.1;
	int& ri = d; //没有发生类型转换不需要const,也可以加上

	double d = 1.1;
	const int& ri = d; //显式/隐式类型转换必须要加const
 * 
 */



//内联函数:关键字inline
/**
 * 宏函数正确格式:Add为函数名;(x,y)为函数参数表达式列表;  -- 宏参数可以是表达式
 * ((x)+(y))中括号是避免替换时与其他符号产生优先级冲突,外括号有(a+b)*c,内括号有(a|b)+(a&b) --->
 * --->即替换后参数表达式的目标运算顺序被改变 -- 为了安全每个参数表达式都加上括号
 * 在定义宏函数的时候注意宏函数名和’('之间不能有空格。
 * 宏是非常暴力的替换,意味着规则很复杂.主要是为了防止副作用
 * 举例:#define Add1(x,y) ((x)+(y))
 * 
 * 宏的缺点:
 * 1.不能调试(编译的时候是直接替换掉)
 * 2.没有类型安全的检查
 * 3.有些场景非常的复杂
 * 
 * 宏的优点:
 * 1.快,非常快,不用建立栈帧,直接替换后执行
 * 2.提高复用性,可维护性;对于重复出现的常量,用宏可以方便维护
 * 
 * 引入内联函数:C++为了保留宏的优点,避开宏的缺点.引入了内联函数
 * C++推荐用const和enum去替代宏常量,inline去替代宏函数
 * 
 * 关键字:inline 内联
 * 用法: inline int Add(int x,int y){ return x+y };
 * 原理:编写时按函数一样编写,而编译时会将函数体替换函数调用,像宏一样展开,替换;不必调用栈帧
 * 性能:规则简单,效率不比宏函数差
 * 
 * 注:内联在默认debug下不会起作用,需要修改一些配置.一般在release下起作用
 * 配置步骤:
 * 1.在项目属性中,配置属性C/C++,常规,调试信息格式,选为程序数据库(/Zi)
 * 2.在项目属性中,配置属性C/C++,优化,内联函数扩展,选为只适用于_inline(/Ob1)
 * 
 * 检查是否调用内联:在反汇编中查看是否有call 
 * 
 * 
 * 特性:
 * 1.内联是一种以空间换时间的做法.
 * 缺陷:可能使目标文件变大,不是运行时占用的内存,而是编译出来的可执行程序体积大,因为是直接将函数体换进去--->
 * ---> 设函数体内代码行数n,调用函数有m行,(下面编译后不一定是m和n,只是估算)
 * ---> 若全部执行内联,则行数增加n*m,若执行普通函数,编译后只有n+m行,相差几个数量级
 * ---> 坏处:导致用户体验下降
 * 优势:少了调用开销,提高程序运行效率.
 * 
 * 2.inline对于编译器而言只是一个建议,不同编译器关于inline的实现机制不同,一般函数规模较小的,不是递归,且频繁调用-->
 * --->的函数采用inline修饰,否则编译器会忽略,避免可执行程序体积灾难性过大.因此inline不能强制要求编译器展开
 * 编译器说了算
 * 
 * 内联说明只是向编译器发出一个请求,编译器可以选择忽略这个请求.
 * 
 * 3.类中的成员函数默认隐藏了inline
 * 
 * 内联的使用注意：
 * 1.内联函数不能声明与定义分离
 * 因为编译器不会给内联函数开辟空间和生成堆栈地址,函数名也没有可以跳转的地址
 * 编译时找到内联函数后，直接展开跟在内联后面的函数体/定义...
 * --->（函数名就是存放堆栈地址的形式(间接)地址和jmp指令的地址:
 * ---> 一般访问普通函数名可以得到jmp指令和函数实际堆栈地址）
 * ---> 因此,内联函数的声明没有意义,通过内联函数的声明调用内联函数将会报错
 * 所以:定义内联函数时,将内联函数定义在头文件中即可
 * 
 * 
 * 
 * 内联函数的场景：
 * 1.成员函数在类中定义，则会被当作内联（编译器支持）；
 * 
 */

//关键字auto
/**
 * 由编译器自动推导类型
 * 在C++11标准的语法中，auto被定义为自动推断变量的类型。(gcc,g++4.6以上,VS2013)
 * 实际价值：简化代码，C++后面复杂代码用到 ，当类型很长时，可以考虑自动推导（也可以用typedef）
 * 
 * 注意：typedef+const时要小心，会编译成const+typedef ???
 * 
 * 灵活使用1:
 * 	int* a = 0;
	auto b = &a;	//自动推导b为a类型
	auto* c = &a;	//限定c为指针类型,只要是指针，不论二级三级指针
	auto** d = &a;	//限定d为二级指针起步
	auto& e = a;	//限定e为别名
 *
 * 灵活使用2:
 * 	范围for(遍历) -- 语法糖
	自动依次取数组中数据赋给用户定义的变量(x),
	int array[] = { 1,2,3,4,5,6 };
	for (auto x : array) //可以其他类型:如int x; char y;
	{
		cout << x << " ";
	}
	cout << endl;
 //注意:范围for是将原数组的内容赋值给用户新定义的变量,再输出新变量的值
 * ---> 对变量做修改是不会影响到原数组的内容
 * 
 * 如果要影响原数组,可以使用引用 -- 数据量大的话最好加引用,不加引用就是拷贝
 * for (auto& x : array) 
	{
		x *= 2;
		cout << x << " ";
	}
	cout << endl;
 * 
 * 注意:不能将通过形参接收的数组用于范围for,因为C语言为了提高运行效率,不支持接收组数,--->
 * --->只能接收数组名存放的数组首地址,通过首地址无法识别数组的范围,因此不能使用
 * 
 * 对范围for中的常用auto变量名
 * $ auto x  --- 自定义类型
 * $ auto e  --- element -- 库中类型/自定义类型
 * $ auto s  --- string
 * $ auto i  --- int
 * $ auto ch --- character
 * 
 * 
 * 
 * 
 * 灵活使用3:
 * auto可以在同一行定义多个相同类型的变量,但不能在同一行定义不同类型的变量(会编译失败)
 * 	正确例子:auto a = 1, b = 2;
	错误例子:auto c = 3, d = 4.0;

 * 注意:
 * 1.auto不能作为函数的参数(形参)
 * 2.auto不能用来声明数组
 * 原因:1.编译器不能识别;2.避免和C++98混淆
 * 
 * 
 * 
 * 
 */

//nullptr
/**
* 
* 一.NULL和nullptr区别
 * NULL实际是一个宏,在传统的头文件中(stddef.h)中,NULL被定义成了C++是0,其他是((void *)0) --
 * --->其中0就是整数0,((void *)0)则是无类型0地址;即C++中NULL为0
 * 历史原因所导致,故C++有时在某场景下会有问题
 *  如:
 void f(int)
 {
	 cout << "int" << endl; 
 }
 void f(int*)
 {
	 cout << "int *" << endl;
 }
 int main()
 {
	 f(0);    //print:int
	 f(NULL); //print:int
	 //说明:NULL为0
	 f(nullptr);//print:int *
	 //说明nullptr为指针
	 return 0;
 }
 * 因此,C++11中引入nullptr作为(void*)0
 * 
 * 使用nullptr:
 * 1.使用nullptr不需要包头文件,因为nullptr是C++11中作为新关键字引入的
 * 2.C++11中,sizeof(nullptr)与sizeof((void*)0)所占字节数相同
 * 3.为了提高代码的健壮性,在后续表示指针空值时最好使用nullptr
 * (健壮性也叫鲁棒性:在异常和危险情况下系统生存的能力)
 * 
 * 语法原则:
 * 1.已经存在的东西,哪怕是坑也不能改.(有可能会影响到以前的代码,灾难)
 * 2.向前兼容
 * (python早期2.7除外,当时python不是主流,冒险升3.0后向下不兼容)
 * 
 * 二.空指针访问
 * 前置知识:   .和-> 应理解成访问类成员访问运算符 -- 重点是访问,和解引用有区别 
 *  -- 补充:->是编译器特殊处理过的,他的操作数是指针,需要编译器处理才能访问到对象内的成员
 * 例:
 * 
 * 
 *  class A {
 *		public:
 * 		int _a;
 * 		void fun() {};
 * 		void fun(int a) {_a = a;};
 * };
 * int main() {
 * 		A* ptr = nullptr;
 * 		ptr->fun();//访问代码区(类共享,公共区,属于类域不属于全域),没解引用.正常运行
 * 		ptr->fun(1);//访问代码区,但解引用赋值给对象,奔溃
 *		(*ptr).fun();//正常运行,VS实际上没解引用对象(反汇编和->一样),然后访问公共区找函数去了
 * ---> 理解:*ptr 和ptr->都是通过对象的信息找到类,然后再访问作为右操作数的成员.期间没有作修改(并没有执行构造函数)
 * ---> 引申:所有访问对象的操作,都是通过this来完成的.即:先到类,然后通过this再去找对象
 * 		return 0;
 * }
 * 
 * 
 * 
 *
 *
 *
 *
 * 
 * 
 */


//面向对象
/**
 *  引入:

 //C语言定义结构体
 typedef struct ListNode 
 {
	 int val;
	 struct ListNode* Node;//类型为struct ListNode
 }ListNode;
 //C语言中typedef在此处后才起作用

 //C++将结构体升级成了类:struct为类的其中一个声明关键字
 struct ListNode
 {
	 //...方法
	 int val;
	 ListNode* Node;		//类型为ListNode
 };
 * 因为类是一个整体,所以成员变量,成员方法...,的内部位置没有顺序,放哪都行
 * .
 */

 //访问限定符/权限
 /**
  * C++有3种：public(公有),protected(保护),private(私有)
  * 说明: 现阶段只需认为保护和私有没有区别,等到中期学继承后再区分.
  * 1.公有就是在类外面可以访问,
  * 2.保护和私有就是只有在类内才能访问
  * 3.访问权限作用域从该访问限定符出现的位置开始知道下一个访问限定符出现时为止
  * 4.如果后面没有访问限定符,作用域就到'}'结束(即类结束)
  * 5.class的默认访问权限为private,struct为public(因为struct要兼容C) -- 声明不写权限时默认为private
  *
  * C++实现封装的方式：用类将对象的属性与方法结合在一块，让对象更加完善，通过访问权限选 --
  * ---> 择性的将其接口提供给外部的用户使用
  *
  * 注意：访问限定符只在编译时有用，当数据映射到内存后，没有任何访问限定符上的区别

C++的访问修饰符的作用是以不同的类为单位
私有是为了实现“对外”的信息隐藏，或者说保护，在类自己内部 ,允许访问同类型的私有变量,但不能访问其他类型的私有成员
  
  */

  //this
  /**
   * 类内成员函数的隐藏参数
   * 
   * 类型:类*
   * 
   * 值:对象的地址
   * 
   */

//类
/**
 * 更常用的关键字class
 * 类的定义模板:
 * class className
 * {
 *	//实体:由成员函数和成员变量组成
 * };
 * class为定义类的关键字,className为类的名字,{}中为类的主体
 * 类体中内容称为类的成员:类中的变量称为类的属性或成员变量;
 * 类中的函数称为类的方法或者成员函数.
 * 
 * 类定义了一个新的的作用域:类域;类中的所有成员都在类的作用域中 ---
 * ---> 在类外定义成员时,需要使用::作用域操作符指明成员属于哪个类域
 * ---> (定义是开辟实际实内存空间,声明没有开辟空间)
 * ---> 类外通过类指针引用成员函数时,不需要再传this 
 *  
 * 定义类有两种方式
 * 1. 声明和定义全部放在类体中，需注意：成员函数如果在类中定义，编译器可能会将其当成内
 * ---> 联函数处理。
 * 2. 类声明放在.h文件中，成员函数定义放在.cpp文件中，注意：成员函数名前需要加类名::
 * --->(加类型::的作用是,告诉编译器当前函数不是全局函数,是类里面的成员函数)
 * 一般情况下，更期望采用第二种方式。
 * 
 //声明与定义分离1：未学权限，先使用struct(默认公有)
 类.h:
struct Stack1 
{
	//成员函数
	void Init(int n = 4); //缺省参数
	void Push(int x);
	//成员变量
	int* a;
	int size;
	int capacity;
};
类.cpp:
#include"类.h"
void Stack1::Init(int n) //
{
	a = (int*)malloc(sizeof(int) * n);
	if (a == nullptr)
	{
		perror("malloc fail!");
		return;
	}
	capacity = n;
	size = 0;
}
void Stack1::Push(int x)
{
	//..
	a[size++] = x;
}
 *
 * 定义成员变量时,一般习惯在名字前加上'_'.类似java的this,用于区分形参和成员变量 -- C++不建议使用this，一般加_区分
 * 不一定是用'_',其他方式也可以的，主要看公司要求。一般都是加个前缀或者后缀标识区分就行。
 * 用'm_'还有'mName'小驼峰等...(m为menber成员的缩写)
 
 
 * 面试题:C++中struct和class的区别是什么？
  解答：C++需要兼容C语言，所以C++中struct可以当成结构体使用。另外C++中struct还可以用来
  定义类。和class定义类是一样的，区别是struct定义的类默认访问权限是public，class定义的类
  默认访问权限是private。注意：在继承和模板参数列表位置，struct和class也有区别，后续学习
  补充：一般来说成员全部开放的时候用的是struct，封装的时候使用class
  如
  1.stl_list使用的是struct,
  2.struct默认权限是public,class是private
 
 C++中struct和class的区别
相同点：

两者都可以用来定义用户自定义数据类型（UDT）。 两者都可以包含成员变量和成员函数。

不同点：

在默认情况下，C++中的class成员默认为私有（private），而struct成员默认为公有（public）。

C++中的class可以实现封装和数据隐藏，可以使用访问修饰符指定成员的访问权限（公有、私有或保护），而struct默认公开其成员。

C++中的class支持继承和多态性，而struct不支持。

在C语言中，struct只能包含变量，不能包含函数，而在C++中，struct可以包含成员函数。 引申：

在C++中，struct可以被视为class的一种特例，除了默认访问权限和继承方式不同之外，它们几乎具有相同的特性和语法。

C++中的struct可以实现与class相同的功能，但在设计上用于表示更简单的数据结构。 在C语言中，struct主要用于定义数据结构，没有封装和继承的概念，仅仅是一个简单的数据集合。

在C++中，struct被扩展为支持更多的特性，使其能够拥有成员函数、封装性和继承等特性，更加类似于class。




 
 * 类的实例化:即开辟空间
 * Class className;   //实例化
 * 
 * 错误的实例化方式:
 * Class className(); //分不清是函数声明还是实例化(虽然不会报错,但可能导致未知的bug)
 * 
 * 比喻:
 * 类:图纸,设计图(图纸不能住人,不能访问实体所有的)
 * 对象:用图纸设计的实物,可以多种多样
 * 
 * 
 * 实体空间中只存放成员变量,不存放成员函数(成员函数存放在代码段)
 * sizeof(实体) = 成员变量的大小(要考虑对齐)  --- 没有成员方法
 * 为什么没有成员方法,为什么实体空间中不存放成员函数? ---
 * ---> 成员变量一般是一个实体唯一的,而成员函数是各个实体都能使用的,---
 * ---> 就像小区中每套房子的各个房间都是独立的,但小区中的公共设施是公用的,---
 * ---> 如果为每套房子都配一套公共设施,必然会造成浪费,所以成员函数不存放在实体空间中.
 * 即:
 * 每个对象的成员变量是不一样的,需要独立存储(栈)
 * 如果对象是new出来的，则对象，对象的成员变量保存在堆区!!!
 * 每个对象调用的成员函数是一样的,所以放到公共代码区(代码段)
 * 
 * 注意sizeof(类)的大小:
 // 类中既有成员变量，又有成员函数
 class A1 {
 public:
	 void f1() {}
 private:
	 int _a;
 };

 // 类中仅有成员函数
 class A2 {
 public:
	 void f2() {}
 };

 // 类中什么都没有---空类
 class A3
 {};
 int main()
 {
	 cout << sizeof(A1) << endl; //4
	 cout << sizeof(A2) << endl; //1
	 cout << sizeof(A3) << endl; //1
	 return 0;
 }
 * 说明:类只有成员函数或为空时,占1个字节大小,着1byte不存储有效数据 --- 
 * ---> 用于占位,表示对象存在(被被实例化定义出来了)
 * 
 * 类成员访问:
 * 1.如何得知访问成员方法时访问的是哪个对象的成员方法?
 * 引入:关键字this :成员方法中隐含了Date* this参数,因此要注意参数列表不能多写
 //实际编译器操作
  class Date
 {
 public:
	 void Init(Date* this,int year, int month, int day) //<<<<<<<<<<<<不能显式,只能隐式
	 {// -> === *(地址).
		 this->_year = year;							//<<<<<<<<<<<<可以显示
		 this->_month = month;							//<<<<<<<<<<<<可以显示
		 this->_day = day;								//<<<<<<<<<<<<可以显示
		 cout << this << endl;							//<<<<<<<<<<<<可以显示
	 }
 private:
	 int _year; // 年
	 int _month; // 月
	 int _day; // 日
 };

 int main()
 {
	 Date d1, d2;
	 d1.Init(&d1,2022, 1, 11);							//<<<<<<<<<<<<不能显式,只能隐式
	 d2.Init(&d2,2022, 1, 12);							//<<<<<<<<<<<<不能显式,只能隐式
	 cout << this << endl;
	 return 0;
 }
 * 说明:在调用成员方法时,编译器会隐式的加上this来指明是哪个对象调用
 * 实际写代码过程中,我们不能人为显式的在类方法的参数列表中加上 类型* this,会报错
 * 但可以显示的使用this指向对象(因为this是对象空间的地址),一般只有新手会写(￣▽￣)"
 * 
 * this的存储空间:this存放在栈上,因为this是形参(隐式),VS编译器中this指针一般存放在ecx寄存器中(分析汇编较为重要).
 * 
 * 2.访问成员函数为什么要通过对象 //引用?
 *     .访问普通函数时,会到全域中去寻找.而对象 //引用 就是告诉编译器要到类域中去找.
 * 
 * 3.如果类初始化为空指针(Date*ptr=nullptr),则通过空指针引用成员方法会程序运行奔溃吗?
 *  (1).空指针只有解引用才会报错
 *  (2).如果成员函数体中没有解引用this则不会,如cout << this << endl;
 *  (3).通过this访问成员变量,成员变量在类空间,必须解引用this,此时程序运行奔溃
 * 注意:(->)和(.)操作的过程和结果一样.如果是引用成员函数,则类名的作用就是传指针给this, ---
 * ---> 并不会解引用
 * 
 * 4.非静态不能使用Date::func();因为没有对象地址的this传给隐藏形参的this
 * 
 * 5.如果成员函数在类里面定义（不分离定义和声明）
 * 则编译器可能会将其当成内联函数处理（默认，不加inline）
 * 
 * 
 */



//封装
/**
 * 封装本质是一种更好的管理,让用户更方便使用类
 * 面向对象和面向过程区别:
 * C语言: 
 * 1.数据和方法是分离的
 * 2.数据访问控制是自由的,不受限制的
 * 问题：
 * (1)不安全,容易出错,越界,野指针等,破环程序,系统,
 * (2)不方便,需要了解底层结构,使用不方便,学习成本
 * (3)不规范,使用方法各式各样,难以维护和管理
 * 
 * 
 * C++:
 * 1.数据和方法都封装到类里
 * 2.控制访问方式
 * 
 * C++弥补了C语言的面向过程的缺点.
 * C++类和C语言结构体效率基本相同,在使用上更加方便
 * 
 */

//类中的6个默认成员函数
/**
 * 如果一个类中没有成员,则称为空类(编译前)
 * 编译器会在空类中生成6个默认成员函数
 * 
 * 默认成员函数:用户没有自己编写,编译器会自动生成的成员函数称为默认成员函数 ---
 * ---> 一旦用户显式定义编译器将不再生成(拷贝构造也算)
 * 
 * 分别为:
 * 1.初始化和清理
 * (1)构造函数:主要任务并不是开空间创建对象，而是初始化对象
 * (2)析构函数:主要完成清理工作
 * 规定:默认/内置类型不处理,自定义类型成员才会调用构造函数
 * 2.拷贝复制
 * (1)拷贝构造函数:使用同类对象初始化创建对象
 * (2)赋值运算符重载函数/拷贝赋值重载:主要是把一个对象赋值给另一个对象
 * 3.取地址重载:主要是普通对象和const对象取地址,这两个很少会自己实现
 * (1)取地址函数/取地址重载
 * (2)const取地址操作符重载函数/const取地址重载
 * 
 */

//构造函数(天选之子1)
/**
 * 构造函数是特殊的成员函数
 * 特征如下:
 * 1.函数名与类名相同
 * 2.无返回值(不能写返回值类型)
 * 3.对象实例化时编译器自动调用对应的构造函数
 * 4.构造函数可以重载(允许有多种初始化方式)
 * 5.如果内置类型满足构造函数的参数,则可以隐式类型转换成自定义类型
 * --- 隐式类型转换需要有相应的构造函数支持
 * --- 隐式类型转换的过程就是拷贝构造的过程
 *    :就是通过拷贝构造创建的一个对象,
 * 
 * 
 * 产生原因:因为C语言经常会忘记初始化,为方便使用,设置了构造函数
 * 
 * 使用:如果类中没有显式定义构造函数，则C++编译器会自动生成一个无参的默认构造函数，一旦 ===
 * ---> 用户显式定义编译器将不再生成。
 //调用构造函数
 {
   Stack st;	  //不传参写法.和其他方法不一样,构造方法和其他方法不同之处
   //Stack st();  //会警告,不能这么写,容易和函数声明混淆,故编译器不支持
   Stack st1(4);  //传参写法,为什么不会认为是声明? 因为声明需要带上类型和变量,而实例化传的是具体值,所以不会
   //st.Stack(4)  //错误!!! 不能这么写,违背了构造函数的初衷(自动初始化),语法不支持
 }
 * 
 * 灵活使用1:全缺省可以将无参构造函数(函数体内分别赋固定值的)合并到其他重载函数(不用再写无参重载)
 * ---> 无参的构造函数和全缺省的构造函数都称为默认构造函数,并且只有同时存在一个 ---
 * ---> 因为在调用时会存在歧义.(无参,全缺省,不写自动生成的,都可以认为是默认构造函数)
 //代码举例:
 Date(int year = 1900, int month = 1, int day = 1)//全缺省
{
	_year = year;
	_month = month;
	_day = day;
}
 * 
 * 规定:默认/内置类型不处理(若不初始化则是随机值),自定义类型成员会调用他的默认构造函数
 * 规定:无参,全缺省,不写自动生成的,都可以认为是默认构造函数,且只有同时存在一个
 * 
 * 特别:VS2019中构造函数不处理时会默认将内置类型初始化成0!!!可能导致无法跨平台
 * 
 * C++11补丁:对于内置类型,可以在声明位置给缺省值(不是初始化,因为声明没有开辟空间) 
 * ---> 补丁作用:如果构造函数没有初始化内置类型,则缺省值起作用
 * 
 * 问题? 声明时给缺省值还是全缺省构造函数?
 * 
 */

//析构函数(天选之子2)
/**
 * 

析构函数是一个成员函数，在对象超出范围或通过调用 delete 显示销毁对象时，会自动调用析构函数。

 
 用途:对象在销毁时会自动调用析构函数,清理对象中的资源
 * 
 * 特性:
 * 1.析构函数名是在类名前加上字符~:意义是与构造函数的功能相反(C语言中~是按位取反)
 * 2.无参数无返回值(不用写参数和返回值类型)
 * 3.一个类只能有1个析构函数.若未显示定义,系统会自动生成默认的析构函数.(不能重载)
 * 4.对象声明周期结束时,C++编译系统系统(C++编译器)自动调用析构函数
 * 5.析构顺序是按栈规则来,先析构栈顶的(最后进去的) -- 后定义的先析构
 * 
 * 规定:默认/内置类型不处理,自定义类型成员才会调用构造函数
 * 
 *

手动析构函数
1.如果对象在栈上,则不建议手动显式调用析构.析构后资源没有,但对象还在, --- 最好是出了作用域自动析构
2.如果对象在堆上,则使用delete进行销毁对象,使用delete会自动调用对象的析构函数2.如果对象在堆上,则使用delete进行销毁对象,使用delete会自动调用对象的析构函数 
 *   
 */

//拷贝构造函数(天选之子3)
/**
 * 引入:直接拷贝往往是浅拷贝,自定义类型如果有指向其他空间,拷贝后会同时指向同一块空间,非彻底拷贝
 * 
 * 规定:
 * 1.内置类型的拷贝,编译器可以直接拷贝
 * 2.自定义类型的拷贝,需要调用拷贝构造函数来拷贝
 * 
 * 默认生成的拷贝构造:当一个类没有显式地定义拷贝构造函数时，C++编译器将会自动生成一个默认的拷贝构造函数。默认拷贝构造函数执行的操作是成员变量的逐一复制，即浅拷贝。
 * 
 * (对于有多层调用的自定义类型(如栈),和分配了堆资源的,需要调用深拷贝构造,后面学习)
 * 
 * 拷贝构造意思就是:对于多级指针的,用户自己编写调用拷贝构造函数
 * ---> 不论深浅拷贝,都靠用户自己判断自己编写
 * 
 * 
 //拷贝构造函数的基本形式:
 Date(const Date& d)  //一般都会加上const,用于保护原对象.也可以不加
 {
	_year = d._year;
	_month = d._month;
	_day = d._day;
}
 * 
Date(Date d)           //无穷递归,为什么?
 { //... } 
 * 
 * 自定义类型的传参是通过拷贝构造函数传值到形参(自定义类型形参接收实参会调用构造拷贝函数)
 * 如果使用引用就没有传参,也就不会调用拷贝构造
 * 
 * 分析:拷贝构造函数需要接收形参,会调用拷贝构造函数,而构造拷贝函数又需接收形参,还会继续调用 --
 * ---> 无限递归,因此不能使用形参来作为拷贝构造的参数
 * 解决:只需要使用引用就不会再调用构造拷贝函数了
 * 
 * 拷贝构造的使用方法:
 * Date d2(d1);    //调用拷贝构造函数来拷贝
 * Date d2 = d1;   //调用拷贝构造函数来拷贝
 * fun(d1);		   //调用拷贝构造函数来传参
 * fun(&d1);	   //调用拷贝构造函数来传参
 * Date tmp = *this; //类方法内调用拷贝构造函数来拷贝
 * 
 * 注意:Date(const Date& d){}为编译器规定的拷贝构造形式,---
 * ---> Date(const Date* d){}不是拷贝构造函数,就只是普通的构造函数
 *  
 * 拷贝构造内置类型会进行值拷贝或者浅拷贝(按字节一个一个拷memset)<--->深拷贝需要用户实现拷贝构造
 * 拷贝构造自定义类型会进行调用拷贝构造/赋值重载=== 深拷贝
 * 
 * 浅拷贝内成员指向同一块空间的问题:
 * 1.插入删除数据会互相影响,数据覆盖
 * 2.析构两次,程序奔溃:析构顺序是按栈规则来,先析构栈顶的(最后进去的)
 * 
 * 
 * 
 * 什么情况下需要实现拷贝构造？
 * ---> 自己实现了析构函数释放空间,就需要实现拷贝构造
 * 
 * 其他调用拷贝构造的情况不再存在无限递归的可能，因为拷贝构造已经实现，直接调用即可（除非用户声明的拷贝构造有问题）
 * 
 */


/*类和对象有代码未实现(日期计算)*/  //已实现,在日期类(class Date)里


//运算符重载
/**
 * 引入:C++为了增强代码的可读性引入了运算符重载,运算符重载是具有特殊函数名的函数,也具有返回类型
 * 语法:返回值类型 operator操作符(参数列表)
 * 
 * 规定:参数列表中第一个参数数为左操作数,第二个为右操作数,依次类推(极少有第三操作数)
 * 
 * 自定义类型：除了赋值运算符（天选之子），其他运算符都需要重载
 * 内置类型不需要重载：C++都已经支持（写好，内置了）
 * 
 * 不规定操作符重载一定是成员函数,也可以是全局函数(如流插入<<),有一些只能成员函数(如赋值,天选之子4)
 *  
 * 运算符重载和函数重载没有关系
 * 函数重载支持函数名相同,参数列表不同的函数可以同时使用
 * 运算符重载是让自定义类型可以使用运算符
 * 
 * 定义运算符重载:
//方式1:普通函数
bool operator==(const Date& d1, const Date& d2)
{
	return d1._day == d2._day &&
		d1._month == d2._month &&
		d1._year == d2._year;
}
int main()
{
	Date d1;
	Date d2(1,1,1);
	cout << operator==(d1, d2) << endl;
	cout << (d1 == d2) << endl;
	return 0;
} //这种方法的缺点是需要通过接口来访问成员变量(隐藏)或者公开成员变量

//方法2:定义在类方法里(好一点)
class Date
{
public:
	Date(int year = 1 , int month =1 ,int day = 1);
	bool operator==(const Date& d);  

//private:
	int _year; // 年
	int _month; // 月
	int _day; // 日
};
 * 
//使用方法:
int main()
{
	Date d1;
	Date d2(1, 1, 1);
	cout << d1.operator==(d2) << endl;  //原型
	cout << (d1 == d2) << endl;			//提高可读性,方便,编译器会自动调用原型
	return 0;
}
 * 
 * 注意:
 * 1.不能使用其他符号来创建新的操作符,如@等(不能创造新的运算符号)
 * 2.重载操作符必须有一个类类型(自定义类型)参数
 * 3.用于内置类型的运算符,其含义不能改变 ? (不能改变内置运算符)
 * 4.作为类成员函数重载时,形参看起来比操作数少1.原因是成员函数第一个参数是隐藏的this
 * 5.'.*' , '::' , 'sizeof' , '?:' , ',' 5个运算符不能重载(点心,C语言就有了,没用过,记住就好了)
 * 
 
 //自定义小于号运算符重载
	 bool Date::operator<(const Date& d)
	{
			return _year < d._year
				||_year == d._year && _month < d._month
				||_year == d._year && _month == d._month && _day < d._day;
	}

//自定义等于号运算符重载
	bool operator==(const Date& d)
	{
		return _day == d._day &&
			_month == d._month &&
			_year == d._year;
	}

//自定义其他运算符(整套:>,==,<,>=,<=,!=)只需套用两个:等于和大于小于的其中一个
	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;
	}

	bool operator>(const Date& d)
	{
		return !(*this <= d);
	}

	bool operator>=(const Date & d)
	{
		return *this > d || *this == d;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
 * 
 * 
 * 赋值运算符重载(天选之子4)
 * 
 * 赋值运算符重载格式
 * 1.参数类型：const T&，传递引用可以提高传参效率
 * 2.返回值类型：T&，返回引用可以提高返回的效率，有返回值目的是为了支持连续赋值
 * 3.检测是否自己给自己赋值
 * 4.返回*this ：要复合连续赋值的含义
 * 
 * 赋值运算符是默认构造函数,如果用户不定义编译器会自动生成  --- 因此不能在类外定义(全局函数),会冲突
 * 
 * 默认生成的赋值运算符以值的方式逐字节拷贝。内置类型成员变量是直接赋值的,
 * 
 * 注意：如果类中未涉及到资源管理，赋值运算符是否实现都可以；一旦涉及到资源管理则必须要实现。
 * 
//模板:
 	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
 * 
 * 
 * 内置类型一般不用用户实现运算符重载
 * 
 * 拷贝构造和赋值重载区别:
 * 1.定义/实例化时赋值运算符是拷贝构造
 * 2.实体对象间赋值是赋值运算符重载
 * 
 * 赋值运算符是将成员值拷贝过去,C++中一般不会直接赋值地址（引用/别名居多）
 * 
 * 还有其他运算符重载看Date类
 * 
 * 后置--/++规定参数为int ,其他报错(参数值编译器会自动传)
 * 自定义类型能用前置用前置,后置代价更大(拷贝构造调用多)
 * 
 * 流插入运算符重载:
 * 根据规定:运算符左操作数为第一个参数,右操作数为第二个参数.
 * ---> 如果流插入运算符为成员函数,则会显得不符合用户操作习惯.
 * ---> 因此,可以将流插入运算符实现成全局函数重载
 * 
 */

//const
/**
 * C语言:
 * 1.const A *p 限制p的内容不能被修改
 * 2.A const *p 限制p的内容不能被修改
 * 3.A * const p 限制指针变量p不能被修改
 * 4.const A * const p -- 上面两种结合,都不能被修改
 * 
 * 总结:
 * $ const在*的左边(无论在哪,只要在左边)就是限制*p不能被修改 -- const *p
 * $ const在*的右边,则是限制指针p不能再修改                  -- const  p
 * $ const不会影响到下下层对象,只会影响当前对象
 * 
 * 
 * 引入:
 * 1.成员函数默认隐藏的第一个参数为 'class_name *this' ;
 * 2.如果被const修饰的变量类型会变成  'const 类型名'
 * 3.const实例化有一个类,const classA a; &a的类型是const classA;
 * 
 * 
 * 问题1:可以发现,如果通过a调用成员函数,会将实参类型const classA传给隐藏形参类型classA --->
 * ---> 即权限放大.
 * 问题2:类方法隐藏参数的默认权限是不能直接修改成const classA的(不能显式修改this,底层是不能修改的)
 * (为了规范,固定隐式/显式*this是必然的,C++规定隐式)
 * 解决:在类方法名后,花括号前加上const,即 ---
 * ---> void fun() const {//...};     //修饰的是*this
 * 
 * 使用场景:形参接收引用,为防止修改,一般会加const.此时形参类的的权限就缩小成const了,---
 * ---> 如果此时调用类中的函数,如果这个函数没有被const修饰就会放大权限,报错.        ---
 * ---> 因此,需要使用const
 * 
 * 使用规范:
 * 1.声明和定义分离:声明和定义都要加
 * 2.不是成员函数不能加在函数名后面(因为此时的coust修饰的是*this,而全局函数没有*this)
 * 3.const只能是非静态成员函数时才能加到参数列表后(只能修饰成员函数,修饰*this)
 * 
 * 小结：内部不改变成员变量的成员函数,最好加上const
 * 
 * 一般不需要显式实现的默认函数(默认的够用了)
 * 1.取地址运算符函数重载(天选之子5)
 * 2.const修饰的取地址运算符函数重载(天选之子6)
 * 
 * 场景：
 * const定义的变量必须在类内初始化列表前完成初始化（因为const只有一次初始化的机会，如果类定义时没有初始化，后面就不能再改，矛盾）
 * ——const变量定义时必须初始化
 * 
 * 注意:
 * 1.如果形参需要修改,则不能加const.
 * 2.不需要修改的形参最好加上const
 * 3.const如果修饰的是对象,则整个对象都不能修改,-- const迭代器原理
 * 
 * 特点:
 * 1.const对象在初始化时没有const属性,意思是初始化时和普通对象一样,初始化后才有const属性--
 * -- 如果const直接不能修改,则根本不能初始化,const对象也没有了意义.
 * 
 */


 //const类
 /*
	const class A; //类本身是const的. 因为this就是自己的指针,则this也是const的. 即 const this
	所以,const A 的成员函数,要对外提供,都应有对应的const版本, 即func()const. //修饰this,成为const this
 
 */


//取地址运算符重载和const修饰的取地址运算符重载
/**
 * 两个都是天选之子,而且一般也没有重写的必要,自带的也够了
 * 
 * 注意:
 * 1.const跟在(参数列表)后面,表示修饰的是this
 * 2.const只能是非静态成员函数时才能加到参数列表后(只能修饰成员函数,修饰*this)
 * 
 * class Date
{ 
public :
 Date* operator&()
 {
	return this ;
 }
 const Date* operator&()const
 {
	return this ;
 }
private :
 int _year ; // 年
 int _month ; // 月
 int _day ; // 日
};
 * 
 */

//初始化列表(服务于构造函数,属于构造函数,是对象的成员定义的地方)
/**
 * 引入: 
 * 1.const修饰的局部变量必须初始化
 * 如果类中定义了const修饰的成员变量,则编译器不会处理(内置类型不做处理)
 * 
 * 2.类中写的如int a;是声明成员函数,并没有定义.一般来说,在所执行函数中的才是定义(具有分配的空间) ---
 * --- 因此,为了定义类中的成员属性,引入了初始化列表
 * 
 * 重点:
 * 一.初始化执行顺序:
 * 1.是否有缺省值(第一次赋值)  --- 缺省值服务于初始化列表
 * 2.初始化列表是否显式给出(第二次赋值)
 * 3.构造函数(第三次赋值) -- 在函数时严格而言已经不算初始化了-算赋值
 * 
 * 二.3类必须在初始化列表的成员
 * 1.const修饰的成员
 * 2.引用
 * 3.没有默认构造(写了带参数的,但没写不带参数的)  的自定义类型成员(类)
特点:必须要带参数才能初始化的类型
 * 
 *  
 * 三.一个成员只能在初始化列表出现一次,不能出现两次
 * 
 * 四.先声明先初始化:初始化顺序是声明顺序,与初始化列表顺序无关,先声明的先初始化
 * 
 * 五.初始化顺序:先声明的先初始化,初始化执行完后再到下一个声明
 * 
 * 特点:
 * 1.自定义类型会调用他的拷贝构造
 * 2.使用初始化列表时,如果不赋值,则默认为0
 * 3.不在初始化列表中的参数不会初始化
 * 4.不在初始化列表中的自定义类型成员会隐式调用默认构造函数,内置类型为随机值
 * 5.规定所有成员都会走初始化列表
 * 6.拷贝构造也有初始化列表
 * 
 * 注意:初始化列表是写在构造函数的,必经构造函数,不经过构造函数则无法使用初始化列表且缺省参数
 * 
 */


//小总结,回顾
/**
 * 1.不写构造函数和写不带初始化列表无参构造函数是一样的:因为初始化列表是所有成员定义的地方,所有成员都会经过
 * 2.初始化列表过程对内置类型不作处理,对自定义类型调用他的构造函数:所以,如果是自定义类型,一般直接声明成员即可,无需写在构造函数内
 * 3.默认生成的拷贝构造对内置类型和自定义类型都是值拷贝或浅拷贝
 * 4.默认生成的析构函数对自定义类型调用他的析构函数,对内置类型直接释放,变随机值
 * 
 */


//构造+拷贝构造+初始化列表场景
/**
* 实际上是编译器把将亡值移动构造到新对象
* 
* 关键字 explicit
* 
* 单参数隐式强制类型转换(C++98)
 * A aa1(1);  // 构造
 * A aa2 = 1; // 隐式类型转换//原理:构造(创建临时变量,1为构造参数)+拷贝构造(赋给aa1)//实际编译器优化:构造+拷贝构造->构造(一步到位)
 * const A& aa3 = 10; //证明有临时变量,临时变量有常性,去掉const红字
 * --->
 * 禁止单参数隐式强制类型转化 explicit A(int a):{};
 * 
 * 
 * 多参数隐式强制类型转换(C++11)
 * A aa1(1,1); 
 * A aa2 = {1,1};
 * const A ref& = {1,1};
 * --->
 * 禁止多参数隐式强制类型转换 explicit A(int a1,int a2):{};
 * 
 */

//编译器优化部分场景
/**
 * 一、实际编译器优化:构造+拷贝构造->构造(一步到位)
 * 1.形参
 * void fun(A a){}; 
 * A aa = 1;
 * fun(2);   //提醒:形参也是个对象,可以析构和构造
 * fun(A(2));
 * 注:fun(aa); //无优化:直接调用拷贝构造
 * 
 * 2.形参为引用
 * void fun(const A& a){}; //(const是用于fun(2)) ,无优化
 * //因为临时变量具有常性. 而此处显式的const目的是限制a的内容被修改, 而引用中的const是修饰别名不能重新绑定
 * 
 * 3.传返回值
 * A fun(){
 *     A aa;//构造
 *		return aa;//拷贝
 * }
 * fun();//无优化
 * A a1 = fun() //构造+拷贝+拷贝 => 构造+拷贝 
 * 
 * 4.当A fun(){
 *		return A();
 * }
 * fun();//构造+拷贝=>构造
 * A a1 = fun();//构造+拷贝+拷贝 => 构造
 * 
 * 建议使用场景:
 * A a = fun();
 * 
 * 不建议将定义和初始化分离,效率低,没能优化
 * A a;
 * a = fun();
 * 
 * 总结:
 * 1.接收返回值对象,尽量拷贝构造方式接收,不要赋值接收
 * 2.能接收匿名对象就尽量接收匿名对象
 * 3.传参尽量使用const 引用传参
 * 
 */

//static成员/static成员函数/静态成员/静态成员函数
/**
 * 
 * 
 * 类型 类域::变量名 = val;
 * 
 * 特点:
 * 1.所有对象共享,专属于类,只初始化一次. // 不能给缺省参数,因为静态成员不走构造函数
 * 2.属于类域,不属于全局,不属于局部
 * 3.静态方法没有隐藏参数this,和全局函数一样,没有隐藏参数
 * 4.生命周期随类
 * 5.因为没有this指针,所以函数内不能直接访问类成员 --- 解决,函数套壳把this传进去
   6.必须要在类外初始化 --- 天生就要声明与定义分离
   7.静态成员不受对象控制,只是属于类域
   8.不分公有私有,公有私有都是在全域初始化

注意
1.从 C++11 开始，非静态成员变量也可以在类内进行初始化。 (浮点数不一定可以)
    但是，这并不是在类定义时就进行初始化，而是在构造对象时进行初始化。
    如果在构造函数中也对这个成员进行了初始化，则构造函数中的初始化会覆盖类内的初始化。
2.整型类的静态const成员常量 可以在类内初始化,目的是为了能在类内直接定义栈空间的数组
class A
{
    static const int N = 1;
    int arry[N];
}

 * 
 * 注意:
 * 1.根据引申:所有访问对象的操作,都是通过this来完成的.即:先到类,然后通过this再去找对象.
 * --> () static函数内不能有非静态成员.(访问非静态成员必须有this)
 * 2.静态成员不能给缺省参数(缺省参数是给构造函数的初始化列表使用的,静态不走构造,静态成员必须要在类外初始化)
 * 
 * 场景:
 * 1.统计类被实例化的次数:使用类域计数器最安全
 * class A{
 *   private: 
 *	   static int conut; //声明 
 * }
 * int A::count = 0;//定义+初始化(介于全局与局部间:类域) //静态成员的初始化 -- 不分公有私有,公有私有都是在全域初始化
 * int main(){
 *	 A aa1 = 1;
 *   A *ptr = nullptr;
 * }
 * 
 * 2.打印:
 * int main{
 * //非私有成员下打印方式
 *   cout << A::count << endl; //类域可以找到(没有隐藏)
 *	 cout << aa1.count << endl;
 *   A *ptr = nullptr;
 *   cout << ptr->count << endl;  //static在公共区,访问公共区,与对象无关
 *   
 * }
 * 
 * 3.访问私有静态成员  -- 通过静态方法
 * A::static int getCount(){
 *   return count;
 * }
 * int main(){
 *   A.getCount();//通过类名调用
 *	 A::getCount();//通过寻找类域调用
 * }
 * 
 * 
 * 
 */
//静态与非静态对比
//https://blog.csdn.net/iii_am_haomiaozi/article/details/128902224

//静态对象/static对象
/*
静态变量/对象的生命周期为整个程序运行,所以在程序快结束前(main函数return之后),OS会delete 静态对象,调用析构函数释放资源,然后销毁静态对象,

静态对象和静态成员几乎一样,静态成员对象不受对象控制

*/

//静态全局函数/static全局函数/静态函数/static函数
/*
	只能在文件所在的编译单位内使用，不能在其它编译单位内使用。
*/



//匿名对象
/**
* 语法:
* 类名();
* //A();
* 
* 
 * 特点:
 * 1.生命周期只有所在的行
 * 2.延长生命周期：通过const T& xx = T(); //--->
 * --->const引用可以延长生命周期,将匿名对象的生命周期和xx的生命周期同等 --可以延长匿名对象的生命周期至函数执行完毕!
 * 3.具有常性,所以T&不行,VS2013支持是bug,VS2019不行
 * 
 * 场景:
 * 1.不想实例化带命名的对象时(一次性,偷懒,好看,强迫症,二维vector);
 * cout<< A().func() <<endl;
 * 
 * 正常函数和仿函数的匿名对象写法区别:
 * $ 正常:    D(构造参数列表);
 * $ 仿函数   D(构造参数列表)(()函数重载参数列表)
 * .
 */


//友元函数
/**
 * 有时提供便利,有时破坏封装,增加耦合
 * 
 * 友元声明:
 * friend 函数声明;
 * 
 * 
 * 
 * 特点:
 * 1.友元函数不是成员函数 
 * 2.可以放在类的任何位置(效果一样)
 * 3.友元函数可以访问类的所有成员,包括私有成员和保护成员
 * 
 * 特性:
 * 1.友元关系是单向的,我是你的友元,但你不一定是我的友元(我可以访问你,但你不一定能访问我)
 * 2.友元关系不具有传递性:A->B , B->C !=> A->C 
 * 3.友元关系不能继承!!!
 */

 
//友元类
/**
 * 
 * 友元类的所有成员函数都是另一个类的友元函数，都可以访问另一个类中的隐藏信息（包括私有成员和保护成员）。
 * 当希望一个类可以存取另一个类的私有成员时，可以将该类声明为另一类的友元类。定义友元类的语句格式如下：
 * friend class 类名;
 * 
 * 
 */


//内部类(在类里面再定义一个类)
/**
 * 实际上定义在类内和全域内没什么区别,跟A是独立的,只是受到了类域的限制(权限和作用域)
 * 
 * 特点:
 * 1.天生就是外部类的友元 -- 可以访问外部类
 *
构造函数和析构函数调用的顺序，先调用内部类的构造方法然后再调用外部类的构造方法，
对于析构方法的调用顺序是相反的，先是外部类析构方法调用，然后再是内部类析构方法的调用

先构造的后析构 --- 栈

先构造父类,再构造内部类,之后才是构造外部类. -- 先有父,然后有内,再有外
	因此:先析构外部类,再析构内部类,再析构父类

	不用担心析构外部类时会把内部类干掉,因为析构的是资源而不是自己,自己(栈上的)是编译器负责释放的,只有出了作用域才会释放
 
 */



 //C++内存管理
 /**
  *
  *
  * .
  */

//操作符new和delete  -- 引入
/**
 * 
 * 
 * [与C语言对比
 * 1.开辟一个空间
 * int* p1 = (int*)malloc(sizeof(int));
 * int* p2 = new int;
 * free(p1);
 * delete p2;
 * 
 * 2.开辟多个空间
 * int* p1 = (int*)malloc( 10 * sizeof(int));
 * int* p2 = new int[10];
 * (可以new int[0])
 * free(p1);
 * delete[] p2;
 * 
 * 从C语言的malloc对比来看,new和C语言的malloc基本一样,且都没有对 !基本类型! 进行初始化
 * ]
 * 
 * 特点:C++的new主要是在自定义类型上有新功能,为类服务
 * 1.new会调用自定义类型的构造函数,比malloc多...
 * 2.delete会调用析构函数(比free多了调用析构函数,free是只释放当前空间)
 * 3.出问题会抛出异常,而不返回空指针,所以不需要像malloc 一样空指针检查.
 * 
 * 场景
 * A a = new A(参数);
 * 
 * 带初始化和不带初始化
 * int *p1 = new int; //申请一块内存,不会初始化  
 * int *p1 = new int(0);// 申请一块内存,并初始化成0
 * int *p1 = new int[10]{1,2,3,4}//申请10个int空间,并将一次初始化成1,2,3,4,0,0,0,0,0,0;没给值的初始化成0
 * 
 * 
 * 什么时候需要使用使用delete或free
 * 1.Stack st;  // 不需要使用,因为st自定义类型的对象,作用域结束后会自动调用析构函数
 * 2.Stack *pst;// 需要手动使用,因为pst是内置类型(指针),作用域结束后不会自动调用析构函数->内存泄露
 * 
 * 
 * 注意:
 * 1.原则上能匹配尽量匹配,不要交叉使用,以免发生内存泄露
 * 2.必须使用delete的场景(VS编译器):
 * A *a = new A[1];
 * delete[] a; //必须使用带[]的delete,其他的会报错,原因:--->
 * --> 在new数组时,编译器会在首地址的前面再开辟一个小空间用于存放数组个数(用于告诉VS要调用多少次析构函数,没有其他目的),
 * --> 即实际空间大于申请空间.所以free和delete a;释放free的实际位置不对,会报错
 * --> delete[]会往前减掉一个空间的字节,再读出这个字节的数据,然后根据数据进行析构(10),然后再从前一个位置开始释放(11)
 * 
 * 3.如果2情况下,自定义类型没有写析构函数,那编译器就会认为无所谓,就没必要回偏再开辟一个小空间,此时free和delete都不报错
 * (开小空间的目的就是为了告诉delete[]要调用多少次析构函数)
 */



//operator new函数 和 operator delete函数
/**
 * new 和 delete 是用户进行动态内存申请和释放的操作符
 * operator new 和 operator delete是库里面提供的全局函数,不是new 和delete的重载,delete和new是操作符,前者是函数
 * 
 * new和delete都是在底层调用operator
 * 
 * operator new和delete 实际上是 malloc 和free的封装
 * 
 * .
 */

//placement-new 定位new :对已有空间进行初始化
/**
 * 
 * 
 * 
 * 语法
 * new(对象)构造函数;
 * 
 * $ p1是对象的指针,A是构造函数
 * 
 * new(p1)A;   //无参构造函数
 * new(p1)A(1) //带参构造函数
 * 
 * 场景:
 * 1.用于在malloc或operator new后的没有初始化的情况下,主要存在于向内存池申请(更快) -- 介于堆之间,缓冲作用
 * .
 */

//显式析构函数
/**
 * p1->~A(); //显式调用析构函数
 * free(p1);
 * 
 * .
 */


 

 