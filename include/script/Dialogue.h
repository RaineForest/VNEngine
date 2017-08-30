
#ifndef _DIALOGUE_H_
#define _DIALOGUE_H_

#include <string>

namespace vngine {
namespace script {

class Dialogue {
public:
	Dialogue();
	Dialogue(std::string speaker, std::string text);
	~Dialogue();

	std::string getSpeaker() const;
	std::string getText() const;

private:
	std::string speaker;
	std::string text;
};

}
}

#endif
