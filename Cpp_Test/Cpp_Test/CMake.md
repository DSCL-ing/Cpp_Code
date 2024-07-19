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

 cmake_minimum_requird用于表示支持的cmake最低版e本,以防使用高级版本新特性时,不兼容,无法得知bug原因等

### 指定构建项目的名称

- project(项目名称)

  CMake语法中项目名称不需要加"",虽然他是字符串



- add_executable(项目名称 源文件)

- add_library(库名 类型 依赖)

  add_library(xlog STATIC xlog.cc xlog.h) //放入xlog.h目的是让xlog.h被修改也能重新编译



