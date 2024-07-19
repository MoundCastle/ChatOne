# 聊天服务器和客户端实现，使用nginx tcp进行负载均衡，基于muduo实现，使用redis消息队列，数据库使用mysql。

## 编译方式：
1. + 清空build目录   rm -rf ./build
   + 进入build目录   cd build
   + 利用上级目录中的CMakeLists.txt生成构建文件    cmake ..
   + 自动编译和构建程 make
2.  或者直接使用 shell脚本 AutoBuild 自动执行

## 用到的相关环境

### nginx
> nginx编译加入--with-stream参数激活tcp负载均衡模块
> 相关配置
> 
> ![image](https://github.com/user-attachments/assets/370e6aae-96aa-4f39-bf15-dd7c825418fe)
 
### redis
> redis支持多种不同的客户端编程语言，C++对应的则是hiredis。自行安装拷贝生成的动态库到/usr/local/lib目录下！
> 目的：使用redis的发布-订阅机制实现不同服务器进行信息通信，避免所有的服务器进行硬链接的开销。

### muduo
> 基于muduo的客户端服务器编程
> 完成服务器和客户端程序开发，基于muduo库的TcpServer和TcpClient更便捷。
> 进行线程管理，muduo库提供的ThreadPool线程池管理类已经把Linux的线程创建完全封装起来了。

### MySQL数据库安装
> 本项目默认使用root 用户 密码：123456 。如要修改文件如下src/serve/db/db.cpp
> 
> ![image](https://github.com/user-attachments/assets/a1050477-0983-45e9-8a68-6d6cfcb495c1)
 

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









