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
        bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const;
        std::unique_ptr<T[]> GetLengths() const;

      public:
        Trapezoid();
        Trapezoid(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
        Trapezoid(const Trapezoid& other);
        Trapezoid(Trapezoid&& other) = default;
        Trapezoid<T>& operator=(const Trapezoid& other);
        Trapezoid<T>& operator=(Trapezoid&& other) = default;
        Point<T> Center() const override;
        double Area() const override;
        operator double() const override;
        ~Trapezoid() = default;
    };

    template <Scalar T>
    bool operator==(const Trapezoid<T>& lf, const Trapezoid<T>& rf);

    template <Scalar T>
    bool operator!=(const Trapezoid<T>& lf, const Trapezoid<T>& rf);

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& r);

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Trapezoid<T>& r);
}

#include "trapezoid.ipp"