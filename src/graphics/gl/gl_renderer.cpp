#include "gl_renderer.hpp"
#include "utility/log.hpp"
#include "core/window.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

vi::gl::GLRenderer::GLRenderer(const Window& window) :
	Renderer(window),
	vao(0),
	vbo(0)
{}

bool vi::gl::GLRenderer::Initialize()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Unable to load OpenGL using GLAD.");
		return false;
	}

	LOG_INFO("OpenGL initialized.");

	glEnable(GL_DEPTH);
	glClearColor(255, 255, 0, 255);
	glViewport(0, 0, m_window.GetWidth(), m_window.GetHeight());

	float points[] =
	{
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
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

	return true;
}

void vi::gl::GLRenderer::PreRender()
{}

void vi::gl::GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glDrawArrays(GL_POINTS, 0, 4);

	glfwSwapBuffers(m_window.GetHandle());
}

void vi::gl::GLRenderer::PostRender()
{}
