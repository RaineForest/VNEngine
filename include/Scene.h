
#pragma once

#include <vector>

#include "Character.h"
#include "Background.h"

class Scene {
public:
	Scene();
	~Scene();

	virtual void draw() = 0;
};
