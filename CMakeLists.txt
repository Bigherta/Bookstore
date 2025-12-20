cmake_minimum_required(VERSION 3.10)
project(BookstoreApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/frontend/src
    ${CMAKE_SOURCE_DIR}/frontend/dialogs
)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/frontend/src/main.cpp
    ${CMAKE_SOURCE_DIR}/frontend/src/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/src/parser.cpp
    ${CMAKE_SOURCE_DIR}/src/user.cpp
    ${CMAKE_SOURCE_DIR}/src/Log.cpp
    ${CMAKE_SOURCE_DIR}/src/book.cpp
    ${CMAKE_SOURCE_DIR}/src/Token.cpp
)

set(DIALOG_HEADERS
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/registerdialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/deletedialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/buydialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/showbookdialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/financedialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/modifydialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/logindialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/selectdialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/useradddialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/reportdialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/passwddialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/importdialog.hpp
    ${CMAKE_SOURCE_DIR}/frontend/dialogs/outcomedialog.hpp
)

add_executable(BookstoreApp
    ${SOURCES}
    ${DIALOG_HEADERS}
)

target_link_libraries(BookstoreApp Qt6::Widgets)
