#ifndef GRAPHICS_OPENGL_MESH_HPP
#define GRAPHICS_OPENGL_MESH_HPP

#include "graphics/mesh.hpp"

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
		 * This class does not manage the binary blob's memory
		 * The pointer to the data is stored until "UploadToGPU" has been called
		 *
		 * @sa UploadToGPU()
		 *
		 * @param vertex_blob		Pointer to a blob of vertex data
		 * @param vertex_data_size	Size of the specified vertex data blob in Bytes
		 * @param index_blob		Pointer to a blob of index data
		 * @param index_data_size	Size of the specified index data blob in Bytes
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool AllocateMemory(
			const void* const vertex_blob,
			std::size_t vertex_data_size,
			const void* const index_blob,
			std::size_t index_data_size) override;

		/**
		 * Upload the specified vertex and index data to the allocated GPU memory
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool UploadToGPU() const override;

		/**
		 * Deallocate any allocated device memory
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool DeallocateMemory() const override;
	};
}

#endif //! GRAPHICS_OPENGL_MESH_HPP
