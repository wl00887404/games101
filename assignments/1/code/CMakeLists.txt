cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(Rasterizer)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")

find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp Triangle.hpp Triangle.cpp)
target_include_directories(Rasterizer PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(Rasterizer ${OpenCV_LIBS})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(STATUS "Include directories: ${dirs}")

get_target_property(tar_dirs Rasterizer INCLUDE_DIRECTORIES)
message(STATUS "Rasterizer include directories: ${tar_dirs}")