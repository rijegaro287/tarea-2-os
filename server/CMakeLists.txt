cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

project(ImageServer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(
  SOURCES
  src/main.c
  src/server.c
  src/processing.c
  src/helpers.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(ImageServer ${SOURCES})

target_link_libraries(ImageServer m)