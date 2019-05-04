
#include "graphics/glwrapping/GLHelper.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace vngine::graphics::glwrapping;
using namespace gl;

TEST(GLHelperTest, TypeId)
{
        ASSERT_EQ(glTypeToIdent<float>(0),        "f");
        ASSERT_EQ(glTypeToIdent<double>(0),       "d");
        ASSERT_EQ(glTypeToIdent<int>(0),          "i");
        ASSERT_EQ(glTypeToIdent<short>(0),        "s");
        ASSERT_EQ(glTypeToIdent<unsigned int>(0), "ui");
}

TEST(GLHelperTest, TypeEnum)
{
        ASSERT_EQ(glTypeToEnum<float>(0),          GL_FLOAT);
        ASSERT_EQ(glTypeToEnum<double>(0),         GL_DOUBLE);
        ASSERT_EQ(glTypeToEnum<int>(0),            GL_INT);
        ASSERT_EQ(glTypeToEnum<unsigned int>(0),   GL_UNSIGNED_INT);
        ASSERT_EQ(glTypeToEnum<short>(0),          GL_SHORT);
        ASSERT_EQ(glTypeToEnum<unsigned short>(0), GL_UNSIGNED_SHORT);
        ASSERT_EQ(glTypeToEnum<char>(0),           GL_BYTE);
        ASSERT_EQ(glTypeToEnum<unsigned char>(0),  GL_UNSIGNED_BYTE);
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
