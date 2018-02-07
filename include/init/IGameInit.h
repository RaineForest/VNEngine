
#pragma once

#include "graphics/UI/IContainer.h"
#include "graphics/IUpdateable.h"

using namespace vngine::graphics;

namespace vngine {
namespace init {

class IGameInit : public IContainer, public IUpdateable
{
public:
	virtual void start() = 0;
};

} //namespace init
} //namespace vngine
