add_executable(triangle WIN32 src/main.cpp)

target_link_libraries(triangle PRIVATE vulkan_renderer)
set_compiler_options(triangle)
set_warnings(triangle)
