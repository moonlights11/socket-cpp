# 设置CMake最低版本  
cmake_minimum_required(VERSION 3.10)  
  
# 设置项目名称和版本  
project(MyProject VERSION 1.0)  
  
# 设置C++标准（如果需要）  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  
  
# 添加可执行文件  
add_executable(server main.cpp tcp-server.cpp)  