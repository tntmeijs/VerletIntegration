#ifndef GRAPHICS_GL_SHADER_HPP
#define GRAPHICS_GL_SHADER_HPP

#include "graphics/shader.hpp"

#include <memory>
#include <string_view>
#include <vector>

namespace vi::gl
{
	class GLShader : public Shader
	{
	public:
		/**
		 * Load an OpenGL shader from a file
		 * @param load_info	Information needed to create a shader
		 *
		 * @return	True on successful shader program creation, false otherwise
		 */
		bool Load(const ShaderLoadInfo& load_info) final override;
	};
}

#endif //! GRAPHICS_GL_SHADER_HPP
