cmake_minimum_required(VERSION 3.25)
project(SDE)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(source_dir "${CMAKE_SOURCE_DIR}/source")
set(libraries_dir "${CMAKE_SOURCE_DIR}/libraries")
set(imgui_dir "${libraries_dir}/imgui")

set(imgui_sources
    "${imgui_dir}/imgui.cpp"
    "${imgui_dir}/imgui_draw.cpp"
    "${imgui_dir}/imgui_widgets.cpp"
    "${imgui_dir}/imgui_tables.cpp"
    "${imgui_dir}/imgui_demo.cpp"
    "${imgui_dir}/backends/imgui_impl_glfw.cpp"
    "${imgui_dir}/backends/imgui_impl_opengl2.cpp"
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable(SDE ${source_files} ${imgui_sources})

include_directories(
    "${source_dir}"

    "${libraries_dir}/imgui/"
    "${libraries_dir}/imgui/backends"
    
    "${libraries_dir}/json/"
)

target_include_directories(SDE PRIVATE
    "${source_dir}"

    "${imgui_dir}"
    "${imgui_dir}/backends"

    "${libraries_dir}/json"
)

target_link_libraries(SDE PRIVATE
    glfw
    OpenGL::GL
    pthread
    dl
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)