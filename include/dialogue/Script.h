
#pragma once

#include "Action.h"
#include "Response.h"
#include <string>

namespace vngine {
namespace dialogue {

class Script {
public:
	Script(std::string filename);
	~Script();

	Response& getNextResponse();
	void giveAction(Action& a);

private:
	
};

}
}
