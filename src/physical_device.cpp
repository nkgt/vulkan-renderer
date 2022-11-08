#include "vulkan-renderer/vulkan/physical_device.hpp"
#include "spdlog/spdlog.h"

PhysicalDevice::PhysicalDevice(const vk::Instance& instance) {
	auto [result, devices] = instance.enumeratePhysicalDevices();

	if (result == vk::Result::eSuccess) {
		for (const auto& device : devices) {
			auto properties = device.getProperties();
			auto features = device.getFeatures();

			if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu && features.geometryShader) {
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
}