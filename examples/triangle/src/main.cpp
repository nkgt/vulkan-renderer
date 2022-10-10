#include "vulkan-renderer/window/game_window.hpp"
#include "vulkan-renderer/vulkan/instance.hpp"

int main()
{
    GameWindow window(800, 600, L"三角形");
    Instance i("Triangle");

    window.loop();

    return 0;
}