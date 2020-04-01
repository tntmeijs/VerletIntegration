#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

#include "keycodes.hpp"
#include "graphics/graphics_enums.hpp"

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
		Window(std::uint32_t width, std::uint32_t height, const char* title, RenderingBackend backend);

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

		/**
		 * Get the width of the window's client area in pixels
		 *
		 * @return	Window width in pixels
		 */
		std::uint32_t GetWidth() const;

		/**
		 * Get the height of the window's client area in pixels
		 *
		 * @return	Window height in pixels
		 */
		std::uint32_t GetHeight() const;

		/**
		 * Get a handle to the window
		 */
		GLFWwindow* const GetHandle() const;

		/**
		 * Get the active rendering back-end for this window
		 */
		RenderingBackend GetRenderingBackend() const;

		/**
		 * Swap the back buffer
		 */
		void NextFrame() const;

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
		//#TODO: portable and abstracted method to pass OpenGL version information to this function
		/**
		 * Set the window hints for an OpenGL context
		 */
		void ConfigureOpenGLWindowHints();

	private:
		/** Current width of the window in pixels */
		std::uint32_t m_width;

		/** Current height of the window in pixels */
		std::uint32_t m_height;

		/** Current title of the window */
		const char* m_title;

		/** Window handle to this window */
		GLFWwindow* m_handle;

		/** Rendering back-end set for this window */
		RenderingBackend m_graphics_backend;
	};
}

#endif //! CORE_WINDOW_HPP
