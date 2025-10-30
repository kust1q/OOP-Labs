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
        bool Validate(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) const;

      public:
        Rectangle();
        Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4);
        Rectangle(const Rectangle& other);
        Rectangle(Rectangle&& other) = default;
        Rectangle<T>& operator=(const Rectangle& other);
        Rectangle<T>& operator=(Rectangle&& other) = default;
        Point<T> Center() const override;
        double Area() const override;
        operator double() const override;
        ~Rectangle() = default;
    };

    template<Scalar T>
    bool operator==(const Rectangle<T>& lf, const Rectangle<T>& rf);

    template <Scalar T>
    bool operator!=(const Rectangle<T>& lf, const Rectangle<T>& rf);

    template <Scalar T>
    std::ostream& operator<<(std::ostream& os, const Rectangle<T>& r);

    template <Scalar T>
    std::istream& operator>>(std::istream& is, Rectangle<T>& r);
}

#include "rectangle.ipp"