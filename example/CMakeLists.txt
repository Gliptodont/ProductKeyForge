cmake_minimum_required(VERSION 3.22)

project(Example
        LANGUAGES CXX
)

add_executable(Example main.cpp)

target_link_libraries(Example PRIVATE ProductKeyForge)