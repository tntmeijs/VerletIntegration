#ifndef GRAPHICS_RENDERER_HPP
#define GRAPHICS_RENDERER_HPP

#include "graphics_enums.hpp"
#include "utility/log.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace vi
{
	/** Forward declarations */
	class Mesh;

	/**
	 * Base class for a rendering back-end
	 * All rendering back-ends should derive from this class
	 */
	class Renderer
	{
	public:
		/**
		 * Create a new renderer instance
		 *
		 * @param backend	Graphics API to use
		 *
		 * @return Pointer to the new renderer instance
		 */
		static std::shared_ptr<Renderer> Create(RenderingBackend backend);

	public:
		/**
		 * Initialize the renderer
		 *
		 * @param width		Initial width of the swapchain's back buffer
		 * @param height	Initial height of the swapchain's back buffer
		 *
		 * @return	True when initialized successfully, false on error
		 */
		virtual bool Initialize(std::uint32_t width, std::uint32_t height) = 0;

		/**
		 * Used to retrieve the graphics API type from a specialized renderer instance using a base class pointer
		 *
		 * @return Graphics API used to instantiate this renderer
		 */
		virtual RenderingBackend GetBackendType() = 0;

		/**
		 * Clear the back buffer to prepare for a new frame (this includes color and depth buffers)
		 */
		virtual void NewFrame() = 0;

		/**
		 * Render the scene
		 */
		void Render() const;

		/**
		 * Deallocate all used resources
		 */
		void Destroy();

	public:
		/**
		 * Create a new mesh object and save it in the list of meshes to render
		 *
		 * @return Weak pointer to the new mesh
		 */
		std::weak_ptr<Mesh> CreateMesh();

	protected:
		//#TODO: Add a proper scene graph
		/** All meshes that should be rendered */
		std::vector<std::shared_ptr<Mesh>> m_mesh_list;
	};
}

#endif //! GRAPHICS_RENDERER_HPP
