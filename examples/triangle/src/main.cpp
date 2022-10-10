#include "vulkan-renderer/window/game_window.hpp"

int main()
{
    GameWindow window(800, 600, L"三角形");
    window.loop();

    return 0;
}