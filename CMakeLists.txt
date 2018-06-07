cmake_minimum_required(VERSION 3.7)
project(DS_wet2_a)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-DNDEBUG" )
set(SOURCE_FILES main.cpp AVLtree.h minHeap.h player.cpp player.h clan.cpp clan.h hash.h List.h)
add_executable(DS_wet2_a ${SOURCE_FILES})