# To find the cmake version run $ cmake --version
cmake_minimum_required(VERSION 3.22)

# Set the project
set(PROJECT_NAME "ProductKeyForge")
project(${PROJECT_NAME}
        VERSION 1.0.0
        DESCRIPTION "ProductKeyForge is a lightweight, cross-platform C++20 library designed to generate, validate, and even encrypt custom product keys."
        HOMEPAGE_URL "https://github.com/Gliptodont/ProductKeyForge"
        LANGUAGES CXX
)

# Set the C++ standard we will use to compile the library
set(CMAKE_CXX_STANDARD 20)
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
        include/PKF.h
        include/KeyFormat.h
        include/ProductKeyGenerator.h

        # Random Generator
        include/RandomGenerator/IRandomGenerator.h
        include/RandomGenerator/MTRandomGenerator.h
        include/RandomGenerator/LinearCongruentialGenerator.h
        include/RandomGenerator/XorshiftGenerator.h

        # Checksum Algorithm
        include/Checksum/IChecksumAlgorithm.h
        include/Checksum/BaseChecksumAlgorithm.h
        include/Checksum/CRC32ChecksumAlgorithm.h

        # Encryption Algorithm
        include/Encryption/IEncryptionAlgorithm.h
        include/Encryption/XOREncryption.h
        include/Encryption/VigenereCipher.h
        include/Encryption/ShiftCipher.h
)

# Set the source files
set(SOURCE_FILES
        src/KeyFormat.cpp
        src/ProductKeyGenerator.cpp

        # Random Generator
        src/RandomGenerator/MTRandomGenerator.cpp
        src/RandomGenerator/LinearCongruentialGenerator.cpp
        src/RandomGenerator/XorshiftGenerator.cpp

        # Checksum Algorithm
        src/Checksum/BaseChecksumAlgorithm.cpp
        src/Checksum/CRC32ChecksumAlgorithm.cpp

        # Encryption Algorithm
        src/Encryption/XOREncryption.cpp
        src/Encryption/VigenereCipher.cpp
        src/Encryption/ShiftCipher.cpp
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

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_NAME "gcc")
    set(COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_NAME "clang")
    set(COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_NAME "msvc")
    set(COMPILER_VERSION "${MSVC_VERSION}")
else()
    set(COMPILER_NAME "unknown")
    set(COMPILER_VERSION "unknown")
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

# CPack configuration for simple archive packaging
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${COMPILER_NAME}")
set(CPACK_GENERATOR "ZIP")

# Include CPack to enable the configuration
include(CPack)

# Test -DTEST_PRODUCT_KEY_FORGE=ON
option(TEST_PRODUCT_KEY_FORGE "Test ProductKeyForge" OFF)
if(TEST_PRODUCT_KEY_FORGE)
    add_subdirectory(test)
endif()

# Example -DBUILD_PRODUCT_KEY_FORGE_EXAMPLE=ON
option(BUILD_PRODUCT_KEY_FORGE_EXAMPLE "Build ProductKeyForge Example" OFF)
if(BUILD_PRODUCT_KEY_FORGE_EXAMPLE)
    add_subdirectory(example)
endif()
