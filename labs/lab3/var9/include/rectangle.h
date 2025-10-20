#pragma once

#include "figure.h"

namespace figure {
    class Rectangle: public Figure {
        friend bool operator==(const Rectangle& lf, const Rectangle& rf);
        friend bool operator!=(const Rectangle& lf, const Rectangle& rf);
        friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);
        friend std::istream& operator>>(std::istream& is, Rectangle& r);
      private:
        Point* points[RECTANGLEANGLES];

        bool Validate(Point p1, Point p2, Point p3, Point p4) const;
        void Clear();
      public:
        Rectangle();
        Rectangle(Point p1, Point p2, Point p3, Point p4);
        Rectangle(const Rectangle& other);
        Rectangle& operator=(const Rectangle& other);
        Point Center() const override;
        double Area() const override;
        operator double() const override;
        ~Rectangle();
    };

    bool operator==(const Rectangle& lf, const Rectangle& rf);
    bool operator!=(const Rectangle& lf, const Rectangle& rf);
    std::ostream& operator<<(std::ostream& os, const Rectangle& r);
    std::istream& operator>>(std::istream& is, Rectangle& r);
}

