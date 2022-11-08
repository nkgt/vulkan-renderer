#include "vulkan-renderer/vulkan/device.hpp"
#include "spdlog/spdlog.h"

#include <optional>
#include <set>

struct QueueFamilyIncides {
	std::optional<std::uint32_t> graphics_family;
	std::optional<std::uint32_t> present_family;

	bool is_complete() const noexcept {
		return graphics_family.has_value() && present_family.has_value();
	}
};

static QueueFamilyIncides find_queue_families(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) {
	std::uint32_t index = 0;
	QueueFamilyIncides indices;

	for (const auto& family : device.getQueueFamilyProperties()) {
		if (family.queueFlags & vk::QueueFlagBits::eGraphics) {
			indices.graphics_family = index;
		}

		if (const auto [_, supported] = device.getSurfaceSupportKHR(index, surface); supported) {
			indices.present_family = index;
		}

		if (indices.is_complete()) {
			break;
		}

		index += 1;
	}

	return indices;
}

static bool is_device_suitable(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface) {
	const auto properties = device.getProperties();
	const auto features = device.getFeatures();
	const auto indices = find_queue_families(device, surface);

	return properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu &&
		   features.geometryShader &&
		   indices.graphics_family.has_value();
}

Device::Device(const vk::Instance& instance, const vk::SurfaceKHR& surface) {
	auto [result, devices] = instance.enumeratePhysicalDevices();

	if (result == vk::Result::eSuccess) {
		for (const auto& device : devices) {
			if (is_device_suitable(device, surface)) {
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
	const auto queue_family_indices = find_queue_families(m_physical_device, surface);

	std::vector<vk::DeviceQueueCreateInfo> queue_infos;
	queue_infos.reserve(2);

	std::set unique_queue_families_indices = {
		queue_family_indices.graphics_family.value(),
		queue_family_indices.present_family.value()
	};

	for (const auto index : unique_queue_families_indices) {
		spdlog::info("Creating queue with index {}", index);

		vk::DeviceQueueCreateInfo queue_info{
			.queueFamilyIndex = queue_family_indices.graphics_family.value(),
			.queueCount = 1,
			.pQueuePriorities = &priority
		};
		queue_infos.push_back(queue_info);
	}

	vk::PhysicalDeviceFeatures device_features {};

	vk::DeviceCreateInfo create_info{
		.queueCreateInfoCount = static_cast<std::uint32_t>(queue_infos.size()),
		.pQueueCreateInfos = queue_infos.data(),
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = nullptr,
		.pEnabledFeatures = &device_features
	};

	const auto [result_create, device] = m_physical_device.createDevice(create_info);

	if (result_create == vk::Result::eSuccess) {
		m_device = device;
		spdlog::info("Logical Vulkan device created");
	}
	else {
		auto error_message = std::format("Failed to create Vulkan device! Error: {}", vk::to_string(result_create));

		spdlog::error(error_message);
		throw std::runtime_error(error_message);
	}

	m_graphics_queue = m_device.getQueue(queue_family_indices.graphics_family.value(), 0);
	m_present_queue = m_device.getQueue(queue_family_indices.present_family.value(), 0);
}

Device::~Device() {
	m_device.destroy();
}