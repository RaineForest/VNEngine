
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
		std::unique_ptr<ICamera> camera = std::make_unique<PerspectiveCamera>(45.0f, static_cast<float>(1280)/static_cast<float>(720), 0.1f, 100.0f),
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
	std::unique_ptr<ICamera> camera;
	bool fullscreen;
	int width;
	int height;
	std::string title;

	std::vector<std::unique_ptr<graphics::IDrawable>> drawables;

	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;

};

} //namespace init
} //namespace vngine
