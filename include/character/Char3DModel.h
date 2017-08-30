
#ifndef _CHAR3DMODEL_H_
#define _CHAR3DMODEL_H_

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

#endif
