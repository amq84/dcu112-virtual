cmake_minimum_required(VERSION 3.10)

project(peripheral LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDBUSCPP REQUIRED sdbus-c++)

add_executable(peripheral
    main_peripheral.cpp
    gatt_app.cpp
    advertisement.cpp
)

target_include_directories(peripheral PRIVATE ${SDBUSCPP_INCLUDE_DIRS})
target_link_libraries(peripheral ${SDBUSCPP_LIBRARIES} btscanner)
