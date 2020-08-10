
#include "Exceptions.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace vngine;

TEST(ExceptionTest, ThrowTest)
{
        std::string expected = std::string("GLException: test");
        std::string err = "";
        try {
                GLException e("test");
                throw e;
        }
        catch (const std::exception& e) {
                err = e.what();
        }
        EXPECT_EQ(err.substr(0, expected.size()), expected);
}
