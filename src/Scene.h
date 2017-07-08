
#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

#include "Character.h"
#include "Background.h"

class Scene {
public:
	Scene();
	~Scene();
	Scene(const Scene& s);


	void setBackground(Background b);

	void enterLeft(Character* c);
	void enterRight(Character* c);

	void draw();

private:
	std::vector<Character*> chars;
	Background* bg;

};

#endif //_SCENE_H_

