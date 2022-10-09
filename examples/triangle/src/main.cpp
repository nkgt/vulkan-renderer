#include "vulkan-renderer/window/game_window.hpp"

#ifndef UNICODE
#define UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	GameWindow window(800, 600, L"三角形", reinterpret_cast<int*>(hInstance), nCmdShow);
	window.loop();

	return 0;
}