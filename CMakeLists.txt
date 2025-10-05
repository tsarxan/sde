cmake_minimum_required(VERSION 3.25)
project(SDE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(source_dir "${CMAKE_SOURCE_DIR}/source")
set(libraries_dir "${CMAKE_SOURCE_DIR}/libraries")

file(GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable(SDE ${source_files})

include_directories(
    "${source_dir}"

    "${libraries_dir}/imgui/"
    "${libraries_dir}/imgui/backends"
    
    "${libraries_dir}/json/"
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)