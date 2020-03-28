#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <memory>
#include <string_view>
#include <vector>

namespace vi
{
	/**
	 * All available shader types
	 */
	enum class ShaderType
	{
		VertexShader,
		ComputeShader,
		PixelShader
	};

	/**
	 * A single shader source file and it's type
	 */
	struct ShaderSource
	{
		ShaderType type;
		std::string_view file;
	};

	/**
	 * All shader sources that makes up a single shader
	 */
	struct ShaderLoadInfo
	{
		std::vector<ShaderSource> sources;
	};

	/**
	 * Base class for loading and using shaders
	 */
	class Shader
	{
	public:
		/**
		 * Load a new shader from a source file
		 * @param load_info	Information needed to create a shader
		 *
		 * @return	True when the shader was loaded successfully, false otherwise
		 */
		virtual bool Load(const ShaderLoadInfo& load_info) = 0;

		/**
		 * Get a pointer to the underlaying shader handle
		 *
		 * @return	Weak pointer to the shader handle
		 */
		std::weak_ptr<void> Get() { return m_handle; }

	protected:
		/** Handle to use the shader in the renderer */
		std::shared_ptr<void> m_handle;
	};
}

#endif //! GRAPHICS_SHADER_HPP
