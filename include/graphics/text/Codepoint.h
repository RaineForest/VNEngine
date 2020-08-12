#pragma once

#include <string>
#include <vector>

namespace vngine {
namespace graphics {
namespace text {

/**
 * Class for representing a Unicode codepoint.
 * This is helpful for identifying multibyte glyphs to font renderers.
 */
class Codepoint {
public:
        /**
         * Constructor
         * @param c a unicode codepoint
         */
        Codepoint(char32_t c);
        virtual ~Codepoint() = default;

        /**
         * make - factory method for converting UTF-8 strings into Codepoints
         * @param s a UTF-8 string
         * @return a vector of codepoints
         */
        static std::vector<Codepoint> make(const std::string& s);

        /**
         * get - gets the value of this codepoint
         * @return the unicode codepoint
         */
        char32_t get() const;

private:
        char32_t codepoint;
};

} // namespace text
} // namespace graphics
} // namespace vngine