cmake_minimum_required(VERSION 3.25)
project(SDE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(source_dir "${CMAKE_SOURCE_DIR}/source")
file(GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable(SDE ${source_files})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)