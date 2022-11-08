#include "vulkan-renderer/vulkan/instance.hpp"

#include "spdlog/spdlog.h"

#ifndef NDEBUG
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* data,
    void* user_data
) {
    if (severity <= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        spdlog::info(data->pMessage);
    }
    else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        spdlog::warn(data->pMessage);
    }
    else {
        spdlog::error(data->pMessage);
    }

    return VK_FALSE;
}
#endif

Instance::Instance(std::string application_name) {
    vk::ApplicationInfo app_info = {
        .pApplicationName = application_name.c_str(),
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "Trallala",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3
    };

    const std::array extensions {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#ifndef NDEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
    };

#ifdef NDEBUG
    const std::array <const char*, 0> layers {};
#else
    const std::array layers {
        "VK_LAYER_KHRONOS_validation"
    };

    vk::DebugUtilsMessengerCreateInfoEXT messenger_info {
        .messageSeverity = // vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                           // vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo    |
                           vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                           vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
        .messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral     |
                       vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                       vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
        .pfnUserCallback = debug_messenger
    };
#endif

    vk::InstanceCreateInfo instance_info {
#ifndef NDEBUG
        .pNext = &messenger_info,
#endif
        .pApplicationInfo = &app_info,
        .enabledLayerCount = static_cast<std::uint32_t>(layers.size()),
        .ppEnabledLayerNames = layers.data(),
        .enabledExtensionCount = static_cast<std::uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data()
    };

    auto [result, instance] = vk::createInstance(instance_info);

    if (result == vk::Result::eSuccess) {
        m_instance = instance;
        spdlog::info("Vulkan Instance successfully created");
    } else {
        auto error_message = std::format("Failed to create Vulkan instance! Error: {}", vk::to_string(result));

        spdlog::error(error_message);
        throw std::runtime_error(error_message);
    }

#ifndef NDEBUG
    m_loader = vk::DispatchLoaderDynamic(m_instance, vkGetInstanceProcAddr);
    auto [result_m, messenger] = instance.createDebugUtilsMessengerEXT(messenger_info, nullptr, m_loader);

    if (result_m == vk::Result::eSuccess) {
        m_messenger = messenger;
        spdlog::info("Vulkan Debug Messenger successfully created");
    }
    else {
        auto error_message = std::format("Failed to create Vulkan Debug Messenger! Error: {}", vk::to_string(result));

        spdlog::error(error_message);
        throw std::runtime_error(error_message);
    }
#endif
}

Instance::~Instance() {
#ifndef NDEBUG
    m_instance.destroyDebugUtilsMessengerEXT(m_messenger, nullptr, m_loader);
#endif
    m_instance.destroy();
}

const vk::Instance& Instance::get() const noexcept {
    return m_instance;
}