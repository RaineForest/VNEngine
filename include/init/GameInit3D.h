
#pragma once

#include "init/IGameInit.h"

#include <functional>
#include <GL/glfw.h>
#include <memory>
#include <string>

namespace vngine {
namespace init {

class GameInit3D : public IGameInit
{
public:
	GameInit3D(
		bool fullscreen = false, 
		int width = 1280,
		int height = 720,
		std::string title = "Game"
	);
	~GameInit3D();

	void start();

	void draw();

	void add(IDrawable* obj);
	void remove(IDrawable* obj);

	void update(std::chrono::milliseconds dt);

private:
	bool fullscreen;
	int width;
	int height;
	std::string title;

	std::unique_ptr<GLFWwindow> window;
};

} //namespace init
} //namespace vngine
