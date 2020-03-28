#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace vi
{
	/** Forward declarations */
	class Window;

	/**
	 * Base class for a rendering back-end
	 * All rendering back-ends should derive from this class
	 */
	class Renderer
	{
	public:
		/**
		 * Save a reference to the window for future use
		 */
		Renderer(const Window& window) :
			m_window(window)
		{}

		/**
		 * Initialize the renderer
		 *
		 * @return	True when initialized successfully, false on error
		 */
		virtual bool Initialize() { return false; }

		/**
		 * Perform any actions to prepare for rendering (e.g. cull objects)
		 */
		virtual void PreRender() {}

		/**
		 * Render the scene
		 */
		virtual void Render() {}

		/**
		 * Any logic that should run after rendering the scene but before the frame ends
		 */
		virtual void PostRender() {}

	protected:
		/** Window to render to */
		const Window& m_window;
	};
}

#endif //! RENDERER_HPP
