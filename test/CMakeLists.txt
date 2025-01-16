cmake_minimum_required(VERSION 3.22)

project(Test LANGUAGES CXX)

enable_testing()

file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_subdirectory(googletest)
add_executable(Test ${TEST_SOURCES})

target_link_libraries(Test PRIVATE ProductKeyForge gtest_main gmock_main)