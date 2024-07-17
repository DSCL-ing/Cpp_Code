## cmake执行CMakeList.txt命令 



- cmake dir[CMakeList.txt所在目录]   

  表示在运行cmake所在的路径下,根据dir找到并执行CMakeList.txt,并将执行的结果放置到运行cmake所在目录.

  例如: [\home\user\test]# cmake .

  该命令表示在test目录下找到并执行CMakeList.txt,并将执行结果放置到当前目录(test).

  但是这样执行存在目录污染的问题,即源代码目录中出现了额外的构建文件;如果需要清理这些构建文件,则会很困难.

  为了解决目录污染问题,我们采用另一种cmake方式

  \# md/mkdir build   //创建一个目录build,win10中创建目录的命令是md

  \# cd build		 //进入build目录

  \# cmake ../        //在上级目录寻找CMakeList.txt,然后在当前目录执行CMakeList.txt

  这样做的好处是避免了目录污染,不需要构建文件时可以直接将build目录删除掉,并不影响源代码.

- cmake -S source_dir -B build_dir

  其中-S表示source,表示后面是CMakeList.txt所在路径,-B表示build,表示后面的是构建生成的路径.

  其中-B 后面的目录是cmake自动创建的,不需要我们手动创建.

  cmake -S . -B build //该命令和"mkdir build;cd build;cmake ../"的效果是一样的.



## CMake统一的编译方法

- cmake --build construct_dir 

  constructor_dir 是执行CMakeList生成的构建文件所在路径.会将编译好的文件合并到construct_dir 中

  

- cmake --build construct_dir  [-j线程数]

  -j是启用多线程编译,后面跟着多线程数

  搭配ninja才好使,否则可能出现不如单线程的情况



- cmake --build construct_dir --config <release或debug> 

  生成dubug版本或者release版本



## CMake安装

- cmake --install construct_dir 

  默认安装的是release版本,其他版本需要配置
