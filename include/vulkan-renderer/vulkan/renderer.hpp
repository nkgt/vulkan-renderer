#pragma once

#include "vulkan-renderer/vulkan/instance.hpp"
#include "vulkan-renderer/vulkan/device.hpp"
#include "vulkan-renderer/window/game_window.hpp"

class Backend {
public:
	explicit Backend(
		std::size_t width,
		std::size_t height,
		std::wstring window_name,
		std::string application_name
	);

	void loop() const noexcept;

private:
	Instance m_instance;
	GameWindow m_window;
	Device m_device;
};
