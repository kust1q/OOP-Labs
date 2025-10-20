#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <vector>

namespace figure {
    const double EPS = 1e-9;
    const int16_t TRIANGLEANGLES = 3;
    const int16_t SQUAREANGLES = 4;
    const int16_t RECTANGLEANGLES = 4;

    class Point {
      public:
        double x = 0;
        double y = 0;
        Point() = default;
        Point(double x, double y);
    };

    bool operator==(const Point& lp, const Point& rp);
    bool operator!=(const Point& lp, const Point& rp);

    class Figure {
      public:
        virtual Point Center() const = 0;
        virtual double Area() const  = 0;
        virtual operator double() const = 0;
        virtual ~Figure() = default;
    };  

    double DistanceBetweenPoints(const Point& a, const Point& b);

    std::ostream& operator<<(std::ostream& os, const Point& p);
    std::istream& operator>>(std::istream& is, Point& p);
}