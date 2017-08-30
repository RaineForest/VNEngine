
#ifndef _SCRIPT_H_
#define _SCRIPT_H_

namespace vngine {
namespace script {

class Script {
public:
	Script();
	~Script();

	bool hasNext();
	Dialogue& next();
	
private:

};

}
}

#endif
