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

#include "vulkan/vulkan.hpp"

#include <string>

class Instance {
public:
    explicit Instance(std::string application_name);
    ~Instance();

    const vk::Instance& get() const noexcept;

private:
#ifndef NDEBUG
    vk::DebugUtilsMessengerEXT m_messenger;
    vk::DispatchLoaderDynamic m_loader;
#endif
    vk::Instance m_instance;
};