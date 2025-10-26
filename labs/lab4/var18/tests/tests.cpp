#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"
#include "vector.hpp"
#include "exceptions.hpp"

using namespace figure;

// --- Тесты для Rectangle<double> ---
TEST(RectangleTest, ConstructorValidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    EXPECT_NO_THROW(Rectangle<double> r(p1, p2, p3, p4));
}

TEST(RectangleTest, ConstructorInvalidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 0.0), p3(2.0, 2.0), p4(0.0, 2.0);
    EXPECT_THROW(Rectangle<double> r(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(RectangleTest, DefaultConstructor) {
    Rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.Area(), 1.0);
}

TEST(RectangleTest, Center) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r(p1, p2, p3, p4);
    Point<double> center = r.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(RectangleTest, Area) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(r.Area(), 8.0);
}

TEST(RectangleTest, DoubleCast) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 8.0);
}

TEST(RectangleTest, Equality) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2(p1, p2, p3, p4);
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 != r2);

    Point<double> p5(0.0, 0.0), p6(0.0, 3.0), p7(3.0, 3.0), p8(3.0, 0.0);
    Rectangle<double> r3(p5, p6, p7, p8);
    EXPECT_FALSE(r1 == r3);
}

TEST(RectangleTest, CopyConstructor) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

TEST(RectangleTest, AssignmentOperator) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2;
    r2 = r1;
    EXPECT_DOUBLE_EQ(r2.Area(), 8.0);
    EXPECT_TRUE(r1 == r2);
}

TEST(RectangleTest, MoveConstructor) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    double area = r1.Area();
    Rectangle<double> r2 = std::move(r1);

    EXPECT_DOUBLE_EQ(r2.Area(), area);
    EXPECT_DOUBLE_EQ(r2.Center().x, 2.0);
    EXPECT_DOUBLE_EQ(r2.Center().y, 1.0);

    EXPECT_DOUBLE_EQ(r1.Area(), 1.0);
}

TEST(RectangleTest, MoveAssignment) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    Point<double> p5(1.0, 1.0), p6(1.0, 4.0), p7(4.0, 4.0), p8(4.0, 1.0);
    Rectangle<double> r1(p1, p2, p3, p4);
    Rectangle<double> r2(p5, p6, p7, p8);
    double area = r1.Area();
    r2 = std::move(r1);

    EXPECT_DOUBLE_EQ(r2.Area(), area);
    EXPECT_DOUBLE_EQ(r1.Area(), 1.0);
}

// --- Тесты для Square<double> ---
TEST(SquareTest, ConstructorValidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    EXPECT_NO_THROW(Square<double> s(p1, p2, p3, p4));
}

TEST(SquareTest, ConstructorInvalidPoints) {
    Point<double> p1(0.0, 0.0), p2(3.0, 0.0), p3(3.0, 3.0), p4(0.0, 2.0);
    EXPECT_THROW(Square<double> s(p1, p2, p3, p4), exceptions::InvalidPointsException);
}

TEST(SquareTest, Center) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    Square<double> s(p1, p2, p3, p4);
    Point<double> center = s.Center();
    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(SquareTest, Area) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    Square<double> s(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(s.Area(), 4.0);
}

TEST(SquareTest, MoveConstructor) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    Square<double> s1(p1, p2, p3, p4);
    double area = s1.Area();
    Point<double> center = s1.Center();

    Square<double> s2 = std::move(s1);

    EXPECT_DOUBLE_EQ(s2.Area(), area);
    EXPECT_DOUBLE_EQ(s2.Center().x, center.x);
    EXPECT_DOUBLE_EQ(s2.Center().y, center.y);
    EXPECT_DOUBLE_EQ(s1.Area(), 1.0);
}

TEST(SquareTest, MoveAssignment) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    Point<double> p5(1.0, 1.0), p6(1.0, 3.0), p7(3.0, 3.0), p8(3.0, 1.0);
    Square<double> s1(p1, p2, p3, p4);
    Square<double> s2(p5, p6, p7, p8);
    double area = s1.Area();

    s2 = std::move(s1);

    EXPECT_DOUBLE_EQ(s2.Area(), area);
    EXPECT_DOUBLE_EQ(s1.Area(), 1.0);
}

// --- Тесты для Trapezoid<double> ---
TEST(TrapezoidTest, ConstructorValidPoints) {
    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    EXPECT_NO_THROW(Trapezoid<double> t(p1, p2, p3, p4));
}

TEST(TrapezoidTest, ConstructorInvalidPoints) {
    Point<double> p1(0.0, 0.0), p2(0.0, 0.0), p3(0.0, 0.0), p4(0.0, 0.0);
    EXPECT_THROW(Trapezoid<double> t(p1, p2, p3, p4), exceptions::InvalidPointsException);

    Point<double> p5(0.0, 0.0), p6(2.0, 0.0), p7(3.0, 2.0), p8(0.0, 2.0);
    EXPECT_THROW(Trapezoid<double> t(p5, p6, p7, p8), exceptions::InvalidPointsException);

    Point<double> p9(0.0, 0.0), p10(0.0, 4.0), p11(3.0, 2.0), p12(2.0, 0.0); // боковые стороны разной длины
    EXPECT_THROW(Trapezoid<double> t(p9, p10, p11, p12), exceptions::InvalidPointsException);
}

TEST(TrapezoidTest, Center) {
    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    Trapezoid<double> t(p1, p2, p3, p4);
    Point<double> center = t.Center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(TrapezoidTest, Area) {
    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    Trapezoid<double> t(p1, p2, p3, p4);
    EXPECT_DOUBLE_EQ(t.Area(), 6.0);
}

TEST(TrapezoidTest, MoveConstructor) {
    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    Trapezoid<double> t1(p1, p2, p3, p4);
    double area = t1.Area();
    Point<double> center = t1.Center();
    Trapezoid<double> t2 = std::move(t1);

    EXPECT_DOUBLE_EQ(t2.Area(), area);
    EXPECT_DOUBLE_EQ(t2.Center().x, center.x);
    EXPECT_DOUBLE_EQ(t2.Center().y, center.y);

    EXPECT_DOUBLE_EQ(t1.Area(), 1.0);
}

TEST(TrapezoidTest, MoveAssignment) {
    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    Point<double> p5(1.0, 1.0), p6(2.0, 3.0), p7(4.0, 3.0), p8(5.0, 1.0);
    Trapezoid<double> t1(p1, p2, p3, p4);
    Trapezoid<double> t2(p5, p6, p7, p8);
    double area = t1.Area();

    t2 = std::move(t1);

    EXPECT_DOUBLE_EQ(t2.Area(), area);
    EXPECT_DOUBLE_EQ(t1.Area(), 1.0);
}

TEST(TrapezoidTest, Equality) {
    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    Trapezoid<double> t1(p1, p2, p3, p4);
    Trapezoid<double> t2(p1, p2, p3, p4);
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 != t2);

    Point<double> p5(1.0, 1.0), p6(3.0, 4.0), p7(4.0, 4.0), p8(6.0, 1.0);
    Trapezoid<double> t3(p5, p6, p7, p8);
    EXPECT_FALSE(t1 == t3);
}

// --- Тесты для Vector<Figure<T>*> с разными типами фигур ---

// Тест для Vector<Figure<double>*>
TEST(VectorTest, FigureDoubleVector) {
    using FigPtr = std::shared_ptr<Figure<double>>;
    Vector<FigPtr> v;

    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    auto rect = std::make_shared<Rectangle<double>>(p1, p2, p3, p4);
    v.PushBack(rect);

    Point<double> p5(0.0, 0.0), p6(2.0, 0.0), p7(2.0, 2.0), p8(0.0, 2.0);
    auto sq = std::make_shared<Square<double>>(p5, p6, p7, p8);
    v.PushBack(sq);

    Point<double> p9(0.0, 0.0), p10(1.0, 2.0), p11(3.0, 2.0), p12(4.0, 0.0);
    auto trap = std::make_shared<Trapezoid<double>>(p9, p10, p11, p12);
    v.PushBack(trap);

    EXPECT_EQ(v.Size(), 3);

    EXPECT_DOUBLE_EQ(v.CommonArea<double>(), 8.0 + 4.0 + 6.0); // 18.0

    for (size_t i = 0; i < v.Size(); ++i) {
        auto fig = v[i];
        EXPECT_DOUBLE_EQ(fig->Area(), static_cast<double>(*fig));
    }

    v.Erase(0, 1); // удаляем квадрат
    EXPECT_EQ(v.Size(), 2);
}

// Тест для Vector<Rectangle<double>*>
TEST(VectorTest, RectangleDoubleVector) {
    using RectPtr = std::shared_ptr<Rectangle<double>>;
    Vector<RectPtr> v;

    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    auto r1 = std::make_shared<Rectangle<double>>(p1, p2, p3, p4);
    v.PushBack(r1);

    Point<double> p5(1.0, 1.0), p6(1.0, 3.0), p7(5.0, 3.0), p8(5.0, 1.0);
    auto r2 = std::make_shared<Rectangle<double>>(p5, p6, p7, p8);
    v.PushBack(r2);

    EXPECT_EQ(v.Size(), 2);
    EXPECT_DOUBLE_EQ(v[0]->Area(), 8.0);
    EXPECT_DOUBLE_EQ(v[1]->Area(), 8.0);

    EXPECT_DOUBLE_EQ(v.CommonArea<double>(), 16.0);

    v.PopBack();
    EXPECT_EQ(v.Size(), 1);
}

// Тест для Vector<Square<double>*>
TEST(VectorTest, SquareDoubleVector) {
    using SqPtr = std::shared_ptr<Square<double>>;
    Vector<SqPtr> v;

    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(2.0, 2.0), p4(2.0, 0.0);
    auto s1 = std::make_shared<Square<double>>(p1, p2, p3, p4);
    v.PushBack(s1);

    Point<double> p5(1.0, 1.0), p6(1.0, 3.0), p7(3.0, 3.0), p8(3.0, 1.0);
    auto s2 = std::make_shared<Square<double>>(p5, p6, p7, p8);
    v.PushBack(s2);

    EXPECT_EQ(v.Size(), 2);
    EXPECT_DOUBLE_EQ(v[0]->Area(), 4.0);
    EXPECT_DOUBLE_EQ(v[1]->Area(), 4.0);

    EXPECT_DOUBLE_EQ(v.CommonArea<double>(), 8.0);
}

// Тест для Vector<Trapezoid<double>*>
TEST(VectorTest, TrapezoidDoubleVector) {
    using TrapPtr = std::shared_ptr<Trapezoid<double>>;
    Vector<TrapPtr> v;

    Point<double> p1(0.0, 0.0), p2(1.0, 2.0), p3(3.0, 2.0), p4(4.0, 0.0);
    auto t1 = std::make_shared<Trapezoid<double>>(p1, p2, p3, p4);
    v.PushBack(t1);

    Point<double> p5(1.0, 1.0), p6(2.0, 3.0), p7(4.0, 3.0), p8(5.0, 1.0);
    auto t2 = std::make_shared<Trapezoid<double>>(p5, p6, p7, p8);
    v.PushBack(t2);

    EXPECT_EQ(v.Size(), 2);
    EXPECT_DOUBLE_EQ(v[0]->Area(), 6.0);
    EXPECT_DOUBLE_EQ(v[1]->Area(), 6.0);

    EXPECT_DOUBLE_EQ(v.CommonArea<double>(), 12.0);
}

// --- Полиморфизм с shared_ptr ---
TEST(PolymorphismTest, VirtualMethodsWithSharedPtr) {
    Point<double> p1(0.0, 0.0), p2(0.0, 2.0), p3(4.0, 2.0), p4(4.0, 0.0);
    auto r = std::make_shared<Rectangle<double>>(p1, p2, p3, p4);

    Point<double> p5(0.0, 0.0), p6(0.0, 2.0), p7(2.0, 2.0), p8(2.0, 0.0);
    auto s = std::make_shared<Square<double>>(p5, p6, p7, p8);

    Point<double> p9(0.0, 0.0), p10(1.0, 2.0), p11(3.0, 2.0), p12(4.0, 0.0);
    auto t = std::make_shared<Trapezoid<double>>(p9, p10, p11, p12);

    std::shared_ptr<Figure<double>> f1 = r;
    EXPECT_DOUBLE_EQ(f1->Area(), 8.0);
    Point<double> center1 = f1->Center();
    EXPECT_DOUBLE_EQ(center1.x, 2.0);
    EXPECT_DOUBLE_EQ(center1.y, 1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f1), 8.0);

    std::shared_ptr<Figure<double>> f2 = s;
    EXPECT_DOUBLE_EQ(f2->Area(), 4.0);
    Point<double> center2 = f2->Center();
    EXPECT_DOUBLE_EQ(center2.x, 1.0);
    EXPECT_DOUBLE_EQ(center2.y, 1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f2), 4.0);

    std::shared_ptr<Figure<double>> f3 = t;
    EXPECT_DOUBLE_EQ(f3->Area(), 6.0);
    Point<double> center3 = f3->Center();
    EXPECT_DOUBLE_EQ(center3.x, 2.0);
    EXPECT_DOUBLE_EQ(center3.y, 1.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(*f3), 6.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}