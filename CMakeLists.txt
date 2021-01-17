cmake_minimum_required(VERSION 3.0.0)
project(my_machine_learning_c++)
AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
set(CMAKE_CXX_STANDARD 11)
include_directories(include)

add_executable(my_machine_learning_c++ main.cpp)


#add_executable(run ${DIR_SRCS})

