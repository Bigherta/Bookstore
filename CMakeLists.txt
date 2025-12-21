cmake_minimum_required(VERSION 3.16)

project(BookstoreApp
    VERSION 1.0
    LANGUAGES CXX
)

# ---------------------------
# C++ 标准
# ---------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------
# Qt 自动工具
# ---------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---------------------------
# 查找 Qt6
# ---------------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ---------------------------
# 源文件
# ---------------------------
set(SOURCES
    frontend/src/main.cpp
    frontend/src/mainwindow.cpp

    src/parser.cpp
    src/user.cpp
    src/Log.cpp
    src/book.cpp
    src/Token.cpp
)

# ---------------------------
# 带 Q_OBJECT 的头文件
# ---------------------------
set(HEADERS
    frontend/src/mainwindow.hpp

    frontend/dialogs/registerdialog.hpp
    frontend/dialogs/deletedialog.hpp
    frontend/dialogs/buydialog.hpp
    frontend/dialogs/showbookdialog.hpp
    frontend/dialogs/financedialog.hpp
    frontend/dialogs/modifydialog.hpp
    frontend/dialogs/logindialog.hpp
    frontend/dialogs/selectdialog.hpp
    frontend/dialogs/useradddialog.hpp
    frontend/dialogs/reportdialog.hpp
    frontend/dialogs/passwddialog.hpp
    frontend/dialogs/importdialog.hpp
    frontend/dialogs/outcomedialog.hpp
    frontend/dialogs/logdialog.hpp
)

# ---------------------------
# Qt 资源文件
# ---------------------------
qt6_add_resources(RESOURCES
    images.qrc
)

# ---------------------------
# 创建 Windows GUI 可执行文件（关键！）
# ---------------------------
add_executable(BookstoreApp
    WIN32
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# ---------------------------
# 头文件搜索路径
# ---------------------------
target_include_directories(BookstoreApp PRIVATE
    include
    src
    frontend/src
    frontend/dialogs
)

# ---------------------------
# 链接 Qt 库
# ---------------------------
target_link_libraries(BookstoreApp PRIVATE
    Qt6::Widgets
)

# ---------------------------
# Qt6 规范收尾（可选但推荐）
# ---------------------------
qt_finalize_executable(BookstoreApp)
