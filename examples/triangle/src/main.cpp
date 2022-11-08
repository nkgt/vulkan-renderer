#include "vulkan-renderer/window/game_window.hpp"
#include "vulkan-renderer/vulkan/renderer.hpp"

int main()
{
    GameWindow window(800, 600, L"三角形");
    Backend backend("Triangle");

    window.loop();

    return 0;
}