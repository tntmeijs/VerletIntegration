#ifndef GRAPHICS_GL_SHADER_HPP
#define GRAPHICS_GL_SHADER_HPP

#include "graphics/shader.hpp"

#include "glad/glad.h"

#include <string_view>
#include <string>

namespace vi::gl
{
	/**
	 * OpenGL implementation of a shader
	 */
	class GLShader : public Shader
	{
	public:
		GLShader();

		/**
		 * Deletes the shader program to prevent it from leaking
		 */
		~GLShader();

		/**
		 * Create a new OpenGL shader from source files
		 * @param load_info	Information needed to create a shader
		 *
		 * @return	True on successful shader program creation, false otherwise
		 */
		bool Create(const ShaderCreateInfo& load_info) final override;

		/**
		 * Activate the shader by calling "glUseProgram"
		 */
		void Use() const;

	private:
		/**
		 * Load the shader text from a file
		 *
		 * @return	Shader source code as a single string object
		 */
		std::string ReadShaderSourceFromFile(std::string_view source) const;

	private:
		/** Shader program handle */
		GLuint m_program;

		/** Indicates whether the program linked successfully */
		bool m_success;
	};
}

#endif //! GRAPHICS_GL_SHADER_HPP
