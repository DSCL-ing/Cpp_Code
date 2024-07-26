﻿# 基本语法认识

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

- add_library(库名 STATIC/SHARED/... 依赖/源文件)

  > 动静态库等由内建变量BUILD_SHAERD_LIBS决定,默认是静态

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



### 示例

linux工具 

ldd, echo $LD_LIBRARY_PATH,



#### xlog

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



## CMake注释

注释:预处理阶段会清除掉的文本

### 行注释

行注释:一行中#号之后(包括#)的所有内容都是注释

Exam:

```
# CMakeLists.txt

cmake_minimum_required(VERSION 3.20) #表示cmake最低需要的版本号
```



### 括号注释

cmake3.0开始

语法: #[[  注释内容 ]]

Exam: 

```
```





## message

### 基本使用

语法: message(arg1 arg2 arg3 ...)

```
//CMakeLists.txt
cmake_minimum_required(VERSION 3.20.1)

message("参数1")
message("参数1" "参数2" "参数3")
message("你 好" 111 你 好)
message(需要加特殊字符,如 "空 格" 时,用双引号围起来,否则会自动去掉空格和自动拼接)
message(使用双引号时,两边要加"空格",否则双引号也会输出)

project(first_cmake)

add_executable(first_cmake main.cc)
```

![image-20240721193707231](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240721193707231.png)





### 高级用法

#### 指定日志级别 :

message([\<mode\>] "message text" ...)

--log-level=<ERROR|WARNING|NOTICE|STATUS|VERBOSE|DEBUG|TRACE>

显示级别为最高级别到指定的低级别.不在范围内的更低的级别则不会显示.

#### 日志级别:

FATAL_ERROR级别最高,越往下越低

|     FATAL_ERROR     |     停止cmake运行和生成      | stderr |
| :-----------------: | :--------------------------: | :----: |
|     SEND_ERROR      |    cmake继续运行,生成跳过    | stderr |
|       WARNING       |             警告             | stderr |
|  (none) or NOTICE   |             通知             | stderr |
|       STATUS        |   项目用户可能感兴趣的信息   | stdout |
| VERBOSE(默认不显示) |    针对项目用户的详细信息    | stdout |
|  DEBUG(默认不显示)  | 项目本身的开发人员使用的信息 | stdout |
|  TRACE(默认不显示)  | 非常低级实现细节的细粒度消息 | stdout |
|                     |                              |        |

- FATAL_ERROR

  FATAL_ERROR:致命错误.

  当CMakeLists.txt执行到FATAL_ERROR时, cmake程序停止运行,项目生成也随之停止运行.

  ![image-20240721202859649](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240721202859649.png)

- SEND_ERROR

  发送错误

  当CMakeLists.txt执行到SEND_ERROR时,cmake程序继续运行,项目文件生成停止.即发生错误后,不需要再继续生成项目文件,也能够获取更多信息.

- WARNING

  警告,一般是小错误,但不影响项目继续生成.

  例如项目中某个库缺失或编译失败,导致少了一部分功能,但是还能够运行.

  

- (none) or NOTICE

  不写日志等级或写为notice.

  这是一般的日志等级,用于提示各种信息

- STATUS

  状态,用户可能感兴趣的消息 

  输出时会自动在消息前加上前缀 --



- VERBOSE

  (默认不显示),用户需要的详细信息

  输出时会自动在消息前加上前缀 --

  带日志等级执行(显示)

  ![image-20240721205101302](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240721205101302.png)

  不带日志等级执行(不显示)

  ![image-20240721205121448](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240721205121448.png)



- DEBUG

  (默认不显示),开发者调试常用

- TRACE

  (默认不显示),



> 1. error都会输出CMakeLists.txt文件的行号
>
> 2. STATUS以上都是默认显示的等级,VERBOSE开始往下都是默认不显示的等级
>
> 3. 重定向测试: cmake -S . -B b --log-level=VERBOSE >log.txt 2>&1
>
>    标准输出重定向到log.txt , 标准错误重定向到标准输出







## 变量

### 变量语法:

设置变量 set(\<variable\>\<value\>)

>  没有指定value,则变量会被撤销

撤销变量 unset(\<variable\>)

### 变量使用:

- 获取变量值: ${variable}

  >  如果未设置变量,则返回空字符串 

- 嵌套使用(从内向外求值): ${${variable}}

  Exam: 

  ```
  set(VAR1 "变量1的值")
  set(VAR2 "VAR1")
  message(\${VAR1}=${${VAR2}})
  ```

  ![image-20240722104135453](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240722104135453.png)

- 变量大小写敏感

- 变量可以直接在字符串中

  Exam: "${var}变量可以直接在字符串中"

- 使用转义可以得到原始$

  Exam: "\\${var}得到的是原始的\$"



### 示例:变量+message改变控制台颜色输出



### 内建变量

#### 1. 提供信息的变量

```
project(xlog)
# 提供信息的变量 PROJECT_NAME:项目名称 -- 对应project的值
```



#### 2. 改变行为的变量

```
# BUILD_SHARED_LIBS,ON动态库,OFF静态库,默认OFF
set(BUILD_SHARED_LIBS OFF)
# BUILD_SHARED_LIBS还属于缓存变量

# cmake传递变量给C++
add_definitions(-Dxlog_STATIC) #默认值为1
```

##### 搭配跨平台代码例程

```
//xlog.h
#ifndef XLOG_H
#define XLOG_H

#ifdef _WIN32 //WIN32环境
    #ifdef xlog_STATIC //如果是静态库 XLOG_STATIC为用户定义
        #define XCPP_API //不需要导出导入
    #else
        #ifdef xlog_EXPORTS //需要导出(动态库) -- 动态库时,CMake会自动生成xx_EXPORTS变量
            #define XCPP_API _declspec(dllexport)
        #else  //否则导入
            #define XCPP_API _declspec(dllimport)
        #endif
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







#### 3. 描述系统的变量

```
# 描述系统的变量
message("MSVC = " ${MSVC})
message("WIN32 = " ${WIN32})
message("UNIX = " ${UNIX})
message("CMAKE_SYSTEM_NAME = " ${CMAKE_SYSTEM_NAME})
# ANDROID
```

windows:

![image-20240722230737463](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240722230737463.png)

linux:

![image-20240722230820744](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240722230820744.png)



#### 4. 控制构建过程的变量

```
# 控制构建过程的变量 输出路径控制 CMAKE_COLOR_MAKEFILE:makefile执行过程是否有颜色,默认ON
set(CMAKE_COLOR_MAKEFILE OFF)
# 效果:make执行过程不再显示颜色
```







## include

//CMakeLists.txt

```
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project("cmake_include")

message("begin include")

# cmake中的 include 和C/C++中的include类似,都是直接把文件内容直接拷贝到当前文件.多次引用多次复制
include("cmake/test_cmake.cmake")
include("cmake/test_cmake.cmake")

include("cmake/test_cmake1.cmake" OPTIONAL) #OPTIONAL选项,表示可选,当文件不存在时不报错.

include("cmake/test_cmake1.cmake" OPTIONAL RESULT_VARIABLE ret)
message("ret = ${ret}") #ret = NOTFOUND

include("cmake/test_cmake.cmake" OPTIONAL RESULT_VARIABLE ret)
message("ret = ${ret}") #ret = NOTFOUND

message("end include")
```



// ./cmake/test_cmake.cmake

```
message("in cmake/test_cmake.cmake")
```

![image-20240723144831924](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240723144831924.png)





## 自动搜索源文件

//CMakeLists.txt

```
#[[
项目目录层次结构
主目录
    CMakeLists.txt
    main.cc
    src/
        xlog.cpp
        xthread.cc
        xtest.c
    include/
        xlog.h
        xthread.hpp
]]

cmake_minimum_required(VERSION 3.20)

project("auto_add_source")

# 自动找到目录下源码文件,写入到变量中
aux_source_directory("." M_SRC)
aux_source_directory("./src" SRC)

include_directories("./include")

# 读取头文件, 写入到HDR_LIST中
file(GLOB HDR_LIST "include/*.h" "include/*.hpp")

add_executable(${PROJECT_NAME} ${M_SRC} ${SRC} ${HDR_LIST})
```







## CMake分步编译和清理

注意,只有指定生成makefile文件才具有此步骤;Win中需要使用nmake,MSVC不支持



- 分布编译

```
cmake --build b --target help
```

![image-20240723202713903](C:/Users/chj/Desktop/Repository/Cpp_Code/Cpp_Test/Cpp_Test/CMake.assets/image-20240723202713903.png)

指定.i可以得到预处理文件,指定.s可以得到编译后的汇编文件, 指定.o(win中为.obj)可以得到汇编后的二进制文件.



- 清理

```
cmake --build b --target clean
```

效果和make clean类似.





## CMake调试启用:打印具体的代码执行/生成指令

- 方式1,加命令选项,最常用

```
cmake --build b -v //或者--verbose
```

- 方式2 配置内建变量

  ```
  #显示详细的生成日志,默认是OFF
  set(CMAKE_VERBOSE_MAKEFILE ON)
  ```



## CMake设置输出路径

```
cmake_minimum_required(VERSION 3.20)

project(xlog)

include_directories(xlog)

message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# CMAKE_LIBRARY_OUTPUT_DIRECTORY : linux动态库.so和mac动态库输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")

# CMAKE_ARCHIVE_OUTPUT_DIRECTORY : windows静态库.lib  windows动态库.lib文件 linux静态库.a文件
# 一般库输出路径都设置成相同的,除非特别需要区分
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")


# CMKAE_RUNTIME_OUTPUT_DIRECTORY : 执行程序 windows动态库dll文件 输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")


# 改变行为的变量 BUILD_SHARED_LIBS,ON动态库,OFF静态库,默认OFF
set(BUILD_SHARED_LIBS OFF)

# cmake传递变量给C++
add_definitions(-Dxlog_STATIC) #默认值为1


# add_library(xlog xlog/xlog.cc)
# add_executable(test_xlog test_xlog/test_xlog.cc xlog)

# 添加子项目目录(主目录项目配置,子目录构建项目) -- 每个子项目必须包含CMakeLists.txt文件
add_subdirectory(xlog)
add_subdirectory(test_xlog)


target_link_libraries(test_xlog xlog)
```





## CMake常用模板

```
#CMakeListt.txt

# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# 添加头文件目录
include_directories(include)

# 收集源文件
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" "include/*.hpp")

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 添加库（如果适用）
# add_library(MyLibrary STATIC src/library/*.cpp)
# target_include_directories(MyLibrary PUBLIC include)

# 链接库到可执行文件（如果适用）
# target_link_libraries(${PROJECT_NAME} PRIVATE MyLibrary)

# 添加编译定义
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")

#-------------------------------------------------------------------------
# 设置编译器警告级别
if(MSVC)
    add_compile_options(/W4 /MP)
elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# 添加外部依赖项（如果适用）
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(PC_SOME_PKG some_pkg)
# include_directories(${PC_SOME_PKG_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} ${PC_SOME_PKG_LIBRARIES})
# -------------------------------------------------------------------------
# 注释
# cmake_minimum_required() 确保 CMake 版本满足项目需求。
# project() 定义项目名称、版本和使用的语言。
# set(CMAKE_CXX_STANDARD ...) 设置 C++ 标准版本。
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ...) 设置输出目录。
# include_directories() 设置头文件的包含路径。
# file(GLOB ...) 收集源文件和头文件。
# add_executable() 创建可执行文件。
# add_library() 和 target_link_libraries() 用于创建和链接库（如果项目中包含库）。
add_definitions() 添加编译时的预处理器定义。
add_compile_options() 设置编译器选项。
# find_package() 和 pkg_check_modules() 用于处理外部依赖项。
```



