#ifndef GRAPHICS_MESH_HPP
#define GRAPHICS_MESH_HPP

#include <cstddef>

namespace vi
{
	/**
	 * Base mesh class
	 * This class takes care of vertex data management and uploads said data to the GPU
	 */
	class Mesh
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
			std::size_t index_data_size) = 0;

		/**
		 * Upload the specified vertex and index data to the allocated GPU memory
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool UploadToGPU() const = 0;

		/**
		 * Deallocate any allocated device memory
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool DeallocateMemory() const = 0;
	};
}

#endif //! GRAPHICS_MESH_HPP
