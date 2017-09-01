
#pragma once

#include "include/dialogue/Action.h"
#include "include/dialogue/Response.h"
#include <string>

namespace vngine {
namespace dialogue {

class Conversation {
public:
	Conversation();
	~Conversation();

	Response& prompt();
	void respond(Action& a);
};

}
}
