#ifndef GRAPHICS_RENDERER_HPP
#define GRAPHICS_RENDERER_HPP

#include "graphics_enums.hpp"
#include "utility/log.hpp"

#include <cstdint>
#include <memory>

namespace vi
{
	namespace gl
	{
		class GLRenderer;
	}

	/**
	 * Base class for a rendering back-end
	 * All rendering back-ends should derive from this class
	 */
	class Renderer
	{
	public:
		/**
		 * Create a new renderer instance
		 *
		 * @param backend	Graphics API to use
		 *
		 * @return Pointer to the new renderer instance
		 */
		static std::shared_ptr<Renderer> Create(RenderingBackend backend);

	public:
		/**
		 * Initialize the renderer
		 *
		 * @param width		Initial width of the swapchain's back buffer
		 * @param height	Initial height of the swapchain's back buffer
		 *
		 * @return	True when initialized successfully, false on error
		 */
		virtual bool Initialize(std::uint32_t width, std::uint32_t height) = 0;

		/**
		 * Perform any actions to prepare for rendering (e.g. cull objects)
		 */
		virtual void PreRender() = 0;

		/**
		 * Render the scene
		 */
		virtual void Render() = 0;

		/**
		 * Any logic that should run after rendering the scene but before the frame ends
		 */
		virtual void PostRender() = 0;
	};
}

#endif //! GRAPHICS_RENDERER_HPP
