
#pragma once

#include "graphics/IDrawable.h"
#include "graphics/PerspectiveCamera.h"
#include "init/IGameInit.h"

#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <vector>

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
	virtual ~GameInit3D();
	GameInit3D(GameInit3D&& other) = default;

	virtual void start();

	void add(std::unique_ptr<graphics::IDrawable> obj);

	virtual void draw();

	virtual void update(std::chrono::milliseconds dt);

private:
	bool fullscreen;
	int width;
	int height;
	std::string title;

	std::vector<std::unique_ptr<graphics::IDrawable>> drawables;

	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;

	PerspectiveCamera camera;
};

} //namespace init
} //namespace vngine
