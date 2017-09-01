
#pragma once

namespace vngine {
namespace character {

class Char3DModel : ICharacterModel {
public:
	void load();
	void draw();
	void setActiveAnimation();
};

}
}
