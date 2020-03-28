#ifndef GRAPHICS_GL_RENDERER_HPP
#define GRAPHICS_GL_RENDERER_HPP

#include "graphics/renderer.hpp"

#include <cstdint>

namespace vi
{
	/** Forward declarations */
	class Window;

	namespace gl
	{
		/**
		 * An OpenGL-based rendering back-end
		 */
		class GLRenderer : public Renderer
		{
		public:
			/**
			 * Initialize members, initialize the base class
			 */
			GLRenderer(const Window& window);

			/**
			 * Initialize the renderer
			 *
			 * @return	True when initialized successfully, false on error
			 */
			bool Initialize() final override;

			/**
			 * Perform any actions to prepare for rendering (e.g. cull objects)
			 */
			void PreRender() final override;

			/**
			 * Render the scene
			 */
			void Render() final override;

			/**
			 * Any logic that should run after rendering the scene but before the frame ends
			 */
			void PostRender() final override;

		private:
			// This is all temporary until we have a few points rendering on screen
			std::uint32_t vao;
			std::uint32_t vbo;
		};
	}
}

#endif //! GRAPHICS_GL_RENDERER_HPP
