#pragma once

//搜索关键字
/**
 * C++未做:没有用C++实现的题
 * .
 */

//力扣注意事项:
/**
 * 1.力扣接口型题目是按一定规范提供结构,有些参数对题目意义不大.用于维护规范而提供,按规范完成好即可
 * C语言接口涉及二维数组时,会提供一些输出型参数(需要输入数据,但无需返回,因为是指针,传址传参)
 * 1.int* returnSize 2.int** returnColumsSizes.
 * 这两个参数类型是指针,目的是传址以达到能修改原数据的目的.一维数组需要传二级指针,实体类型需要传1级指针才能修改原数据.
 * c语言二维数组动态开辟方式:
 * int** pp = (int**)malloc(sizeof(int*)* numRows)
 * 然后,for(int i = 0;
 *		*(pp+i) = (int*)malloc(sizeof(int)*n);
 * //...
 * 
 * 
 * 2.设计好测试用例的题目尽可能要充分输入数据,测试用例和正常逻辑实现不一样
 * 如:"最小栈"
 * 
 * 3.尽可能学习如何画图辅助做题
 * 
 */




//题目:求1 + 2 + 3 + ... + n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A ? B : C）。
//https://www.nowcoder.com/practice/7a0da8fc483247ff8800059e12d7caf1?tpId=13&tqId=11200&tPage=3&rp=3&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
//知识点:静态成员和静态方法的使用	


//题目:给定一个字符串 s(小写字母) ，找到 它的第一个不重复的字符，并返回它的索引 。如果不存在，则返回 - 1 。
//https://leetcode.cn/problems/first-unique-character-in-a-string/submissions/
//知识点:string开胃菜

//计算字符串最后一个单词的长度，单词以空格隔开
//https://www.nowcoder.com/practice/8c949ea5f36f422594b306a2300315da?tpId=37&&tqId=21224&rp=5&ru=/activity/oj&qru=/ta/huawei/question-ranking
//知识点:string的find和获取字符串


//给你一个字符串 s ，根据下述规则反转字符串：
//所有非英文字母保留在原有位置。
//所有英文字母（小写或大写）位置反转。
//返回反转后的 s 。
//https://leetcode.cn/problems/reverse-only-letters/
//知识点:string[]


//超大数相加
//给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和并同样以字符串形式返回。
//https://leetcode.cn/problems/add-strings/submissions/
//知识点:string::reserve,reverse,


//只出现一次的数字
//https://leetcode.cn/problems/single-number/submissions/
//知识点:for-auto,vector<int>


//杨辉三角
//https://leetcode.cn/problems/pascals-triangle/submissions/
//知识点:二维vector , resize , 或二维数组


//电话号码的字母组合
//https://leetcode.cn/problems/letter-combinations-of-a-phone-number/submissions/
//知识点:DFS,树,vector,递归,string



//最小栈
//https://leetcode.cn/problems/min-stack/submissions/
//知识点stack的使用


//是否是同一组栈的压入、弹出序列
//https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&&tqId=11174&rp=1&ru=/activity/oj&qru=/ta/coding-interviews/question-ranking
//知识点:stack的使用,stack的特性


//逆波兰表达式求值
//https://leetcode.cn/problems/evaluate-reverse-polish-notation/submissions/
//知识点：stack,运算后缀表达式
//扩展:从中缀表达式转成后缀表达式(定位:stack queue)


//用栈实现队列
//https://leetcode.cn/problems/implement-queue-using-stacks/
//C++未做,stack和queue

//用队列实现栈
//https://leetcode.cn/problems/implement-stack-using-queues/
//C++未做 , stack和queue
