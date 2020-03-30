#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <algorithm>
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
	struct ShaderCreateInfo
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
		 * Create a new shader from source files
		 * @param load_info	Information needed to create a shader
		 *
		 * @return	True when the shader was loaded successfully, false otherwise
		 */
		virtual bool Create(const ShaderCreateInfo& load_info) = 0;
	};
}

#endif //! GRAPHICS_SHADER_HPP
