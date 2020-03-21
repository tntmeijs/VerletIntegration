#include "core/window.hpp"
#include "renderer.hpp"
#include "utility/log.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

vi::Renderer::Renderer(const Window& window)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Unable to load OpenGL using GLAD.");
		return;
	}

	LOG_INFO("OpenGL initialized.");

	glEnable(GL_DEPTH);
	glClearColor(255, 255, 0, 255);
	glViewport(0, 0, window.GetWidth(), window.GetHeight());
}

void vi::Renderer::Render(const Window& window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(window.GetHandle());
}
