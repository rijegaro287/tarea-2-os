cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

project(ImageServer)

# find_package(OpenCV REQUIRED)

# include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(
  SOURCES
  src/main.c
  src/server.c
  src/processing.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(ImageServer ${SOURCES})

# target_link_libraries(ImageServer ${OpenCV_LIBS})
