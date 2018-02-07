
#include "init/GameInit3D.h"

#include <GL/glew.h>

namespace vngine {
namespace init {

GameInit3D::GameInit3D(bool fullscreen, int width, int height, std::string title) :
	fullscreen(fullscreen),
	width(width),
	height(height),
	title(title)
{}

GameInit3D::~GameInit3D()
{}

void GameInit3D::start()
{
	if (!glfwInit()) {
		throw std::runtime_error("Failed to init GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = std::unique_ptr<GLFWwindow>(
		glfwCreateWindow(
			width, 
			height,
			title,
			fullscreen ? glfwGetPrimaryMonitor() : NULL,
			NULL),
		[](GLFWwindow* me) { glfwDestroyWindow(me); }
	);

	if (!window) {
		throw std::runtime_error("Failed to open window");
	}

	glfwMakeContextCurrent(window);
	glewExperimental=true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to init GLEW");
	}

	std::chrono::high_resolution_clock::time_point last = std::chrono::high_resolution_clock::now();

	do {
		draw();

		std::chrono::high_resolution_clock::time_point next = std::chrono::high_resolution_clock::now();
		update(next - last);
		last = next;

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwWindowShouldClose(window) == 0);
}

}
}
