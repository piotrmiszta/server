cmake_minimum_required(VERSION 3.2)
set(PROJ_NAME "server")
project(${PROJ_NAME})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-Weverything -Wno-declaration-after-statement -Wno-date-time -g")
#set(CMAKE_C_FLAGS "-pthread -Wall -pedantic -g -Werror -lm")
add_subdirectory(src)

add_executable(${PROJ_NAME} src/main.c)

enable_testing()
target_link_libraries(${PROJ_NAME} PUBLIC "serverlib")
target_link_libraries(${PROJ_NAME} PUBLIC "utility")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(cmocka 1.1.0 REQUIRED)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/AddCMockaTest.cmake)
add_subdirectory(test)
