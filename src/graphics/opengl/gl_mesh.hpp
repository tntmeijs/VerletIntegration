#ifndef GRAPHICS_OPENGL_MESH_HPP
#define GRAPHICS_OPENGL_MESH_HPP

#include "graphics/mesh.hpp"

#include "glad/glad.h"

#include <cstddef>

namespace vi::gl
{
	/**
	 * OpenGL implementation of a mesh object
	 */
	class GLMesh : public Mesh
	{
	public:
		/**
		 * Allocate VRAM for the vertex and index data
		 *
		 * @param info	Mesh create information structure that contains all information needed to create a mesh
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool AllocateMesh(const MeshCreateInfo& info) override;

		/**
		 * Deallocate any allocated device memory
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool DeallocateMesh() const override;

		/**
		 * Bind the mesh to the pipeline and render it
		 */
		virtual void RecordDrawCommands() const override;

	private:
		/**
		 * Generate VAO, VBO, and EBO buffers
		 */
		void GenerateBuffers();

		/**
		 * Convert the mesh usage enum to OpenGL buffer usage flags
		 *
		 * @param usage		Enum value that hints how often this mesh data will change
		 *
		 * @return OpenGL usage flag that corresponds to the specified mesh update frequency
		 */
		GLenum MeshUsageToOpenGLFlag(MeshUsage usage) const;

	private:
		/** Vertex array object */
		GLuint m_vao;

		/** Vertex buffer object */
		GLuint m_vbo;

		/** Element array object */
		GLuint m_ebo;

		/** Number of vertices in this mesh */
		std::size_t m_vertex_count;

		/** Indicates whether indices are used in this mesh */
		bool m_has_indices;

		/** Number of indices in this mesh */
		std::size_t m_index_count;
	};
}

#endif //! GRAPHICS_OPENGL_MESH_HPP
