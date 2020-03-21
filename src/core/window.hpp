#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GLFW/glfw3.h"

#include <cstdint>

namespace vi
{
	class Window
	{
	public:
		/**
		 * Create a new window and set it as the current context
		 *
		 * @param width		Width of the window in pixels
		 * @param height	Height of the window in pixels
		 * @param title		Title of the window
		 */
		Window(std::uint32_t width, std::uint32_t height, const char* title);

		/**
		 * Check if the window is still open
		 * Should be used to determine if the main loop should remain active
		 *
		 * @return	True when the window is open, false when the window is about to close / is closed
		 */
		bool IsOpen() const;

	private:
		/** Current width of the window in pixels */
		std::uint32_t m_width;

		/** Current height of the window in pixels */
		std::uint32_t m_height;

		/** Current title of the window */
		const char* m_title;

		/** Window handle to this window */
		GLFWwindow* m_handle;
	};
}

#endif //! WINDOW_HPP
