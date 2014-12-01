cmake_minimum_required(VERSION 3.0)

project("echo-core")

enable_testing()

include(Echo/Test)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB headers
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/echo/*.h"
)

install(FILES ${headers} DESTINATION include/echo)

add_subdirectory(unittest)
