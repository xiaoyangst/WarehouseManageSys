cmake_minimum_required(VERSION 3.26)
project(WarehouseManageSys)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

#搜索头文件
include_directories(include/)
file(GLOB HEADER_FILES "include/*.h")

#搜索源文件
file(GLOB SRC_LIST "src/*.cpp")

# 搜索ui文件
file(GLOB UI_FILES "ui/*.ui")

# 搜索资源文件（图片、图标、音乐等）
file(GLOB_RECURSE RESOURCES "sources/*.qrc")

add_subdirectory(src)

#调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT6_WRAP_CPP(HEADERS_MOC ${HEADER_FILES})
#使用uic处理.ui文件
QT6_WRAP_UI(FORMS_HEADERS ${UI_FILES})
#处理资源得到.qrc文件
QT6_ADD_RESOURCES(RCC ${RESOURCES})

add_executable(WarehouseManageSys main.cpp ${HEADERS_MOC} ${SRC_LIST} ${FORMS_HEADERS} ${RCC})

target_link_libraries(WarehouseManageSys
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
)
