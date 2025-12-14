# 最小CMake版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(Bookstore-2025 CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------
# 1. 设置头文件搜索路径 (include directory)
# ----------------------------------------------------
# 使用相对路径，更安全
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# ----------------------------------------------------
# 2. 收集源文件
# ----------------------------------------------------
# 收集 'src' 目录下所有 .cpp 文件
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# ----------------------------------------------------
# 3. 创建可执行目标
# ----------------------------------------------------
add_executable(Bookstore ${SOURCE_FILES})

# ----------------------------------------------------
# 4. 链接库（OJ上通常不需要额外库，如果需要可自行添加）
# ----------------------------------------------------
# target_link_libraries(Bookstore m)  # 示例：链接数学库

# ----------------------------------------------------
# 5. 输出目录调整（OJ常要求可执行文件在当前目录）
# ----------------------------------------------------
set_target_properties(Bookstore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

# ----------------------------------------------------
# 6. 防止CMake缓存冲突
# ----------------------------------------------------
# 这样可以避免 CMakeCache.txt 不同路径导致的错误
set(CMAKE_CACHEFILE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
