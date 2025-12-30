cmake_minimum_required(VERSION 3.16)

project(BookstoreApp
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    frontend/src/main.cpp
    frontend/src/mainwindow.cpp

    src/parser.cpp
    src/user.cpp
    src/Log.cpp
    src/book.cpp
    src/Token.cpp
)

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

qt6_add_resources(RESOURCES
    images.qrc
)

add_executable(BookstoreApp
    WIN32
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

target_include_directories(BookstoreApp PRIVATE
    include
    src
    frontend/src
    frontend/dialogs
)

target_link_libraries(BookstoreApp PRIVATE
    Qt6::Widgets
)

qt_finalize_executable(BookstoreApp)
