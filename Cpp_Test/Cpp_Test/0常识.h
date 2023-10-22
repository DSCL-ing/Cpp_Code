﻿#pragma once

//windows在识别文件时不区分大小写 --- #include时大写小写有时无所谓

//32位无符号最大整数为42亿字节左右 -- 2^32-1

//常规最大数据量为40亿个无符号整型左右

//1G = 2^10M = 2^20^K = 2^30B = 8*2^30bit = 10亿字节

//INT_MAX只有20多亿

//求最大整型方法:1.size_t( -1) 2.0xFFFFFFFF -- 限32位--4字节整型

//65535 = 2^16 = 2^10 * 2^6 = 1024 * 64

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
*/