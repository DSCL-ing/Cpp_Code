# 基本语法认识

## 认识CMakeLists.txt

CMakeLists.txt被拆分成4部分,前3部分注意要大写,以防跨平台时无法识别(特别是linux,只认识CMakeLists.txt)

C

Make

Lists

.txt



## cmake执行CMakeLists.txt命令 



- cmake dir[CMakeLists.txt所在目录]   

  表示在运行cmake所在的路径下,根据dir找到并执行CMakeLists.txt,并将执行的结果放置到运行cmake所在目录.

  例如: [\home\user\test]# cmake .

  该命令表示在test目录下找到并执行CMakeLists.txt,并将执行结果放置到当前目录(test).

  但是这样执行存在目录污染的问题,即源代码目录中出现了额外的构建文件;如果需要清理这些构建文件,则会很困难.

  为了解决目录污染问题,我们采用另一种cmake方式

  \# md/mkdir build   //创建一个目录build,win10中创建目录的命令是md

  \# cd build		 //进入build目录

  \# cmake ../        //在上级目录寻找CMakeLists.txt,然后在当前目录执行CMakeLists.txt

  这样做的好处是避免了目录污染,不需要构建文件时可以直接将build目录删除掉,并不影响源代码.

- cmake -S source_dir -B build_dir

  其中-S表示source,表示后面是CMakeLists.txt所在路径,-B表示build,表示后面的是构建生成的路径.

  其中-B 后面的目录是cmake自动创建的,不需要我们手动创建.

  ​    cmake -S . -B build //该命令和"mkdir build;cd build;cmake ../"的效果是一样的.

- -G "编译方式"

  -G 指定编译器,生成相应的MakeFile文件

  Exam:`cmake -S . -B g -G "MinGW Makefiles"E`



## CMake统一的编译方法

- cmake --build construct_dir 

  constructor_dir 是执行CMakeLists.txt生成的构建文件所在路径.会将编译好的文件合并到construct_dir 中

  

- -j线程数

  -j是启用多线程编译,后面跟着多线程数

  搭配ninja才好使,否则可能出现不如单线程的情况



- --config <release或debug> 

  生成dubug版本或者release版本





## CMake install (安装)

- cmake --install construct_dir 

  默认安装的是release版本,其他版本需要配置



## CMake 文件

标准名称: CMakeLists.txt

CMakeLists.txt本身大小写不敏感,满足跨平台特性.

最好按标准名称写,可读性更好.在敏感大小写的平台,不同名称可能是不同的文件.



## CMakeLists.txt编写

### 指定CMake最小版本

- cmake_minimum_required(VERSION 3.20)

  minimum:最低

  requird:需求

  3.20: 最低支持的版本,表示3.20.0. 还可以写成3.20.1,指定更细版本

  cmake_minimum_requird用于表示支持的cmake最低版e本,以防使用高级版本新特性时,不兼容,无法得知bug原因等

### 指定构建项目的名称

- project(项目名称)

  CMake语法中项目名称不需要加"",虽然他是字符串



### 添加构建对象

源文件相对路径以CMakeLists.txt为起始

#### 可执行文件

- add_executable(项目名称 源文件)

  `add_executable(xlog xlog.cc xlog.h)`

- add_executable(项目名称 源文件 库)

  `add_executable(xlog xlog.cc xlog)`

#### 库

- add_library(库名 STATIC/SHARED 依赖/源文件)

  如果是静态库,需要显示指明STATIC

  `add_library(xlog STATIC xlog.cc xlog.h) //放入xlog.h目的是让xlog.h被修改也能重新编译`

  如果是动态库

  `add_library(xlog ARED xlog.cc xlog.h)`

  或`add_library(xlog xlog.cc xlog.h)` //缺省



### 指定路径

#### 指定查找的头文件所在路径

- include_directories("头文件所在路径")

  include_directories("../xlog")



#### 指定库查找路径

不同平台中,cmake生成库的路径可能不一样,cmake能够一定情况下自动查找(同属于cmake --build生成)

windows中vs会生成../Debug/ 或../Release,在大部分情况都能够查找

- link_directories("库所在路径")

  link_directories("../xlog/build")

  

#### 指定库(分离)

- target_link_libraries(项目名称 库名)

  target_link_libraries(test_xlog xlog)

  > 注意: 
  >
  > 1.target_link_libraries需要在add_executable/add_library下方.
  >
  > 2.库名没有lib,.so,.lib这些





## Windows平台特性说明

- 动态库在windows平台需要导出.lib文件,需要使用微软提供的宏`__declspec()`.`_WIN32`

decl:declaration; spec:specifier; --- 大意为声明限定符

导入:`__declspec(dllimport)`

导出:`__declspec(dllexport)`

标识:`_WIN32`; _WIN32包含32位和64位

- 跨平台容易出现编码问题,可以使用utf8 with BOM



## 示例

linux工具 

ldd, echo $LD_LIBRARY_PATH,



### xlog

CMakeLists.txt

```
cmake_minimum_required(VERSION 3.20)

project(xlog)

include_directories(xlog)

add_library(xlog SHARED xlog/xlog.cc)

add_executable(test_xlog test_xlog/test_xlog.cc xlog)

target_link_libraries(test_xlog xlog)
```

xlog.h

```
//xlog.h

#ifndef XLOG_H
#define XLOG_H


//仅动态库 --动静态库由CMakeLists.txt设置,在后续..
#ifdef _WIN32 //WIN32环境
    #ifdef XLOG_EXPORTS //需要导出(动态库)
        #define XCPP_API _declspec(dllexport)
    #else  //否则导入
        #define XCPP_API _declspec(dllimport)
    #endif
#else  //linux mac环境
    #define XCPP_API //非WIN32环境则为空
#endif


class XCPP_API Xlog{
    public:
       Xlog();
};
#endif
```

xlog.cc

```
//xlog.cc

#include<iostream>
#include"xlog.h"
Xlog::Xlog(){
  std::cout<<"Xlog()"<<std::endl;
}
```



