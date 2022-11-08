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

class PhysicalDevice {
public:
	PhysicalDevice(const vk::Instance& instance);

private:
	vk::PhysicalDevice m_physical_device;
};