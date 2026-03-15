cmake_minimum_required(VERSION 3.13)
project(arcade)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUG "Compile with -g3" OFF)

set(SOURCES
    
)

add_executable(arcade ${SOURCES} src/main.cpp)

target_compile_options(arcade PRIVATE
    -Wall
    -Wextra
)

if(DEBUG)
    target_compile_options(arcade PRIVATE -g3)
endif()

target_include_directories(arcade
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Tests

enable_testing()

add_executable(test_binary
    ${SOURCES}
    tests/test_void.cpp
)

target_compile_options(test_binary PRIVATE
    -Wall
    -Wextra
    -g3
)

target_include_directories(test_binary
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_binary PRIVATE criterion)