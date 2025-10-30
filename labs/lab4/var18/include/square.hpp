#pragma once

#include "figure.hpp"
#include "exceptions.hpp"

namespace figure {
    template<Scalar T>
    class Square: public Figure<T> {
        template<Scalar U>
        friend bool operator==(const Square<U>& lf, const Square<U>& rf);
        template<Scalar U>
        friend bool operator!=(const Square<U>& lf, const Square<U>& rf);
        template<Scalar U>
        friend std::ostream& operator<<(std::ostream& os, const Square<U>& r);
        template<Scalar U>
        friend std::istream& operator>>(std::istream& is, Square<U>& r);
      private:
        std::unique_ptr<Point<T>[]> points;
        bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const;

      public:
        Square();
        Square(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
        Square(const Square& other);
        Square(Square&& other) = default;
        Square<T>& operator=(const Square& other);
        Square<T>& operator=(Square&& other) = default;
        Point<T> Center() const override;
        double Area() const override;
        operator double() const override;
        ~Square() = default;
    };

    template <Scalar T>
    bool operator==(const Square<T>& lf, const Square<T>& rf);

    template <Scalar T>
    bool operator!=(const Square<T>& lf, const Square<T>& rf);

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Square<T>& r);

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Square<T>& r);
}

#include "square.ipp"