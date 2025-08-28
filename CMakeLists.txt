cmake_minimum_required(VERSION 3.15)
project(MyCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.0)

include_directories(${GTK3_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS})

add_compile_options(${GTK3_CFLAGS_OTHER} ${WEBKIT_CFLAGS_OTHER})

add_executable(calculator main.cpp)

target_link_libraries(calculator ${GTK3_LIBRARIES} ${WEBKIT_LIBRARIES})

