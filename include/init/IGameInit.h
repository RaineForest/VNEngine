
#pragma once

#include "graphics/IUpdateable.h"

namespace vngine {
namespace init {

using namespace graphics;

class IGameInit : public IUpdateable
{
public:
	virtual void start() = 0;
};

} //namespace init
} //namespace vngine
