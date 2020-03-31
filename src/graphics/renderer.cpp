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

void vi::Renderer::Render() const
{
	for (const auto& mesh : m_mesh_list)
	{
		mesh->RecordDrawCommands();
	}
}

void vi::Renderer::Destroy()
{
	for (const auto& mesh : m_mesh_list)
	{
		mesh->DeallocateMesh();
	}
}

std::weak_ptr<vi::Mesh> vi::Renderer::CreateMesh()
{
	std::weak_ptr<Mesh> mesh_handle;
	std::shared_ptr<Mesh> new_mesh;

	switch (GetBackendType())
	{
		// OpenGL renderer
		case RenderingBackend::OpenGL:
			new_mesh = std::make_shared<gl::GLMesh>();
			break;

			// Invalid
		default:
			LOG_FATAL("Invalid rendering back-end specified, this should never happen. Unable to create a mesh");
			break;
	}

	// Register the new mesh to the renderer
	if (new_mesh)
	{
		m_mesh_list.push_back(new_mesh);
		mesh_handle = new_mesh;
	}

	// The renderer manages the lifetime of the mesh, not the user
	return mesh_handle;
}
