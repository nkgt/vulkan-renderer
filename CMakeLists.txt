cmake_minimum_required(VERSION 3.24)
project(vulkan-render)

include(cmake/compiler.cmake)

set(GLOBAL PROPERTY USE_FOLDERS ON)
set(GLOBAL PROPERTY CXX_STANDARD_REQUIRED 20)

find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_library(vulkan_renderer STATIC
    include/vulkan-renderer/window/game_window.hpp
    src/game_window.cpp
)

target_include_directories(vulkan_renderer PUBLIC include)
target_link_libraries(vulkan_renderer PRIVATE spdlog::spdlog Vulkan::Vulkan)
set_compiler_options(vulkan_renderer)
set_warnings(vulkan_renderer)

if(VULKAN_RENDERER_EXAMPLES)
    add_subdirectory(examples)
endif()