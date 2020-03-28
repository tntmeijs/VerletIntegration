#ifndef GRAPHICS_RENDERER_FACTORY_HPP
#define GRAPHICS_RENDERER_FACTORY_HPP

#include "graphics_enums.hpp"

#include <memory>

namespace vi
{
	/** Forward declarations */
	class Renderer;
	class Window;

	/**
	 * Factory used to create a rendering back-end of a specific type
	 */
	class RendererFactory
	{
	public:
		/**
		 * Create a new renderer using the specified rendering back-end
		 *
		 * @param backend	The rendering back-end to use for the new renderer
		 * @param window	Reference to the window used to render this application
		 *
		 * @return	New renderer object
		 */
		static std::shared_ptr<Renderer> CreateRenderer(RenderingBackend backend, const Window& window);

	private:
		/** Do not allow any instances of this class */
		RendererFactory();
	};
}

#endif //! GRAPHICS_RENDERER_FACTORY_HPP
