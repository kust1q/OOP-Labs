#include "triangle.h"
#include "exceptions.h"

namespace figure {
    Triangle::Triangle(){
        points[0] = new Point(0, 0);
        points[1] = new Point(2, 0);
        points[2] = new Point(1, std::sqrt(3));
    }

    Triangle::Triangle(Point p1, Point p2, Point p3){
        points[0] = new Point(p1.x, p1.y);
        points[1] = new Point(p2.x, p2.y);
        points[2] = new Point(p3.x, p3.y);
        if (!Validate(p1, p2, p3)) {
            Clear();
            throw exceptions::InvalidPointsException("Invalid points to create triangle");
        }
    }

    Triangle::Triangle(const Triangle& other) {
        for (size_t i = 0; i < TRIANGLEANGLES; ++i) {
            points[i] = new Point(other.points[i]->x, other.points[i]->y);
        }
    }

    bool Triangle::Validate(Point p1, Point p2, Point p3) const {
        Point points_arr[4] = {p1, p2, p3};
        for (int i = 0; i < TRIANGLEANGLES; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (points_arr[i] == points_arr[j]) {
                    return false;
                }
            }
        }

        double area = 0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
        if (area < std::numeric_limits<double>::epsilon()) {
            return false;
        }
        double s1 = DistanceBetweenPoints(p1, p2);
        double s2 = DistanceBetweenPoints(p2, p3);
        double s3 = DistanceBetweenPoints(p1, p3); 

        bool b1 = std::abs(s1 - s2) < EPS;
        bool b2 = std::abs(s2 - s3) < EPS;
        bool b3 = std::abs(s1 - s3) < EPS;
        return b1 && b2 && b3;
    }

    Triangle& Triangle::operator=(const Triangle& other) {
        if (&other == this) {
            return *this;
        }
        for (size_t i = 0; i < TRIANGLEANGLES; ++i) {
            if (points[i] == nullptr) {
                points[i] = new Point(other.points[i]->x, other.points[i]->y);
            } else {
                *points[i] = *other.points[i];
            }
        }
        return *this;
    }

    Point Triangle::Center() const {
        Point center((points[0]->x + points[1]->x + points[2]->x) / 3.0, (points[0]->y + points[1]->y + points[2]->y) / 3.0);
        return center;
    }

    double Triangle::Area() const {
        double area = 0.5 * ((points[1]->x - points[0]->x) * (points[2]->y - points[0]->y) - (points[2]->x - points[0]->x) * (points[1]->y - points[0]->y));
        return area;
    }

    Triangle::operator double() const {
        return Area();
    }

    void Triangle::Clear() {
        for (size_t i = 0; i < TRIANGLEANGLES; ++i) {
            delete points[i];
            points[i] = nullptr;
        }
    }

    Triangle::~Triangle() {
        Clear();
    }

    bool operator==(const Triangle& lf, const Triangle& rf) {
        double s1 = DistanceBetweenPoints(*lf.points[0], *lf.points[1]);
        double s2 = DistanceBetweenPoints(*rf.points[0], *rf.points[1]);
        return s1 == s2;
    }

    bool operator!=(const Triangle& lf, const Triangle& rf) {
        return !(lf == rf);
    }

    std::ostream& operator<<(std::ostream& os, const Triangle& t) {
        for (size_t i = 0; i < TRIANGLEANGLES; ++i) {
            os << *t.points[i];
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Triangle& t) {
        Point p1, p2, p3;
        is >> p1;
        is >> p2;
        is >> p3;
        Triangle temp(p1, p2, p3);
        std::swap(t.points, temp.points);
        return is;
    }
}

