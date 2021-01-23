cmake_minimum_required(VERSION 3.13)
project(my_machine_learning_c++ VERSION 0.1.0)

project(my_machine_learning_c++ )
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src DIR_SRCS)
set(CMAKE_CXX_STANDARD 11)
include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(run ${DIR_SRCS} )
set(CMAKE_BUILD_TYPE Debug)

#add_executable(run ${DIR_SRCS})
#main.cpp