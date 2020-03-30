#include "renderer.hpp"
#include "opengl/gl_renderer.hpp"
#include "opengl/gl_mesh.hpp"

std::shared_ptr<vi::Renderer> vi::Renderer::Create(RenderingBackend backend)
{
	switch (backend)
	{
			// OpenGL renderer
		case RenderingBackend::OpenGL:
			return std::shared_ptr<Renderer>(new gl::GLRenderer);
			break;

			// Invalid
		default:
			LOG_FATAL("Invalid rendering back-end specified, this should never happen.");
			return nullptr;
			break;
	}
}

std::shared_ptr<vi::Mesh> vi::Renderer::CreateMesh()
{
	switch (GetBackendType())
	{
		// OpenGL renderer
		case RenderingBackend::OpenGL:
			return std::shared_ptr<gl::GLMesh>(new gl::GLMesh);
			break;

			// Invalid
		default:
			LOG_FATAL("Invalid rendering back-end specified, this should never happen.");
			return nullptr;
			break;
	}
}
