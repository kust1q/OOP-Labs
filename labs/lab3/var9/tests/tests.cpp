#include <gtest/gtest.h>
#include "rectangle.h"
#include "square.h"
#include "triangle.h"
#include "vector.h"
#include "exceptions.h"

using namespace figure;
using namespace vector;

TEST(RectangleTest, ConstructorValidPoints) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    EXPECT_NO_THROW(Rectangle r(p1, p2, p3, p4));
}

TEST(RectangleTest, ConstructorInvalidPoints) {
    Point p1(0, 0), p2(0, 0), p3(2, 2), p4(0, 2);
    EXPECT_THROW(Rectangle r(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(RectangleTest, Center) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r(p1, p2, p3, p4);
    Point center = r.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, Area) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(r.Area(), 8.0);
}

TEST(RectangleTest, DoubleCast) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 8.0);
}

TEST(RectangleTest, Equality) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2(p1, p2, p3, p4);
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 != r2);

    Point p5(0, 0), p6(3, 0), p7(3, 3), p8(0, 3);
    Rectangle r3(p5, p6, p7, p8);
    EXPECT_FALSE(r1 == r3);
}

TEST(RectangleTest, CopyConstructor) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

TEST(RectangleTest, AssignmentOperator) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle r1(p1, p2, p3, p4);
    Rectangle r2;
    r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}


TEST(SquareTest, ConstructorValidPoints) {
    Point p1(0, 0), p2(0, 2), p3(2, 2), p4(2, 0);
    EXPECT_NO_THROW(Square s(p1, p2, p3, p4));
}

TEST(SquareTest, ConstructorInvalidPoints) {
    Point p1(0, 0), p2(3, 0), p3(3, 3), p4(0, 2);
    EXPECT_THROW(Square s(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(SquareTest, Center) {
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Square s(p1, p2, p3, p4);
    Point center = s.Center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(SquareTest, Area) {
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Square s(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(s.Area(), 4.0);
}

TEST(TriangleTest, ConstructorValidPoints) {
    Point p1(0, 0), p2(2, 0), p3(1, std::sqrt(3));
    EXPECT_NO_THROW(Triangle t(p1, p2, p3));
}

TEST(TriangleTest, ConstructorInvalidPoints) {
    Point p1(0, 0), p2(0, 0), p3(1, 2);
    EXPECT_THROW(Triangle t(p1, p2, p3), exceptions::InvalidPointsException);

    Point p4(0, 0), p5(1, 0), p6(2, 0);
    EXPECT_THROW(Triangle t(p4, p5, p6), exceptions::InvalidPointsException);

    Point p7(0, 0), p8(2, 0), p9(1, 2);
    EXPECT_THROW(Triangle t(p7, p8, p9), exceptions::InvalidPointsException);
}

TEST(TriangleTest, Center) {
    Point p1(0, 0), p2(2, 0), p3(1, std::sqrt(3));
    Triangle t(p1, p2, p3);
    Point center = t.Center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, std::sqrt(3) / 3);
}

TEST(TriangleTest, Area) {
    Point p1(0, 0), p2(2, 0), p3(1, std::sqrt(3));
    Triangle t(p1, p2, p3);
    EXPECT_DOUBLE_EQ(t.Area(), sqrt(3));
}

TEST(VectorTest, DefaultConstructor) {
    Vector v;
    EXPECT_TRUE(v.IsEmpty());
    EXPECT_EQ(v.Size(), 0);
    EXPECT_EQ(v.Capacity(), 0);
}

TEST(VectorTest, InitializerList) {
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Rectangle* r = new Rectangle(p1, p2, p3, p4);
    Vector v = {r};
    EXPECT_EQ(v.Size(), 1);
    delete r;
}

TEST(VectorTest, PushBack) {
    Vector v;
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Rectangle* r = new Rectangle(p1, p2, p3, p4);
    v.PushBack(r);
    EXPECT_EQ(v.Size(), 1);
    delete r;
}

TEST(VectorTest, Insert) {
    Vector v;
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Rectangle* r1 = new Rectangle(p1, p2, p3, p4);
    Rectangle* r2 = new Rectangle(p1, p2, p3, p4);
    v.PushBack(r1);
    v.Insert(0, r2);
    EXPECT_EQ(v.Size(), 2);
    delete r1;
    delete r2;
}

TEST(VectorTest, Erase) {
    Vector v;
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Rectangle* r1 = new Rectangle(p1, p2, p3, p4);
    Rectangle* r2 = new Rectangle(p1, p2, p3, p4);
    v.PushBack(r1);
    v.PushBack(r2);
    v.Erase(0, 1);
    EXPECT_EQ(v.Size(), 1);
    delete r1;
    delete r2;
}

TEST(VectorTest, PopBack) {
    Vector v;
    Point p1(0, 0), p2(2, 0), p3(2, 2), p4(0, 2);
    Rectangle* r = new Rectangle(p1, p2, p3, p4);
    v.PushBack(r);
    v.PopBack();
    EXPECT_EQ(v.Size(), 0);
    delete r;
}

TEST(VectorTest, CommonArea) {
    Vector v;
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Point p5(0, 0), p6(2, 0), p7(2, 2), p8(0, 2);
    Rectangle* r1 = new Rectangle(p1, p2, p3, p4);
    Rectangle* r2 = new Rectangle(p5, p6, p7, p8);
    v.PushBack(r1);
    v.PushBack(r2);
    EXPECT_DOUBLE_EQ(v.CommonArea(), 12.0);
    delete r1;
    delete r2;
}

TEST(VectorTest, SeparateCenter) {
    Vector v;
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle* r = new Rectangle(p1, p2, p3, p4);
    v.PushBack(r);

    Point p5(0, 0), p6(2, 0), p7(1, std::sqrt(3));
    Triangle* t = new Triangle(p5, p6, p7);
    v.PushBack(t);

    Point p8(0, 0), p9(2, 0), p10(2, 2), p11(0, 2);
    Square* s = new Square(p8, p9, p10, p11);
    v.PushBack(s);

    v.SeparateCenter();
    delete r;
    delete t;
    delete s;
}

TEST(VectorTest, SeparateArea) {
    Vector v;

    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle* r = new Rectangle(p1, p2, p3, p4);
    v.PushBack(r);

    Point p5(0, 0), p6(2, 0), p7(1, std::sqrt(3));
    Triangle* t = new Triangle(p5, p6, p7);
    v.PushBack(t);

    Point p8(0, 0), p9(2, 0), p10(2, 2), p11(0, 2);
    Square* s = new Square(p8, p9, p10, p11);
    v.PushBack(s);

    v.SeparateArea();
    delete r;
    delete t;
    delete s;
}

TEST(PolymorphismTest, VirtualMethods) {
    Point p1(0, 0), p2(0, 2), p3(4, 2), p4(4, 0);
    Rectangle* r = new Rectangle(p1, p2, p3, p4);

    Point p5(0, 0), p6(2, 0), p7(1, std::sqrt(3));
    Triangle* t = new Triangle(p5, p6, p7);

    Point p8(0, 0), p9(2, 0), p10(2, 2), p11(0, 2);
    Square* s = new Square(p8, p9, p10, p11);

    Figure* f1 = r;
    EXPECT_DOUBLE_EQ(f1->Area(), 8.0);
    Point center1 = f1->Center();
    EXPECT_DOUBLE_EQ(center1.x, 2.0);
    EXPECT_DOUBLE_EQ(center1.y, 1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f1), 8.0);

    Figure* f2 = s;
    EXPECT_DOUBLE_EQ(f2->Area(), 4.0);
    Point center2 = f2->Center();
    EXPECT_DOUBLE_EQ(center2.x, 1.0);
    EXPECT_DOUBLE_EQ(center2.y, 1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f2), 4.0);

    Figure* f3 = t;
    EXPECT_DOUBLE_EQ(f3->Area(), std::sqrt(3));
    Point center3 = f3->Center();
    EXPECT_DOUBLE_EQ(center3.x, 1.0);
    EXPECT_DOUBLE_EQ(center3.y, std::sqrt(3) / 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f3), std::sqrt(3));
    delete r;
    delete s;
    delete t;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}