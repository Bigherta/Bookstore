cmake_minimum_required(VERSION 3.10)
project(BookstoreApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

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
set(DIALOG_HEADERS
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
    frontend/src/mainwindow.hpp
)

# ---------------------------
# Qt 资源文件
# ---------------------------
set(IMAGE_QRC "${CMAKE_CURRENT_SOURCE_DIR}/images.qrc")
qt6_add_resources(RESOURCES ${IMAGE_QRC})

# ---------------------------
# 创建可执行文件
# ---------------------------
add_executable(BookstoreApp ${SOURCES})
target_sources(BookstoreApp PRIVATE ${DIALOG_HEADERS} ${RESOURCES})

target_include_directories(BookstoreApp PRIVATE
    include
    frontend/src
    frontend/dialogs
)

target_link_libraries(BookstoreApp PRIVATE Qt6::Widgets)
