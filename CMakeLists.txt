cmake_minimum_required(VERSION 3.10)

project(BookstoreManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 输出目录（可选）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    src/main.cpp
    src/user.cpp
    src/book.cpp
    src/log.cpp
    src/parser.cpp
    src/Token.cpp
)

add_executable(code ${SOURCES})

target_include_directories(code
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
