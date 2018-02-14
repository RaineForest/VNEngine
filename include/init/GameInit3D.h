
#pragma once

#include "init/IGameInit.h"

#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

namespace vngine {
namespace init {

using namespace graphics;

class GameInit3D : public IGameInit
{
public:
	GameInit3D(
		bool fullscreen = false, 
		int width = 1280,
		int height = 720,
		std::string title = "Game"
	);
	virtual ~GameInit3D();

	virtual void start();

	virtual void draw();

	/*
	void add(IDrawable<float, 3>* obj);
	void remove(IDrawable<float, 3>* obj);
	*/

	virtual void update(std::chrono::milliseconds dt);

private:
	bool fullscreen;
	int width;
	int height;
	std::string title;

	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};

} //namespace init
} //namespace vngine
