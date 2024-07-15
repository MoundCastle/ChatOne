cmake_minimum_required(VERSION 3.10) #要求cmake最低的版本号
project(chat)

# 配置选项
set(CMAKE_BUILD_TYPE "Debug")#设置debug模式，如果没有这一行将不能调试设断点
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 设置cmake的全局变量   放置可执行文件 /根目录/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#添加头文件路径，相当于makefile里面的-I
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty) 


# 指定搜索的子目录
add_subdirectory(src)