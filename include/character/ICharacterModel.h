
#pragma once

namespace vngine {
namespace character {

class ICharacterModel {
public:
	virtual void load() = 0;
	virtual void draw() = 0;
	virtual void setActiveAnimation() = 0;
};

}
}
