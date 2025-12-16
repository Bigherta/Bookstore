# 1. 指定所需的 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 2. 定义项目名称
project(BookstoreManager VERSION 1.0
    LANGUAGES CXX
)

# 3. 指定 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. 定义源文件列表 (所有 .cpp 文件)
# 假设所有 .cpp 文件都在 src 目录下
set(SOURCES
    src/main.cpp
    src/user.cpp
    src/book.cpp
    src/log.cpp
    src/parser.cpp
    src/Token.cpp
)

# 5. 添加可执行目标
# 目标名称已更改为 'code'
add_executable(code ${SOURCES})

# 6. 配置包含目录
# ----------------------------------------------------------------------
# 注意：这里的目标名称已从 'bookstore_app' 更改为 'code'
target_include_directories(code
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# ----------------------------------------------------------------------

# 7. 链接依赖库 (如果您的项目使用了外部库，则在这里添加)
# target_link_libraries(code PRIVATE) # 相应的目标名也应改为 'code'