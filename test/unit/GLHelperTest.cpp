
#include "graphics/GLHelper.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace vngine::graphics;

TEST(GLHelperTest, TypeId)
{
        float f = 0.0f;
        double d = 0.0;
        int i = 0;
        short s = 0;
        unsigned int ui = 0;

        ASSERT_EQ(glTypeToIdent(f),  "f");
        ASSERT_EQ(glTypeToIdent(d),  "d");
        ASSERT_EQ(glTypeToIdent(i),  "i");
        ASSERT_EQ(glTypeToIdent(s),  "s");
        ASSERT_EQ(glTypeToIdent(ui), "ui");
}

TEST(GLHelperTest, HelperCall)
{
        ASSERT_NO_THROW({glHelperCall(std::string("glVertex3f"), 0.0f, 0.0f, 0.0f);});
}

TEST(GLHelperTest, Helper)
{
        float f = 0;
        ASSERT_NO_THROW({glHelper(std::string("glVertex"), f, 3, 0.0f, 0.0f, 0.0f);});
}

TEST(GLHelperTest, Nonexist)
{
        ASSERT_THROW({glHelperCall(std::string("glVertex3asdf"), 0.0f, 0.0f, 0.0f);}, std::runtime_error);
}
