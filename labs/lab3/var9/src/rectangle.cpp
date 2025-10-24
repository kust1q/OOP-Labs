#include "rectangle.h"
#include "exceptions.h"
#include "figure.h"
#include <stdexcept>

namespace figure {
    Rectangle::Rectangle(): Rectangle(Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)) {}

    Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4){
        if (!Validate(p1, p2, p3, p4)) {
            throw exceptions::InvalidPointsException("Rectangle: invalid points!");
        }
        points = new Point[RECTANGLEANGLES]{p1, p2, p3, p4};
    }

    Rectangle::Rectangle(const Rectangle& other) {
        points = new Point[RECTANGLEANGLES];
        for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
            points[i] = Point(other.points[i].x, other.points[i].y);
        }
    }

    bool Rectangle::Validate(Point p1, Point p2, Point p3, Point p4) const {
        Point pointsArr[RECTANGLEANGLES] = {p1, p2, p3, p4};
        for (int i = 0; i < RECTANGLEANGLES; ++i) {
            for (int j = i + 1; j < RECTANGLEANGLES; ++j) {
                if (pointsArr[i] == pointsArr[j]) {
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
           points[i] = other.points[i];
        }
        return *this;
    }

    Point Rectangle::Center() const {
        Point p1((points[0].x + points[2].x) / 2.0, (points[0].y + points[2].y) / 2.0);
        return p1;
    }

    double Rectangle::Area() const {
        double area = (std::fabs(points[0].x - points[2].x) * std::fabs(points[0].y - points[2].y));
        return area;
    }

    Rectangle::operator double() const {
        return Area();
    }

    Rectangle::~Rectangle() {
        delete[] points;
    }

    bool operator==(const Rectangle& lf, const Rectangle& rf) {
        bool l = std::fabs(lf.points[0].x - lf.points[3].x) == std::fabs(rf.points[0].x - rf.points[3].x);
        bool w = std::fabs(std::fabs(lf.points[0].y - lf.points[3].y)) == std::fabs(std::fabs(rf.points[0].y - rf.points[3].y));
        bool res = w & l; 
        return res;
    }

    bool operator!=(const Rectangle& lf, const Rectangle& rf) {
        return !(lf == rf);
    }

    std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
        for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
           os << r.points[i];
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Rectangle& r) {
        Point ipoints[RECTANGLEANGLES];
        for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
            is >> ipoints[i];
        }
        try {
            Rectangle temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
            std::swap(r.points, temp.points);
        } catch (exceptions::InvalidPointsException& e) {
            std::cerr << "Rectangle: invalid points from input stream!" << std::endl;
            return is;
        }
        return is;
    }
}

