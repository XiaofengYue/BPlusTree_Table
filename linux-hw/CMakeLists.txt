cmake_minimum_required(VERSION 3.10)
project(linux_hw)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread ")
add_executable(linux_hw main.cpp CLThread.cpp CLThread.h CLExecutive.h CLExecutiveFunctionProvider.h CLTableManager.cpp CLTableManager.h struct.h CLBPlusTree.h CLBPlusTree.cpp CLExecutiveFunctionInsert.h CLExecutiveFunctionSearch.h CLExecutiveFunctionGenerateData.h)
