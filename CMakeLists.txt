# 1. 指定所需的 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 2. 定义项目名称
project(BookstoreManager VERSION 1.0
    LANGUAGES CXX
)

# 3. 指定 C++ 标准
# 现代 C++ 代码通常推荐 C++17 或更高
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. 定义头文件查找路径
# 假设所有头文件 (.hpp) 都在项目根目录下的 'include/' 目录中
include_directories(
    include
)

# 5. 定义所有源文件列表 (假设它们位于 src 目录)
# ----------------------------------------------------
set(SOURCES
    src/main.cpp
    src/user.cpp
    src/book.cpp
    src/log.cpp
    src/parser.cpp
    src/storage.cpp
    src/Token.cpp
)
# ----------------------------------------------------

# 6. 添加可执行目标
# 生成名为 'bookstore_app' 的可执行文件
add_executable(code ${SOURCES})

# 7. 链接依赖库 (如果您的项目使用了外部库，例如 Boost、SQLite 等，则在这里添加)
# target_link_libraries(bookstore_app PRIVATE)