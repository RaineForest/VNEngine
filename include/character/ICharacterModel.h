
#ifndef _ICHARACTER_MODEL_H_
#define _ICHARACTER_MODEL_H_

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

#endif
