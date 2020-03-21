#include "window.hpp"
#include "utility/log.hpp"

vi::Window::Window(std::uint32_t width, std::uint32_t height, const char* title) :
	m_width(width),
	m_height(height),
	m_title(title),
	m_handle(nullptr)
{
	if (!glfwInit())
	{
		LOG_FATAL("Unable to initialize GLFW.");
		return;
	}

	LOG_INFO("GLFW initialized.");

	m_handle = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
	if (!m_handle)
	{
		LOG_FATAL("Error creating a GLFW window.");
		return;
	}

	LOG_INFO("GLFW window created successfully.");

	glfwMakeContextCurrent(m_handle);
}

bool vi::Window::IsOpen() const
{
	return !glfwWindowShouldClose(m_handle);
}
