#pragma once

#include "figure.hpp"
#include "exceptions.hpp"

namespace figure {
    template<Scalar T>
    class Rectangle: public Figure<T> {
        template<Scalar U>
        friend bool operator==(const Rectangle<U>& lf, const Rectangle<U>& rf);
        template<Scalar U>
        friend bool operator!=(const Rectangle<U>& lf, const Rectangle<U>& rf);
        template<Scalar U>
        friend std::ostream& operator<<(std::ostream& os, const Rectangle<U>& r);
        template<Scalar U>
        friend std::istream& operator>>(std::istream& is, Rectangle<U>& r);
      private:
        std::unique_ptr<Point<T>[]> points;

        bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const {
            Point<T> pointsArr[RECTANGLEANGLES] = {p1, p2, p3, p4};
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

      public:
        Rectangle(): Rectangle(Point<T>(0.0, 0.0), Point<T>(0.0, 1.0), Point<T>(1.0, 1.0), Point<T>(1.0, 0.0)) {}

        Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
            if (!Validate(p1, p2, p3, p4)) {
                throw exceptions::InvalidPointsException("Rectangle: invalid points!");
            }
            points = std::make_unique<Point<T>[]>(RECTANGLEANGLES);
            points[0] = p1;
            points[1] = p2;
            points[2] = p3;
            points[3] = p4;
        }

        Rectangle(const Rectangle& other) {
            if (other.points.get() == nullptr) {
                points = std::unique_ptr<Point<T>[]>(nullptr);
                return;
            }
            points = std::make_unique<Point<T>[]>(RECTANGLEANGLES);
            for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
                points[i] = other.points[i];
            }
        }

        Rectangle(Rectangle&& other) = default;

        Rectangle<T>& operator=(const Rectangle& other) {
            if (&other != this) {
                Rectangle<T> temp = other;
                std::swap(temp.points, points);
            }
            return *this;
        }

        Rectangle<T>& operator=(Rectangle&& other) = default;

        Point<T> Center() const override {
            if (points.get() == nullptr) {
                return Point<T>(0, 0);
            }
            Point<T> p((points[0].x + points[2].x) / 2.0, (points[0].y + points[2].y) / 2.0);
            return p;
        }

        double Area() const override {
            if (points.get() == nullptr) {
                return 0;
            }
            double area = (std::fabs(points[0].x - points[2].x) * std::fabs(points[0].y - points[2].y));
            return area;
        }

        operator double() const override {
            return Area();
        }

        ~Rectangle() = default;
    };

    template<Scalar T>
    bool operator==(const Rectangle<T>& lf, const Rectangle<T>& rf) {
        bool l = std::fabs(lf.points[0].x - lf.points[3].x) == std::fabs(rf.points[0].x - rf.points[3].x);
        bool w = std::fabs(std::fabs(lf.points[0].y - lf.points[3].y)) == std::fabs(std::fabs(rf.points[0].y - rf.points[3].y));
        bool res = w && l; 
        return res;
    }

    template <Scalar T>
    bool operator!=(const Rectangle<T>& lf, const Rectangle<T>& rf) {
        return !(lf == rf);
    }

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Rectangle<T>& r) {
        for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
            os << r.points[i];
        }
        return os;
    }

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Rectangle<T>& r) {
        Point<T> ipoints[RECTANGLEANGLES];
        for (size_t i = 0; i < RECTANGLEANGLES; ++i) {
            is >> ipoints[i];
        }
        try {
            Rectangle temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
            std::swap(r.points, temp.points);
        } catch (exceptions::InvalidPointsException&) {
            std::cerr << "Rectangle: invalid points from input stream!" << std::endl;
        }
        return is;
    }
}