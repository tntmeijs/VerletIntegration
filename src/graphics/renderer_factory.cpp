#include "renderer_factory.hpp"
#include "renderer.hpp"
#include "utility/log.hpp"
#include "opengl/gl_renderer.hpp"

using namespace vi;
using namespace vi::gl;

std::shared_ptr<Renderer> RendererFactory::CreateRenderer(RenderingBackend backend, const Window& window)
{
	switch (backend)
	{
		// OpenGL renderer
		case RenderingBackend::OpenGL:
			return std::shared_ptr<Renderer>(new GLRenderer(window));
			break;

		// Invalid
		default:
			LOG_FATAL("Invalid rendering back-end specified, this should never happen.");
			break;
	}

	return std::shared_ptr<Renderer>(new Renderer(window));
}
