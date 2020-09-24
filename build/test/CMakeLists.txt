cmake_minimum_required(VERSION 3.10)

set(PR_NAME "TestApp")

project(${PR_NAME})

add_executable(${PR_NAME}
    ../../src/test.c)

target_link_libraries(${PR_NAME} PRIVATE ArithmeticLib)

target_include_directories(${PR_NAME} PRIVATE ../../inc)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()