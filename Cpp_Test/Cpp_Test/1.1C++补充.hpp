﻿#pragma once


//C++中的类型转换static_cast、dynamic_cast、const_cast和reinterpret_cast


//C++中const类--->类所有成员都不能修改,比方string
//	但是类内指向的堆空间呢?


//通常说的返回值,返回临时对象,比较小的一般存放在寄存器中,也可能是其他
    // 比较大,如类,结构体等的通常放在上一层栈帧(调用栈),如main中调用func,func返回的临时对象就放在main函数栈帧内.所以销毁不影响返回的值


/*
C++的访问修饰符的作用是以不同的类为单位
私有是为了实现“对外”的信息隐藏，或者说保护，在类自己内部 ,允许访问同类型的私有变量,但不能访问其他类型的私有成员
*/





