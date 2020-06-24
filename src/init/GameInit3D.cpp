
#include "init/GameInit3D.h"
#include "Exceptions.h"

#include <functional>

namespace vngine {
namespace init {

void errorHandler(int error, const char* desc)
{
	throw GLException(std::string(desc) + " (" + std::to_string(error) + ")");
}

GameInit3D::GameInit3D(bool fullscreen, int width, int height, std::string title) :
	fullscreen(fullscreen),
	width(width),
	height(height),
	title(title)
{
	if (!glfwInit()) {
		throw std::runtime_error("Failed to init GLFW");
	}

	glfwSetErrorCallback(&errorHandler);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>(
		glfwCreateWindow(
			width, 
			height,
			title.c_str(),
			fullscreen ? glfwGetPrimaryMonitor() : NULL,
			NULL),
		[](GLFWwindow* me) { glfwDestroyWindow(me); }
	);

	if (!window) {
		throw std::runtime_error("Failed to open window");
	}

	glfwMakeContextCurrent(window.get());
	glewExperimental=true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to init GLEW");
	}

	glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
	
GameInit3D::~GameInit3D()
{
	//glfwTerminate();
}

void GameInit3D::start()
{

	std::chrono::high_resolution_clock::time_point last = std::chrono::high_resolution_clock::now();
	GLenum error1 = glGetError();
	if (error1 != GL_NO_ERROR) {
		throw vngine::GLException("Oh geez.");
	}
	do {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			throw vngine::GLException(std::string(reinterpret_cast<const char*>(gluErrorString(error))));
		}
		std::chrono::high_resolution_clock::time_point next = std::chrono::high_resolution_clock::now();
		update(std::chrono::duration_cast<std::chrono::milliseconds>(next - last));
		last = next;
		error = glGetError();
		if (error != GL_NO_ERROR) {
			printf("here2");
			throw vngine::GLException(std::string(reinterpret_cast<const char*>(gluErrorString(error))));
		}

		draw();

		glfwSwapBuffers(window.get());
		glfwPollEvents();

	} while (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window.get()) == 0);
}

void GameInit3D::add(std::unique_ptr<graphics::IDrawable<float, 3>> obj)
{
	drawables.push_back(std::move(obj));
}

void GameInit3D::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& drawable : drawables) {
		drawable->draw();
	}
}

void GameInit3D::update(std::chrono::milliseconds /*dt*/)
{

}

}
}
