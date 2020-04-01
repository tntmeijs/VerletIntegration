#ifndef GRAPHICS_MESH_HPP
#define GRAPHICS_MESH_HPP

#include <cstddef>
#include <cstdint>

namespace vi
{
	/** Forward declarations */
	struct Vertex;

	/**
	 * Indicates how often the mesh data will be updated from the CPU
	 */
	enum class MeshUsage
	{
		MeshAlwaysStatic,	// Mesh data will be set once and never updated again
		MeshOccasionalUse,	// Mesh data will be set once and only used a few times
		MeshDynamicUpdate	// Mesh data will be set often and used often
	};

	/**
	 * All information needed to create a new mesh
	 */
	struct MeshCreateInfo
	{
		MeshUsage usage;

		// Vertex data
		const Vertex* vertex_data;
		std::size_t vertex_data_size;
		std::uint32_t vertex_stride_bytes;
		
		// Index data
		const std::uint32_t* index_data;
		std::size_t index_data_size;
	};

	/**
	 * Base mesh class
	 * This class takes care of vertex data management and uploads said data to the GPU
	 */
	class Mesh
	{
	public:
		/**
		 * Allocate VRAM for the vertex and index data
		 *
		 * The engine expects the following vertex layout:
		 *
		 * Attribute 0 - position:
		 *		POSITION_X
		 *		POSITION_Y
		 *		POSITION_Z
		 *
		 * Attribute 1 - normals
		 *		NORMAL_X
		 *		NORMAL_Y
		 *		NORMAL_Z
		 *
		 * Attribute 2 - texture coordinates
		 *		UV_S
		 *		UV_T
		 *
		 * Attribute 1 - color
		 *		COLOR_R
		 *		COLOR_G
		 *		COLOR_B
		 *		COLOR_A		 
		 *
		 * @param info	Mesh create information structure that contains all information needed to create a mesh
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool AllocateMesh(const MeshCreateInfo& info) = 0;

		/**
		 * Deallocate any allocated device memory
		 *
		 * @return True when successful, false otherwise
		 */
		virtual bool DeallocateMesh() const = 0;

		/**
		 * Record commands necessary to bind / render this mesh
		 */
		virtual void RecordDrawCommands() const = 0;
	};
}

#endif //! GRAPHICS_MESH_HPP
