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
    bool AreParalel(const Point<T>& v1, const Point<T>& v2) {
        bool b = (v1.x * v2.y - v1.y * v2.x) == 0;
        return b;
    }

    template<Scalar T>
    bool operator==(const Point<T>& lp, const Point<T>& rp) {
        bool x = std::fabs(lp.x - rp.x) < EPS;
        bool y = std::fabs(lp.y - rp.y) < EPS;
        return (x && y);
    }

    template<Scalar T>
    bool operator!=(const Point<T>& lp, const Point<T>& rp) {
        return !(lp == rp);
    }

    template<Scalar T>
    double DistanceBetweenPoints(const Point<T>& p1, const Point<T>& p2) {
        double distance = std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
        return distance;
    }


    template<Scalar T>
    std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    template<Scalar T>
    std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x >> p.y;
        return is;
    }

    template<Scalar T>
    class Figure {
      public:
        virtual Point<T> Center() const = 0;
        virtual double Area() const  = 0;
        virtual operator double() const = 0;
        virtual ~Figure() = default;
    };  
}
