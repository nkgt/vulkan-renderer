#pragma once

#include "vulkan-renderer/vulkan/instance.hpp"
#include "vulkan-renderer/vulkan/physical_device.hpp"

class Backend {
public:
	explicit Backend(std::string application_name);

private:
	Instance m_instance;
	PhysicalDevice m_physical_device;
};
