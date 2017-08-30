
#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

#include "Character.h"
#include "Background.h"

class Scene {
public:
	Scene();
	~Scene();

	virtual void draw() = 0;
};

#endif //_SCENE_H_

