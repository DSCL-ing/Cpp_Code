#pragma once

//ifstream等都是basic_ifstream的别名
//using ifstream = basic_ifstream<...>;

//using ios = ios_base ...

//文件创建
/*
ofstream(filename); //创建名为filename的文件

*/

//文件读写
/*
1.头文件简介
ofstream:打开文件写操作
ifstream:打开文件读操作
一般直接用fstream,可读可写 
...

2.打开文件
2.1打开方式
mode:
//以ascii方式打开
ios::in  读方式打开文件
ios::out 写方式打开文件 (也具有创建功能)
ios::app 追加方式打开文件
ios::ate 打开已有文件,文件指针在文件末尾
ios::trunc 文件不存在的情况下具有创建功能,一般以ios::trunc|ios::in
ios::nocreate 不创建方式
ios::noreplace 不替换方式,清除
// 以二进制方式
ios::binary

//缺省值是 ios::in|ios::out  ,即可读可写

2.2判断文件打开是否成功
    1.流对象!运算符和bool运算符重载  if(!fstream) ? 打开失败 : 打开成功
    2.流对象fs.is_open()  true成功,false失败
3.关闭文件
    流对象.close()

4.文件读写
    4.1.以流插入方式写入
    fp<<"str1"<<"\t"<<"str2"<<;
    4.2.流提取
    fp>>buffer1>>buffer2; //默认文件指针从头开始,以空格为分隔符
    
    4.3. 字符流
    char key;
    fs.get(key); //读fs中的一个字符到key中,指针后移
    fs.put(key); //像fs中写入一个key,指针后移

    4. 4 二进制
    char str[100] = "";
    fs.read(str,8);//读fs中8个字符到str
    fs.write(str,9); //将str中的前9个写到fs

5.文件指针
流对象fs.eof() //文件结束标志

ifstream
    seekg(long int pos);
    seekg(long int pos,ios_base::seekdir begin); //把begin移动到pos
ofstream
    seekp(long int pos);
    seekp(long int pos,ios_base::seekdir begin);//把begin移动到pos
begin(枚举类):
    ios::beg 开始位置
    ios::end 结束位置
    ios::cur 当前位置

6.其他
std::noskipws //no skip word space 不跳过间隔(符)
fs>>std::noskipws>>(char*)buffer;  //即先读到noskipws,并且把空格\换行也读了进来,然后传给buffer.这样就能保持读的数据一致
//string需要测试,有特性


//指针和数组下标一样,从0开始,pos是下标
*/


//stringstream
/*
有自动类型转换特性...

*/


//manipulators 操纵符
/*
https://zh.cppreference.com/w/cpp/io/manip
https://legacy.cplusplus.com/reference/ios/


*/

