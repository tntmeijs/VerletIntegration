#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <memory>

namespace vi
{
	/**
	 * Base class for loading and using shaders
	 */
	class Shader
	{
	public:
		/**
		 * Load a new shader from a source file
		 *
		 * @return	True when the shader was loaded successfully, false otherwise
		 */
		virtual bool Load() = 0;

		/**
		 * Get a pointer to the underlaying shader handle
		 *
		 * @return	Weak pointer to the shader handle
		 */
		virtual const std::weak_ptr<void> const Get() = 0;

	protected:
		/** Handle to use the shader in the renderer */
		std::shared_ptr<void> m_handle;
	};
}

#endif //! GRAPHICS_SHADER_HPP
