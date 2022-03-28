cmake_minimum_required (VERSION 3.8)

project ("icp")

add_executable (icp "icp.cpp" "icp.h")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

