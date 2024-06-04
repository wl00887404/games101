cmake_minimum_required(VERSION 3.5)

# $ENV{} 使用環境變數
# ${} 使用 CMAKE 設置的變數
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(Transformation)

find_package(Eigen3 REQUIRED)

# 檢查 vcpkg 設置了什麼參數
message(STATUS "Eigen3_DIR = ${Eigen3_DIR}")
message(STATUS "EIGEN3_INCLUDE_DIR = ${EIGEN3_INCLUDE_DIR}")
message(STATUS "EIGEN3_INCLUDE_DIRS = ${EIGEN3_INCLUDE_DIRS}")


add_executable(Transformation main.cpp)

# NOTICE: 使用 CMAKE 設置的變數一定要用 ${} 刮起來
# 用 include_directories 是全域的，改成 target_include_directories 會更好
target_include_directories(Transformation PRIVATE ${EIGEN3_INCLUDE_DIR})

# 印出所有 include 資料夾
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(STATUS "Include directories: ${dirs}")

get_target_property(tar_dirs Transformation INCLUDE_DIRECTORIES)
message(STATUS "Transformation include directories: ${tar_dirs}")
