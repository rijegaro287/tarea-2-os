cmake_minimum_required(VERSION 3.15)
project(ImageServer)

set(CMAKE_C_COMPILER /usr/bin/g++)

set(U_CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
list(APPEND CMAKE_MODULE_PATH "${U_CMAKE_MODULE_PATH}")

include(FindUlfius)
include(FindLibConfig)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(
  SOURCES
  src/main.c
  src/config.c
  src/http_server.c 
  src/processing.c
  src/helpers.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(ImageServer ${SOURCES})

target_link_libraries(ImageServer ${ULFIUS_LIBRARIES})
target_link_libraries(ImageServer ${LIBCONFIG_LIBRARIES}) 
target_link_libraries(ImageServer m)