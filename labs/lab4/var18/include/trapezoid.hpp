#pragma once

#include "figure.hpp"
#include "exceptions.hpp"

namespace figure {
    template<Scalar T>
    class Trapezoid: public Figure<T> {
        template<Scalar U>
        friend bool operator==(const Trapezoid<U>& lf, const Trapezoid<U>& rf);
        template<Scalar U>
        friend bool operator!=(const Trapezoid<U>& lf, const Trapezoid<U>& rf);
        template<Scalar U>
        friend std::ostream& operator<<(std::ostream& os, const Trapezoid<U>& r);
        template<Scalar U>
        friend std::istream& operator>>(std::istream& is, Trapezoid<U>& r);
      private:
        std::unique_ptr<Point<T>[]> points;

        bool Validate(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) const {
            Point<T> pointsArr[TRAPEZOIDANGLES] = {p1, p2, p3, p4};
            for (int i = 0; i < TRAPEZOIDANGLES; ++i) {
                for (int j = i + 1; j < TRAPEZOIDANGLES; ++j) {
                    if (pointsArr[i] == pointsArr[j]) {
                        return false;
                    }
                }
            }

            Point<T> ab{p2.x - p1.x, p2.y - p1.y};
            Point<T> bc{p3.x - p2.x, p3.y - p2.y};
            Point<T> dc{p3.x - p4.x, p3.y - p4.y};
            Point<T> ad{p4.x - p1.x, p4.y - p1.y};
            
            bool firstVariant = AreParalel(ab, dc) && DistanceBetweenPoints(p2, p3) == DistanceBetweenPoints(p1, p4);
            bool secondVariant = AreParalel(bc, ad) && DistanceBetweenPoints(p1, p2) == DistanceBetweenPoints(p4, p3);

            return firstVariant || secondVariant;
        }
        
        std::unique_ptr<T[]> GetLengths() const {
            std::unique_ptr<T[]> lengths = std::make_unique<T[]>(TRAPEZOIDANGLES);
            lengths[0] = DistanceBetweenPoints(points[0], points[1]);
            lengths[1] = DistanceBetweenPoints(points[3], points[2]);
            lengths[2] = DistanceBetweenPoints(points[0], points[3]);
            lengths[3] = DistanceBetweenPoints(points[1], points[2]);

            for (size_t i = 0; i < TRAPEZOIDANGLES - 1; ++i) {
                for (size_t j = i + 1; j < TRAPEZOIDANGLES; ++j) {
                    if (lengths[j] < lengths[i]) {
                        std::swap(lengths[i], lengths[j]);
                    }
                }
            }
            return lengths;
        }

      public:
        Trapezoid(): Trapezoid(Point<T>(0.0, 0.0), Point<T>(0.0, 1.0), Point<T>(1.0, 1.0), Point<T>(1.0, 0.0)) {}

        Trapezoid(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4){
            if (!Validate(p1, p2, p3, p4)) {
                throw exceptions::InvalidPointsException("Trapezoid: invalid points!");
            }
            points = std::make_unique<Point<T>[]>(TRAPEZOIDANGLES);
            points[0] = p1;
            points[1] = p2;
            points[2] = p3;
            points[3] = p4;
        }

        Trapezoid(const Trapezoid& other) {
            points = std::make_unique<Point<T>[]>(TRAPEZOIDANGLES);
            for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
                points[i] = Point(other.points[i].x, other.points[i].y);
            }
        }

        Trapezoid(Trapezoid&& other): Trapezoid() {
            std::swap(points, other.points);
        }
        
        Trapezoid<T>& operator=(const Trapezoid& other) {
            if (&other != this) {
                for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
                    points[i] = other.points[i];
                }
            }
            return *this;
        }

        Trapezoid<T>& operator=(Trapezoid&& other) {
            if (&other != this) {
                Trapezoid<T> temp = std::move(other);
                std::swap(points, temp.points);
            }
            return *this;
        }

        Point<T> Center() const override {
            T sumX = 0.0;
            T sumY = 0.0;
            for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
                sumX += points[i].x;
                sumY += points[i].y;
            }
            Point<T> p(sumX / TRAPEZOIDANGLES, sumY / TRAPEZOIDANGLES);
            return p;
        }

        T Area() const override {
            T area = 0;
            for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
                size_t j = (i + 1) % TRAPEZOIDANGLES;
                area += points[i].x * points[j].y - points[j].x * points[i].y;
            }
            return std::abs(area) / 2;
        }

        operator double() const override {
            return Area();
        }

        ~Trapezoid() = default;
    };

    template <Scalar T>
    bool operator==(const Trapezoid<T>& lf, const Trapezoid<T>& rf) {
        if (lf.Area() != rf.Area()) {
            return false;
        }
        std::unique_ptr<T[]> lengths1 = lf.GetLengths();
        std::unique_ptr<T[]> lengths2 = lf.GetLengths();
        for (size_t i = 0; i < TRAPEZOIDANGLES; i++) {
            if (lengths1[i] != lengths2[i]) {
                return false;
            }
        }
        return true;
    }

    template <Scalar T>
    bool operator!=(const Trapezoid<T>& lf, const Trapezoid<T>& rf) {
        return !(lf == rf);
    }

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& r) {
        for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
           os << r.points[i];
        }
        return os;
    }

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Trapezoid<T>& r) {
        Point<T> ipoints[TRAPEZOIDANGLES];
        for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
            is >> ipoints[i];
        }
        try {
            Trapezoid temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
            std::swap(r.points, temp.points);
        } catch (exceptions::InvalidPointsException&) {
            std::cerr << "Trapezoid: invalid points from input stream!" << std::endl;
            return is;
        }
        return is;
    }
}