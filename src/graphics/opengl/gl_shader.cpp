#include "gl_shader.hpp"

#include "utility/log.hpp"

#include "glad/glad.h"

#include <cstdint>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

using ShaderData = std::pair<GLuint, std::string>;

vi::gl::GLShader::GLShader() :
	m_program(0),
	m_success(false)
{}

vi::gl::GLShader::~GLShader()
{
	if (m_success)
	{
		glDeleteProgram(m_program);
	}
}

bool vi::gl::GLShader::Create(const ShaderCreateInfo& load_info)
{
	std::vector<ShaderData> datas = {};
	datas.reserve(load_info.sources.size());

	// Load all source code from the files and create an OpenGL shader handle
	for (const auto& source : load_info.sources)
	{
		// Open a file and dump the source code into a string
		std::string source_code = ReadShaderSourceFromFile(source.file);

		if (source_code.length() > 0)
		{
			// Create all shader objects already based on the type
			GLenum shader_type = GL_INVALID_ENUM;
			switch (source.type)
			{
				case ShaderType::VertexShader:
					shader_type = GL_VERTEX_SHADER;
					break;

				case ShaderType::ComputeShader:
					shader_type = GL_COMPUTE_SHADER;
					break;

				case ShaderType::PixelShader:
					shader_type = GL_FRAGMENT_SHADER;
					break;

				default:
					break;
			}

			if (shader_type != GL_INVALID_ENUM)
			{
				GLuint shader = glCreateShader(shader_type);
				datas.push_back({ shader, source_code });
			}
			else
			{
				LOG_FATAL("Unknown / invalid shader type specified.");
				return false;
			}
		}
		else
		{
			LOG_FATAL("Shader source code may not be empty.");
			return false;
		}
	}

	// Compile all shaders
	LOG_INFO("Starting shader compilation...");
	std::uint8_t index = 0;
	for (const auto& data : datas)
	{
		// Log shader compilation progress
		{
			std::string msg = "Compiling shader ";
			msg.append(std::to_string(index + 1));
			msg.append("/");
			msg.append(std::to_string(datas.size()));
			msg.append(".");
			LOG_INFO(msg);
		}

		// Attempt to compile the shader
		const GLchar* const source = data.second.c_str();
		glShaderSource(data.first, 1, &source, nullptr);
		glCompileShader(data.first);

		// Check for any errors
		GLint status_code = -1;
		glGetShaderiv(data.first, GL_COMPILE_STATUS, &status_code);

		if (status_code)
		{
			LOG_INFO("Compilation successful.");
		}
		else
		{
			GLint msg_length = 0;
			glGetShaderiv(data.first, GL_INFO_LOG_LENGTH, &msg_length);

			std::vector<GLchar> error_log(msg_length);
			glGetShaderInfoLog(data.first, msg_length, nullptr, error_log.data());

			std::string msg = "Shader compile error: ";
			msg.append(error_log.data());
			msg.append("        Relevant file: ");
			msg.append(load_info.sources[index].file);
			LOG_ERROR(msg);

			// Delete the shader to make sure it does not leak
			glDeleteShader(data.first);
			return false;
		}

		++index;
	}

	// Create a shader program
	m_program = glCreateProgram();
	for (const auto& data : datas)
	{
		// Add each shader to the program
		glAttachShader(m_program, data.first);
	}
	glLinkProgram(m_program);

	// No matter what happened when linking the program, shaders can always be deleted at this point
	for (const auto& data : datas)
	{
		glDeleteShader(data.first);
	}

	// Check for any errors
	GLint status_code = -1;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status_code);

	if (status_code)
	{
		LOG_INFO("Program linked successfully.");
	}
	else
	{
		GLint msg_length = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &msg_length);

		std::vector<GLchar> error_log(msg_length);
		glGetProgramInfoLog(m_program, msg_length, nullptr, error_log.data());

		std::string msg = "Program link error: ";
		msg.append(error_log.data());
		LOG_ERROR(msg);

		// Delete the program to prevent leaking it
		glDeleteProgram(m_program);
		return false;
	}

	// Save the program for future use
	//m_handle = std::make_shared<void>(program_handle);

	LOG_INFO("Shader created successfully.");
	m_success = true;
	return true;
}

void vi::gl::GLShader::Use() const
{
	glUseProgram(m_program);
}

std::string vi::gl::GLShader::ReadShaderSourceFromFile(std::string_view source) const
{
	std::string source_code = "";
	std::ifstream file(source.data(), std::ios::beg);
	
	if (!file)
	{
		// File not found, corrupt, or any other issues
		std::string msg = "Cannot open shader: ";
		msg.append(source);
		LOG_ERROR(msg);
	}
	else
	{
		std::string line = "";
		while (std::getline(file, line))
		{
			// Read a single shader source line at a time
			source_code.append(line);
			source_code.append("\n");
		}

		// End of file
		source_code.append("\0");
	}

	file.close();
	return source_code;
}
