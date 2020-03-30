#ifndef GRAPHICS_OPENGL_RENDERER_HPP
#define GRAPHICS_OPENGL_RENDERER_HPP

#include "graphics/graphics_enums.hpp"
#include "graphics/opengl/gl_shader.hpp"
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
			GLRenderer();

			/**
			 * Initialize the renderer
			 *
			 * @param width		Initial width of the swapchain's back buffer
			 * @param height	Initial height of the swapchain's back buffer
			 *
			 * @return	True when initialized successfully, false on error
			 */
			virtual bool Initialize(std::uint32_t width, std::uint32_t height) override;

			/**
			 * Perform any actions to prepare for rendering (e.g. cull objects)
			 */
			virtual void PreRender() override;

			/**
			 * Render the scene
			 */
			virtual void Render() override;

			/**
			 * Any logic that should run after rendering the scene but before the frame ends
			 */
			virtual void PostRender() override;

			/**
			 * Used to retrieve the graphics API type from a specialized renderer instance using a base class pointer
			 *
			 * @return Graphics API used to instantiate this renderer
			 */
			virtual RenderingBackend GetBackendType() override;

		private:
			// This is all temporary until we have a few points rendering on screen
			std::uint32_t vao;
			std::uint32_t vbo;
			GLShader cloth_shader;
		};
	}
}

#endif //! GRAPHICS_OPENGL_RENDERER_HPP
