# To find the cmake version run $ cmake --version
cmake_minimum_required(VERSION 3.22)

# Set the project
set(PROJECT_NAME "ProductKeyForge")
project(${PROJECT_NAME}
        VERSION 0.0.1
        DESCRIPTION "ProductKeyForge is a lightweight, cross-platform C++20 library designed to generate, validate, and even encrypt custom product keys."
        HOMEPAGE_URL "https://github.com/Gliptodont/ProductKeyForge"
        LANGUAGES CXX
)

# Set the C++ standard we will use to compile the library
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Clang-Tidy configuration
find_program(CLANG_TIDY_COMMAND NAMES "clang-tidy")
if(CLANG_TIDY_COMMAND)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()

# Extra CMake modules
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set the headers files
set(HEADER_FILES
        include/RandomGenerator/IRandomGenerator.h
        include/RandomGenerator/MTRandomGenerator.h
)

# Set the source files
set(SOURCE_FILES
        src/RandomGenerator/MTRandomGenerator.cpp
)

# Add the library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Set the include directories
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Compiler flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror)
endif()

# Installation
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
)

write_basic_package_version_file(
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${CMAKE_SOURCE_DIR}/Config.cmake.in"
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
)

install(FILES
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
)

# Tests
option(BUILD_PRODUCT_KEY_FORGE_TESTS "Build ProductKeyForge tests" OFF)
if(BUILD_PRODUCT_KEY_FORGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()