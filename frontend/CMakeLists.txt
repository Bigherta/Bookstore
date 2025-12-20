cmake_minimum_required(VERSION 3.10)
project(BookstoreFrontend LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找 Qt5 Widgets 库
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 自动处理 Q_OBJECT、.ui、.qrc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 包含头文件路径
include_directories(
    ../include       # Bookstore/include
    src               # frontend/src
    dialogs           # 所有 dialog header
)

# 所有源文件
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    ../src/parser.cpp
    ../src/user.cpp
    ../src/Log.cpp
    ../src/book.cpp
    ../src/Token.cpp
)

# 所有 header-only dialogs（必须被 CMake 知道，moc 才会处理）
set(DIALOG_HEADERS
    dialogs/registerdialog.hpp
    dialogs/deletedialog.hpp
    dialogs/buydialog.hpp
    dialogs/showbookdialog.hpp
    dialogs/financedialog.hpp
    dialogs/modifydialog.hpp
    dialogs/logindialog.hpp
    dialogs/selectdialog.hpp
    dialogs/useradddialog.hpp
    dialogs/reportdialog.hpp
    dialogs/passwddialog.hpp
    dialogs/importdialog.hpp
    dialogs/outcomedialog.hpp
)

# 添加可执行文件
add_executable(BookstoreFrontend
    ${SOURCES}
    ${DIALOG_HEADERS}
)

# 链接 Qt5 Widgets
target_link_libraries(BookstoreFrontend Qt5::Widgets)
