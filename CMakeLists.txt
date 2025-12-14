# 1. 指定所需的 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 2. 定义项目名称
project(BookstoreManager VERSION 1.0 LANGUAGES CXX)

# 3. 指定 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. 定义头文件查找路径
# 使用 target_include_directories 更规范
# PRIVATE 表示只对当前目标生效
# PROJECT_SOURCE_DIR 指向项目根目录
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# 5. 定义所有源文件
set(SOURCES
    src/main.cpp
    src/user.cpp
    src/book.cpp
    src/log.cpp
    src/parser.cpp
    src/storage.cpp
    src/Token.cpp
)

# 6. 添加可执行目标
add_executable(code ${SOURCES})

# 7. 绑定头文件路径到目标
target_include_directories(code PRIVATE ${INCLUDE_DIR})

# 8. 链接依赖库（如果有外部库，可以在这里添加）
# 例如：target_link_libraries(code PRIVATE Boost::boost)
