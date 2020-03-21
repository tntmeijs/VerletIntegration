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

	// Save the reference to this instance for use in the callback functions
	glfwSetWindowUserPointer(m_handle, this);

	// Register callbacks
	glfwSetKeyCallback(m_handle, KeyCallbackStatic);
}

bool vi::Window::IsOpen() const
{
	return !glfwWindowShouldClose(m_handle);
}

void vi::Window::Close() const
{
	glfwSetWindowShouldClose(m_handle, true);
}

void vi::Window::PollInput() const
{
	glfwPollEvents();
}

void vi::Window::KeyCallbackStatic(
	GLFWwindow* window,
	std::int32_t key,
	std::int32_t scancode,
	std::int32_t action,
	std::int32_t mods)
{
	// Suppress "unreferenced formal parameter" warnings
	mods;
	scancode;

	// Pointer to the window class has been stored as window user data
	const Window* const instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (!instance)
	{
		// Should never happen
		LOG_ERROR("Invalid instance, check the window user data pointer.");
		return;
	}

	// This is safe because the "Keycode" enum matches GLFW's numbering perfectly
	Keycode keycode = static_cast<Keycode>(key);

	// Fire the correct key callback
	if (action == GLFW_PRESS && instance->OnKeyPressed)
	{
		instance->OnKeyPressed(keycode);
	}
	else if (action == GLFW_RELEASE && instance->OnKeyReleased)
	{
		instance->OnKeyReleased(keycode);
	}
}
