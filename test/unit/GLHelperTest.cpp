
#include "graphics/GLHelper.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace vngine::graphics;

TEST(GLHelperTest, TypeId)
{
        ASSERT_EQ(glTypeToIdent(float f = 0.0f),        "f");
        ASSERT_EQ(glTypeToIdent(double d = 0.0),        "d");
        ASSERT_EQ(glTypeToIdent(int i = 0),             "i");
        ASSERT_EQ(glTypeToIdent(short s = 0),           "s");
        ASSERT_EQ(glTypeToIdent(unsigned int ui = 0),   "ui");
}

TEST(GLHelperTest, HelperCall)
{
        ASSERT_NO_THROW(glHelperCall("glVertex3f", 0.0f, 0.0f, 0.0f));
}

TEST(GLHelperTest, Helper)
{
        ASSERT_NO_THROW(glHelper<float, 3>("glVertex", 0.0f, 0.0f, 0.0f));
}
