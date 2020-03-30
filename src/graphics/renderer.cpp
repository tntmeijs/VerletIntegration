#include "renderer.hpp"
#include "opengl/gl_renderer.hpp"

std::shared_ptr<vi::Renderer> vi::Renderer::Create(RenderingBackend backend)
{
	switch (backend)
	{
		// OpenGL renderer
		case RenderingBackend::OpenGL:
			return std::shared_ptr<Renderer>(new vi::gl::GLRenderer);
			break;

			// Invalid
		default:
			LOG_FATAL("Invalid rendering back-end specified, this should never happen.");
			return nullptr;
			break;
	}
}
