# 指定cmake最低版本 不指定会收到警告信息
cmake_minimum_required(VERSION 3.15)
# 工程名称
project(c-record C)

# 指定c语言标准
set(CMAKE_C_STANDARD 11)

# 设置可执行文件的输出目录
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/bin)
# 设置库文件的输出目录
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)

# 生成可执行文件
add_executable(c-record main.c)

add_executable(pointer base/pointer.c)
add_executable(head base/number.c base/head.c)
add_executable(macro base/macro.c)

add_executable(http http/main.c)
add_executable(num-convert num-convert/main.c)

add_executable(server http/server.c)
# 将通过add_executable()或add_library()指令生成的目标文件与库文件进行链接
target_link_libraries(server ws2_32)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/http/index.html
        ${CMAKE_CURRENT_BINARY_DIR}
)

# 官网文档 https://cmake.org/documentation
# cmake 自定义变量 隐式定义和显式定义
#   隐式定义 如PROJECT指令会隐式定义<projectName>_BINARY_DIR和<projectName>_SOURCE_DIR
#   显式定义 使用SET指令定义自定义变量
#
# PROJECT_SOURCE_DIR
#   始终为工程顶层目录 在in source编译时 与PROJECT_BINARY_DIR值一致
#   <projectName>_SOURCE_DIR和CMAKE_SOURCE_DIR与此变量值一致
#
# cmake 常用变量
# PROJECT_BINARY_DIR
#   如为in source编译 值为工程顶层目录
#   如为out of source编译 值为工程编译目录
#   <projectName>_BINARY_DIR和CMAKE_BINARY_DIR与此变量值一致
#
# CMAKE_CURRENT_SOURCE_DIR
#   当前处理的CMakeLists.txt所在目录
#
# CMAKE_CURRENT_BINARY_DIR
#   in source编译 与CMAKE_CURRENT_SOURCE_DIR值一致
#   out of source编译 值为target编译目录 ADD_SUBDIRECTORY(src bin)可更改此变量值
#
# CMAKE_CURRENT_LIST_FILE
#   输出调用此变量的CMakeLists.txt路径
#
# CMAKE_CURRENT_LIST_LINE
#   输出此变量所在行
#
# CMAKE_MODULE_PATH
#   此变量用来定义自己的cmake模块所在路径
#   自己编写cmake模块时 且自定义模块随工程发布 使cmake处理CMakeLists.txt时找到自定义模块
#   需使用SET指令 设置模块路径 如 SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#   此时可通过INCLUDE指令调用自定义模块
#
# EXECUTABLE_OUTPUT_PATH和LIBRARY_OUTPUT_PATH
#   前者重新定义可执行文件存放位置 后者重新定义目标链接库文件存放位置
#
# PROJECT_NAME 获取PROJECT指令定义的项目名称
# 
# cmake调用环境变量 $ENV{NAME}
#
# 设置环境变量 SET(ENV{NAME} VALUE)
#
# 系统信息
# CMAKE_MAJOR_VERSION CMAKE 主版本号 如1.2.3中的1
# CMAKE_MINOR_VERSION CMAKE 次版本号 如1.2.3中的2
# CMAKE_PATCH_VERSION CMAKE 补丁等级 如1.2.3中的3
# CMAKE_SYSTEM 系统名称 如linux-1.2.3
# CMAKE_SYSTEM_NAME 不包含版本的系统名 如linux
# CMAKE_SYSTEM_VERSION 系统版本 如1.2.3