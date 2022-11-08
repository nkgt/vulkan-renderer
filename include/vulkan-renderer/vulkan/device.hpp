#pragma once

#ifndef VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_NO_EXCEPTIONS
#endif

#ifndef VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_NO_CONSTRUCTORS
#endif

#ifndef VULKAN_HPP_NO_SETTERS
#define VULKAN_HPP_NO_SETTERS
#endif

#include "vulkan/vulkan.hpp"

class Device {
public:
	Device(const vk::Instance& instance, const vk::SurfaceKHR& surface);
	~Device();

private:
	vk::PhysicalDevice m_physical_device;
	vk::Device m_device;
	vk::Queue m_graphics_queue;
	vk::Queue m_present_queue;
};