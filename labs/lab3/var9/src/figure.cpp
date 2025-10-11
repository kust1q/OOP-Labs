#include "figure.h"

namespace figure {

    Point::Point(double x, double y): x(x), y(y) {} 

    double DistanceBetweenPoints(const Point& p1, const Point& p2) {
        return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    bool operator==(const Point& lp, const Point& rp) {
        bool x = std::fabs(lp.x - rp.x) < EPS;
        bool y = std::fabs(lp.y - rp.y) < EPS;
        return (x && y);
    }

    bool operator!=(const Point& lp, const Point& rp) {
        return !(lp == rp);
    }


    std::ostream& operator<<(std::ostream& os, const figure::Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    std::istream& operator>>(std::istream& is, figure::Point& p) {
        is >> p.x >> p.y;
        return is;
    }
}