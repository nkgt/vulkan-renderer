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
#include "windows.h"

#include "spdlog/spdlog.h"

#include <stdexcept>

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

GameWindow::GameWindow(
	std::size_t width,
	std::size_t height,
	std::wstring window_name
) {
	HINSTANCE hInstance = GetModuleHandle(0);

	WNDCLASS wc{
		.lpfnWndProc = WindowProc,
		.hInstance = hInstance,
		.lpszClassName = window_name.c_str()
	};

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		window_name.c_str(),
		window_name.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		static_cast<int>(width), static_cast<int>(height),
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (hwnd == nullptr) {
		std::string error_message ("Unable to create a window! Aborting...");

		spdlog::error(error_message);
		throw std::runtime_error(error_message);
	}

	ShowWindow(hwnd, 5);
}

void GameWindow::loop() const {
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
