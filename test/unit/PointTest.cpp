
#include "graphics/geometry/Point.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(PointTest, Initialization)
{
        Point<int, 3> p({1, 2, 3});
        ASSERT_TRUE(p.size() == 3);

        int* d = (int*)p; //testing casting too
        ASSERT_TRUE(d[0] == 1);
        ASSERT_TRUE(d[1] == 2);
        ASSERT_TRUE(d[2] == 3);
}

TEST(PointTest, Access)
{
        Point<int, 4> p({4, 5, 6, 7});
        ASSERT_TRUE(p[0] == 4);
        ASSERT_TRUE(p[1] == 5);
        ASSERT_TRUE(p[2] == 6);
        ASSERT_TRUE(p[3] == 7);

        p[0] = 8;
        ASSERT_TRUE(p[0] == 8);

        ASSERT_TRUE(p.x() == 8);
        ASSERT_TRUE(p.y() == 5);
        ASSERT_TRUE(p.z() == 6);
        ASSERT_TRUE(p.w() == 7);

        ASSERT_TRUE(p.r() == 8);
        ASSERT_TRUE(p.g() == 5);
        ASSERT_TRUE(p.b() == 6);
        ASSERT_TRUE(p.a() == 7);
}

TEST(PointTest, Equality)
{
        Point<int, 2> p({0, 1});
        Point<int, 2> q({1, 2});
        Point<int, 2> r({0, 1});

        ASSERT_TRUE(p == r);
        ASSERT_TRUE(p != q);
}

TEST(PointTest, ElementMath)
{
        Point<int, 2> p({0, 1});
        Point<int, 2> q({2, 3});
        Point<int, 2> result;

        Point<int, 2> expectAdd({2, 4});
        Point<int, 2> expectSub({-2, -2});
        Point<int, 2> expectMul({0, 3});
        Point<int, 2> expectDiv({0, 0});
        
        result = p + q;
        ASSERT_TRUE(result == expectAdd);
        result = p - q;
        ASSERT_TRUE(result == expectSub);
        result = p * q;
        ASSERT_TRUE(result == expectMul);
        result = p / q;
        ASSERT_TRUE(result == expectDiv);
}

TEST(PointTest, ScalarMath)
{
        Point<int, 2> p({0,4});
        int q = 4;
        Point<int, 2> result;

        Point<int, 2> expectMul({0, 16});
        Point<int, 2> expectDiv({0, 1});

        result = p * q;
        ASSERT_TRUE(result == expectMul);
        result = p / q;
        ASSERT_TRUE(result == expectDiv);
}

TEST(PointTest, DotProd)
{
        Point<int, 3> p({1,2,3});
        Point<int, 3> q({0,4,-1});
        int result = 0;
        int expect = 5;

        result = dot(p,q);
        ASSERT_TRUE(result == expect);
}
