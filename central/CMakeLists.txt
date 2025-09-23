cmake_minimum_required(VERSION 3.10)

project(central LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDBUSCPP REQUIRED sdbus-c++)

add_executable(central
    main_central.cpp
)

target_include_directories(central PRIVATE ${SDBUSCPP_INCLUDE_DIRS})
target_link_libraries(central ${SDBUSCPP_LIBRARIES} btscanner)
