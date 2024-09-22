# 通信服务器和客户端实现。
> 此项目服务器基本框架为 网络层、 服务层、 数据存储层 <br>
> 网络层采用的是开源的muduo网络库，是基于非阻塞IO和事件驱动的C++高并发TCP网络库，该网络库很好的解耦了网络模块和业务模块的代码。<br>
> 服务层这里使用C++11的技术，例如绑定器、std::map、auto等<br>
> 数据存储层，使用MYSQL数据库对项目中的一些重要的数据进行落地存储，比如用户账号密码，好友列表，离线消息。<br>
> 拓展：多机的扩展，部署多台网络服务器快速提升项目并发能力。

# 技术相关
+ Json序列化和反序列化
+ muduo网络库开发
+ nginx的tcp负载均衡器配置
+ 基于发布-订阅的服务器中间件redis消息队列编程实践
+ MySQL数据库编程
+ CMake构建编译环境 

## 编译方式：
1. + 清空build目录   rm -rf ./build
   + 进入build目录   cd build
   + 利用上级目录中的CMakeLists.txt生成构建文件    cmake ..
   + 自动编译和构建程 make
2.  或者直接使用 shell脚本 AutoBuild 自动执行

## 环境相关
+ 编译器：GCC 11.4.0
+ 编程语言：C++
+ 开发环境：Ubuntu 22.04.4 LTS vscode


> ## 运行方式：
>服务器端运行：
> 运行bin目录下生成的ChatService可执行文件 参数 IP地址 端口号
> 
> ![image](https://github.com/user-attachments/assets/6977b6b6-0d99-4fb8-9aac-51089fe3e029)
> 客户端运行
> 运行bin目录下生成的ChatClient可执行文件 参数 IP地址 端口号(默认为8000，nginx服务默认监控端口)
>
> ![image](https://github.com/user-attachments/assets/d653b0bc-1ae4-469d-9187-fb04d04e524e)


# 效果展示

![image](https://github.com/user-attachments/assets/f8252e66-f93a-4eec-b073-c59dd9a38c7c)

![image](https://github.com/user-attachments/assets/c928dc4c-9b9d-4049-b79c-9a6e34eaf3a9)

### json
> 使用 json 像使用 STL 容器一样 STL 和 json 容器之间可以相互转换。
> 整个代码由一个头文件组成 json.hpp，没有子项目，没有依赖关系，没有复杂的构建系统，使用起来非常方便。

### muduo
1. 高性能：
+ muduo的网络设计：reactors in threads - one loop per thread
+ Muduo库采用了多线程的设计，可以充分发挥多核处理器的性能，从而在处理大量并发连接时表现出色。
+ 使用非阻塞IO模型和事件驱动的异步编程模型，避免了传统阻塞IO模型中的线程阻塞问题，提高了系统的吞吐量和响应速度。
2. 异步编程模型：
+ Muduo库基于Reactor模式，通过事件驱动和回调机制高效处理网络事件，简化了并发网络编程的复杂度。
+ 开发者无需关心底层的IO复用和线程同步问题，可以更加专注于业务逻辑的实现。
3. 易用性：
+ Muduo库提供了简洁易懂的API接口，方便开发者快速上手和使用。

### MySQL数据库安装
> 本项目默认使用root 用户 密码：123456 。如要修改文件如下src/serve/db/db.cpp
> 
> ![image](https://github.com/user-attachments/assets/a1050477-0983-45e9-8a68-6d6cfcb495c1)
 

### nginx
>1.9版本开始以后，nginx开始支持tcp的长连接负载均衡，但是 nginx默认并没有编译tcp负载均衡模块。 nginx编译加入--with-stream参数激活tcp负载均衡模块
> 相关配置
> 
> ![image](https://github.com/user-attachments/assets/370e6aae-96aa-4f39-bf15-dd7c825418fe)
 
### redis
> 目的：使用redis的发布-订阅机制实现不同服务器进行信息通信，避免所有的服务器进行硬链接的开销。

  
# 参考文献
[1] 施磊．集群聊天服务器．图论科技.2020.7．









