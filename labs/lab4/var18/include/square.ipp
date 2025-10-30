#pragma once

#include "square.hpp"

namespace figure {
    template<Scalar T>
    bool Square<T>::Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const {
        Point<T> pointsArr[SQUAREANGLES] = {p1, p2, p3, p4};
        for (int i = 0; i < SQUAREANGLES; ++i) {
            for (int j = i + 1; j < SQUAREANGLES; ++j) {
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

        if (l1 != l2) {
            return false;
        }

        double a = DistanceBetweenPoints(p1, p2);
        double b = DistanceBetweenPoints(p2, p3);
        double c = DistanceBetweenPoints(p3, p4);
        double d = DistanceBetweenPoints(p4, p1);
        return a == b && a == c && a == d;
    }

    template<Scalar T>
    Square<T>::Square(): Square(Point<T>(0.0, 0.0), Point<T>(0.0, 1.0), Point<T>(1.0, 1.0), Point<T>(1.0, 0.0)) {}

    template<Scalar T>
    Square<T>::Square(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
        if (!Validate(p1, p2, p3, p4)) {
            throw exceptions::InvalidPointsException("Square: invalid points!");
        }
        points = std::make_unique<Point<T>[]>(SQUAREANGLES);
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
    }

    template<Scalar T>
    Square<T>::Square(const Square& other) {
        if (other.points.get() == nullptr) {
            points = std::unique_ptr<Point<T>[]>(nullptr);
            return;
        }
        points = std::make_unique<Point<T>[]>(SQUAREANGLES);
        for (size_t i = 0; i < SQUAREANGLES; ++i) {
            points[i] = other.points[i];
        }
    }

    template<Scalar T>
    Square<T>& Square<T>::operator=(const Square& other) {
        if (&other != this) {
            Square<T> temp = other;
            std::swap(temp.points, points);
        }
        return *this;
    }

    template<Scalar T>
    Point<T> Square<T>::Center() const {
        if (points.get() == nullptr) {
            return Point<T>(0, 0);
        }
        Point<T> p((points[0].x + points[2].x) / 2.0, (points[0].y + points[2].y) / 2.0);
        return p;
    }

    template<Scalar T>
    double Square<T>::Area() const {
        if (points.get() == nullptr) {
            return 0;
        }
        double area = (std::fabs(points[0].x - points[2].x) * std::fabs(points[0].y - points[2].y));
        return area;
    }

    template<Scalar T>
    Square<T>::operator double() const {
        return Area();
    }

    template <Scalar T>
    bool operator==(const Square<T>& lf, const Square<T>& rf) {
        bool l = std::fabs(lf.points[0].x - lf.points[3].x) == std::fabs(rf.points[0].x - rf.points[3].x);
        bool w = std::fabs(std::fabs(lf.points[0].y - lf.points[3].y)) == std::fabs(std::fabs(rf.points[0].y - rf.points[3].y));
        bool res = w && l;
        return res;
    }

    template <Scalar T>
    bool operator!=(const Square<T>& lf, const Square<T>& rf) {
        return !(lf == rf);
    }

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Square<T>& r) {
        for (size_t i = 0; i < SQUAREANGLES; ++i) {
           os << r.points[i];
        }
        return os;
    }

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Square<T>& r) {
        Point<T> ipoints[SQUAREANGLES];
        for (size_t i = 0; i < SQUAREANGLES; ++i) {
            is >> ipoints[i];
        }
        try {
            Square temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
            std::swap(r.points, temp.points);
        } catch (exceptions::InvalidPointsException&) {
            std::cerr << "Square: invalid points from input stream!" << std::endl;
        }
        return is;
    }
}