#include "vulkan-renderer/vulkan/device.hpp"
#include "spdlog/spdlog.h"

#include <optional>

struct QueueFamilyIncides {
	std::optional<std::uint32_t> graphics_family;
};

static QueueFamilyIncides find_queue_families(const vk::PhysicalDevice& device) {
	std::uint32_t index = 0;
	QueueFamilyIncides indices;

	for (const auto& family : device.getQueueFamilyProperties()) {
		if (family.queueFlags & vk::QueueFlagBits::eGraphics) {
			indices.graphics_family = index;
		}

		index += 1;
	}

	return indices;
}

static bool is_device_suitable(const vk::PhysicalDevice& device) {
	const auto properties = device.getProperties();
	const auto features = device.getFeatures();
	const auto indices = find_queue_families(device);

	return properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu &&
		   features.geometryShader &&
		   indices.graphics_family.has_value();
}

Device::Device(const vk::Instance& instance) {
	auto [result, devices] = instance.enumeratePhysicalDevices();

	if (result == vk::Result::eSuccess) {
		for (const auto& device : devices) {
			if (is_device_suitable(device)) {
				m_physical_device = device;
				break;
			}
		}
	}
	else {
		auto error_message = std::format("Failed to enumerate Vulkan physical devices! Error: {}", vk::to_string(result));

		spdlog::error(error_message);
		throw std::runtime_error(error_message);
	}

	auto properties = m_physical_device.getProperties();
	spdlog::info("Found suitable physical device: {}", properties.deviceName);

	const float priority = 1.0f;
	const auto queue_family_indices = find_queue_families(m_physical_device);

	vk::DeviceQueueCreateInfo queue_info{
		.queueFamilyIndex = queue_family_indices.graphics_family.value(),
		.queueCount = 1,
		.pQueuePriorities = &priority
	};

	vk::PhysicalDeviceFeatures device_features {};

	vk::DeviceCreateInfo create_info{
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_info,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = nullptr,
		.pEnabledFeatures = &device_features
	};

	const auto [result_create, device] = m_physical_device.createDevice(create_info);

	if (result_create == vk::Result::eSuccess) {
		m_device = device;
		spdlog::info("Successfully created logical Vulkan device");
	}
	else {
		auto error_message = std::format("Failed to create Vulkan device! Error: {}", vk::to_string(result_create));

		spdlog::error(error_message);
		throw std::runtime_error(error_message);
	}

	m_graphics_queue = m_device.getQueue(queue_family_indices.graphics_family.value(), 0);
}

Device::~Device() {
	m_device.destroy();
}