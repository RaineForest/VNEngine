
#pragma once

#include "include/dialogue/Action.h"
#include <vector>

namespace vngine {
namespace dialogue {

class Response {
public:
	Response();
	~Response();

	virtual std::vector<Action> getActions() = 0;

	virtual std::string getType() = 0;
	
private:

};

}
}