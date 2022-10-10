add_executable(triangle src/main.cpp)

target_link_libraries(triangle PRIVATE vulkan_renderer)
set_compiler_options(triangle)
set_warnings(triangle)
