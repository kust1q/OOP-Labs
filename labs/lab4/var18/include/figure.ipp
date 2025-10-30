#pragma once

#include "figure.hpp"

namespace figure {
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
}