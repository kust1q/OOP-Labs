#include "rectangle.h"
#include "exceptions.h"

namespace figure {
    Rectangle::Rectangle() {
        points[0] = new Point(0, 0);
        points[1] = new Point(0, 1);
        points[2] = new Point(1, 1);
        points[3] = new Point(1, 0);
    }

    Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4){
        points[0] = new Point(p1.x, p1.y);
        points[1] = new Point(p2.x, p2.y);
        points[2] = new Point(p3.x, p3.y);
        points[3] = new Point(p4.x, p4.y);
        if (!Validate(p1, p2, p3, p4)) {
            Clear();
            throw exceptions::InvalidPointsException("Invalid points to create a rectangle");
        }
    }

    Rectangle::Rectangle(const Rectangle& other) {
        for (size_t i = 0; i < 4; ++i) {
            points[i] = new Point(other.points[i]->x, other.points[i]->y);
        }
    }

    bool Rectangle::Validate(Point p1, Point p2, Point p3, Point p4) const {
        Point points_arr[4] = {p1, p2, p3, p4};
        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                if (points_arr[i] == points_arr[j]) {
                    return false;
                }
            }
        }
        Point m1 = Point((p1.x + p3.x) / 2.0, (p1.y + p3.y) / 2.0);
        Point m2 = Point((p2.x + p4.x) / 2.0, (p2.y + p4.y) / 2.0);

        if (m1 != m2) {
            return false;
        }

        double l1 = (p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y);
        double l2 = (p2.x - p4.x) * (p2.x - p4.x) + (p2.y - p4.y) * (p2.y - p4.y);
        return l1 == l2;
    }

    Rectangle& Rectangle::operator=(const Rectangle& other) {
        if (&other == this) {
            return *this;
        }
        for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
            if (points[i] == nullptr) {
                points[i] = new Point(other.points[i]->x, other.points[i]->y);
            } else {
                *points[i] = *other.points[i];
            }
        }
        return *this;
    }

    Point Rectangle::Center() const {
        Point p1((points[0]->x + points[2]->x) / 2.0, (points[0]->y + points[2]->y) / 2.0);
        return p1;
    }

    double Rectangle::Area() const {
        double area = (std::fabs(points[0]->x - points[2]->x) * std::fabs(points[0]->y - points[2]->y));
        return area;
    }

    Rectangle::operator double() const {
        return Area();
    }

    void Rectangle::Clear() {
        for (size_t i = 0; i < 4; ++i) {
            delete points[i];
            points[i] = nullptr;
        }
    }

    Rectangle::~Rectangle() {
        Clear();
    }

    bool operator==(const Rectangle& lf, const Rectangle& rf) {
        bool l = std::fabs(lf.points[0]->x - lf.points[3]->x) == std::fabs(rf.points[0]->x - rf.points[3]->x);
        bool w = std::fabs(std::fabs(lf.points[0]->y - lf.points[3]->y)) == std::fabs(std::fabs(rf.points[0]->y - rf.points[3]->y));
        bool res = w & l; 
        return res;
    }

    bool operator!=(const Rectangle& lf, const Rectangle& rf) {
        return !(lf == rf);
    }

    std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
        Point p;
        for (size_t i = 0; i < 4; ++i) {
           os << *r.points[i];
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Rectangle& r) {
        Point p1, p2, p3, p4;
        is >> p1;
        is >> p2;
        is >> p3;
        is >> p4;
        Rectangle temp(p1, p2, p3, p4);
        std::swap(r.points, temp.points);
        return is;
    }
}

