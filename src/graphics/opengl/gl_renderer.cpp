#include "gl_renderer.hpp"
#include "utility/log.hpp"
#include "core/window.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

vi::gl::GLRenderer::GLRenderer() :
	vao(0),
	vbo(0)
{}

bool vi::gl::GLRenderer::Initialize(std::uint32_t width, std::uint32_t height)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Unable to load OpenGL using GLAD.");
		return false;
	}

	LOG_INFO("OpenGL initialized.");

	//#TODO: Move this to the base renderer
	//#TODO: Wrap the viewport stuff in a new class
	glEnable(GL_DEPTH);
	glClearColor(255, 255, 0, 255);
	glViewport(0, 0, width, height);

	LOG_INFO("OpenGL renderer initialized.");

	//#TODO: create a resource loader
	//#DEBUG: this is all temporary
	ShaderSource vertex_shader = { ShaderType::VertexShader, "./resources/shaders/opengl/cloth_vs.glsl" };
	ShaderSource pixel_shader = { ShaderType::PixelShader, "./resources/shaders/opengl/cloth_ps.glsl" };
	ShaderCreateInfo create_info = { { vertex_shader, pixel_shader } };
	cloth_shader.Create(create_info);

	return true;
}

void vi::gl::GLRenderer::NewFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//#TODO: move this to the base renderer
	cloth_shader.Use();
}

vi::RenderingBackend vi::gl::GLRenderer::GetBackendType()
{
	return RenderingBackend::OpenGL;
}
