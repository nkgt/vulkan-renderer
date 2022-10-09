#pragma once

#include <string>

class GameWindow {
public:
	GameWindow(
		std::size_t width,
		std::size_t height,
		std::wstring window_name,
		int* handle,
		int cmdShow
	);

	void loop() const;
};
