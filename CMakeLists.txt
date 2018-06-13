cmake_minimum_required(VERSION 3.7)
project(DS_wet2_a)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-DNDEBUG -Wall" )
set(CMAKE_CXX_FLAGS  )
set(SOURCE_FILES  AVLtree.h minHeap.h player.cpp player.h clan.cpp clan.h hash.h List.h rankTree.h oasis.cpp oasis.h library2.cpp library2.h penguin_tests.cpp)

add_executable(DS_wet2_a ${SOURCE_FILES})
