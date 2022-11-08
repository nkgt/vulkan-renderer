#include "vulkan-renderer/vulkan/renderer.hpp"

Backend::Backend(std::string application_name)
	: m_instance{ application_name }
	, m_device{ m_instance.get() }
{}