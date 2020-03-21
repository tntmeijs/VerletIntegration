#include "renderer.hpp"
#include "utility/log.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

vi::Renderer::Renderer()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Unable to load OpenGL using GLAD.");
		return;
	}

	LOG_INFO("OpenGL initialized.");
}
