#include "vulkan-renderer/vulkan/renderer.hpp"

int main()
{
    Backend backend(800, 600, L"三角形", "Triangle");
    backend.loop();

    return 0;
}