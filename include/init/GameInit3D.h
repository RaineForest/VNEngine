
#pragma once

#include "graphics/IDrawable.h"
#include "init/IGameInit.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

struct GLFWwindow;

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

	void add(std::unique_ptr<graphics::IDrawable<float, 3>> obj);

	virtual void draw();

	virtual void update(std::chrono::milliseconds dt);

private:
	bool fullscreen;
	int width;
	int height;
	std::string title;

	std::vector<std::unique_ptr<graphics::IDrawable<float, 3>>> drawables;

	std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> window;
};

} //namespace init
} //namespace vngine
