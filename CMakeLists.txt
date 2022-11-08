cmake_minimum_required(VERSION 3.24)
project(vulkan-render)

include(cmake/compiler.cmake)

set(GLOBAL PROPERTY USE_FOLDERS ON)
set(GLOBAL PROPERTY CXX_STANDARD_REQUIRED 20)

find_package(spdlog CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

set(vulkan_renderer_SOURCES
    src/game_window.cpp
    src/physical_device.cpp
    src/instance.cpp
    src/renderer.cpp
)

set(vulkan_renderer_HEADERS
    include/vulkan-renderer/window/game_window.hpp
    include/vulkan-renderer/vulkan/physical_device.hpp
    include/vulkan-renderer/vulkan/instance.hpp
    include/vulkan-renderer/vulkan/renderer.hpp
)

add_library(vulkan_renderer STATIC
    ${vulkan_renderer_HEADERS}
    ${vulkan_renderer_SOURCES}
)

target_include_directories(vulkan_renderer PUBLIC include)
target_link_libraries(vulkan_renderer PRIVATE spdlog::spdlog)
target_link_libraries(vulkan_renderer PUBLIC Vulkan::Vulkan)
set_compiler_options(vulkan_renderer)
set_warnings(vulkan_renderer)

if(VULKAN_RENDERER_EXAMPLES)
    add_subdirectory(examples)
endif()