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

	glEnable(GL_DEPTH);
	glClearColor(255, 255, 0, 255);
	glViewport(0, 0, width, height);

	float points[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	LOG_INFO("OpenGL renderer initialized.");

	//#TODO: create a resource loader
	//#DEBUG: this is all temporary
	ShaderSource vertex_shader = { ShaderType::VertexShader, "./resources/shaders/opengl/cloth_vs.glsl" };
	ShaderSource pixel_shader = { ShaderType::PixelShader, "./resources/shaders/opengl/cloth_ps.glsl" };
	ShaderCreateInfo create_info = { { vertex_shader, pixel_shader } };
	cloth_shader.Create(create_info);

	return true;
}

void vi::gl::GLRenderer::PreRender()
{}

void vi::gl::GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);
	cloth_shader.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void vi::gl::GLRenderer::PostRender()
{}
