#pragma once

#ifndef VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_NO_EXCEPTIONS
#endif

#ifndef VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_NO_CONSTRUCTORS
#endif

#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifndef VULKAN_HPP_NO_SETTERS
#define VULKAN_HPP_NO_SETTERS
#endif

#ifndef UNICODE
#define UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "vulkan/vulkan.hpp"

#include <string>

class GameWindow {
public:
	GameWindow(
		std::size_t width,
		std::size_t height,
		const std::wstring& window_name,
		const vk::Instance* instance
	);

	~GameWindow();

	void loop() const;
	const vk::SurfaceKHR& get_surface() const noexcept;

private:
	const vk::Instance* m_instance;
	vk::SurfaceKHR m_surface;
};
