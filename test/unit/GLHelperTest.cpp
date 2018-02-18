
#include "graphics/glwrapping/GLHelper.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace vngine::graphics::glwrapping;

TEST(GLHelperTest, TypeId)
{
        ASSERT_EQ(glTypeToIdent<float>(),        "f");
        ASSERT_EQ(glTypeToIdent<double>(),       "d");
        ASSERT_EQ(glTypeToIdent<int>(),          "i");
        ASSERT_EQ(glTypeToIdent<short>(),        "s");
        ASSERT_EQ(glTypeToIdent<unsigned int>(), "ui");
}

TEST(GLHelperTest, TypeEnum)
{
        ASSERT_EQ(glTypeToEnum<float>(),          GL_FLOAT);
        ASSERT_EQ(glTypeToEnum<double>(),         GL_DOUBLE);
        ASSERT_EQ(glTypeToEnum<int>(),            GL_INT);
        ASSERT_EQ(glTypeToEnum<unsigned int>(),   GL_UNSIGNED_INT);
        ASSERT_EQ(glTypeToEnum<short>(),          GL_SHORT);
        ASSERT_EQ(glTypeToEnum<unsigned short>(), GL_UNSIGNED_SHORT);
        ASSERT_EQ(glTypeToEnum<char>(),           GL_BYTE);
        ASSERT_EQ(glTypeToEnum<unsigned char>(),  GL_UNSIGNED_BYTE);
}

TEST(GLHelperTest, HelperCall)
{
        ASSERT_NO_THROW({glHelperCall(std::string("glVertex3f"), 0.0f, 0.0f, 0.0f);});
}

TEST(GLHelperTest, Helper)
{
        ASSERT_NO_THROW({glHelper<float>(std::string("glVertex"), 3, 0.0f, 0.0f, 0.0f);});
}

TEST(GLHelperTest, Nonexist)
{
        ASSERT_THROW({glHelperCall(std::string("glVertex3asdf"), 0.0f, 0.0f, 0.0f);}, std::runtime_error);
}
