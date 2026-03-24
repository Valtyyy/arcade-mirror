cmake_minimum_required(VERSION 3.13)
project(arcade)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUG "Compile with -g3" OFF)

set(SHARED
    shared/src/DlLoader.cpp
)

set(CORE
    ${SHARED}
)

add_executable(arcade ${CORE} core/src/main.cpp)

target_compile_options(arcade PRIVATE
    -Wall
    -Wextra
)

if(DEBUG)
    target_compile_options(arcade PRIVATE -g3)
endif()

include_directories(${PROJECT_SOURCE_DIR}/shared/include)

# ===== Tests =====

enable_testing()

add_executable(test_binary
    ${CORE}
    tests/test_void.cpp
    tests/test_shared.cpp
)

add_library(test_lib SHARED tests/libtest/lib_test.cpp)

target_compile_options(test_binary PRIVATE
    -Wall
    -Wextra
    -g3
)

target_compile_definitions(test_binary PRIVATE
    LIB_PATH="${CMAKE_CURRENT_BINARY_DIR}/"
)

target_include_directories(test_lib
    PRIVATE
        ${PROJECT_SOURCE_DIR}/libtest/
        ${PROJECT_SOURCE_DIR}/shared/include
)

target_link_libraries(test_binary PRIVATE criterion)
