#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "keycodes.hpp"

#include "GLFW/glfw3.h"

#include <cstdint>
#include <functional>

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

		/**
		 * Request the window to close
		 */
		void Close() const;

		/**
		 * Poll GLFW for input
		 */
		void PollInput() const;

	public:
		/**
		 * Key pressed callback
		 */
		std::function<void(Keycode)> OnKeyPressed;

		/**
		 * Key released callback
		 */
		std::function<void(Keycode)> OnKeyReleased;

	private:
		/**
		 * Static function to handle key callbacks
		 * The window user data pointer is used to invoke the public input member callbacks
		 */
		static void KeyCallbackStatic(
			GLFWwindow* window,
			std::int32_t key,
			std::int32_t scancode,
			std::int32_t action,
			std::int32_t mods);

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
