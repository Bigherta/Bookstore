cmake_minimum_required(VERSION 3.10)
project(BookstoreManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1️⃣ 找 Qt 库
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 2️⃣ 定义后端源文件
set(BACKEND_SOURCES
    src/user.cpp
    src/book.cpp
    src/log.cpp
    src/parser.cpp
    src/Token.cpp
)

# 3️⃣ 定义前端源文件
set(FRONTEND_SOURCES
    frontend/src/main.cpp
    frontend/src/mainwindow.cpp
)

# 4️⃣ 添加可执行目标
add_executable(BookstoreApp ${BACKEND_SOURCES} ${FRONTEND_SOURCES})

# 5️⃣ 包含头文件目录
target_include_directories(BookstoreApp
    PRIVATE
        include        # 后端头文件
        frontend       # 如果前端也有独立头文件
)

# 6️⃣ 链接 Qt 库
target_link_libraries(BookstoreApp PRIVATE Qt5::Widgets)

# 7️⃣ 启用 Qt 自动 MOC (必要时)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
