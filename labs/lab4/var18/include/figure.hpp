#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>

#include "concepts.hpp"

namespace figure {
    constexpr const double EPS = 1e-9;
    constexpr const int16_t TRAPEZOIDANGLES = 4;
    constexpr const int16_t SQUAREANGLES = 4;
    constexpr const int16_t RECTANGLEANGLES = 4;

    template<Scalar T>
    class Point {
      public:
        T x;
        T y;
        Point() = default;
        Point(T x, T y) : x(x), y(y) {}
    };

    template<Scalar T>
    class Figure {
      public:
        virtual Point<T> Center() const = 0;
        virtual double Area() const  = 0;
        virtual operator double() const = 0;
        virtual ~Figure() = default;
    };  

    template<Scalar T>
    bool AreParalel(const Point<T>& v1, const Point<T>& v2);

    template<Scalar T>
    bool operator==(const Point<T>& lp, const Point<T>& rp);

    template<Scalar T>
    bool operator!=(const Point<T>& lp, const Point<T>& rp);

    template<Scalar T>
    double DistanceBetweenPoints(const Point<T>& p1, const Point<T>& p2);

    template<Scalar T>
    std::ostream& operator<<(std::ostream& os, const Point<T>& p);

    template<Scalar T>
    std::istream& operator>>(std::istream& is, Point<T>& p);
}

#include "figure.ipp"