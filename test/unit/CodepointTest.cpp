
#include "graphics/text/Codepoint.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(CodepointTest, HappyPath) {
        // string with one byte, three byte, two byte, and diacritics (lol thanks cursed text generator)
        std::string test = u8"a€¢á̷͇̫͕̬̫̭͓͜";
        std::vector<char32_t> expected = {
                0x61,
                0x20ac,
                0x00a2,
                0x61,
                0x0337,
                0x0341,
                0x0347,
                0x032b,
                0x0355,
                0x032c,
                0x032b,
                0x035c,
                0x032d,
                0x0353
        };
        auto points = vngine::graphics::text::Codepoint::make(test);
        EXPECT_EQ(points.size(), expected.size());

        for (size_t i = 0; i < expected.size(); i++) {
                EXPECT_EQ(points.at(i).get(), expected.at(i));
        }
}
