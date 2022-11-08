#include "vulkan-renderer/vulkan/renderer.hpp"

Backend::Backend(
	std::size_t width,
	std::size_t height,
	std::wstring window_name,
	std::string application_name
)	: m_instance{ application_name }
	, m_window{ width, height, window_name, &m_instance.get() }
	, m_device{ m_instance.get(), m_window.get_surface() }
{}

void Backend::loop() const noexcept {
	m_window.loop();
}