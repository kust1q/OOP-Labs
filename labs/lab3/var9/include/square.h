#pragma once

#include "figure.h"

namespace figure {
    class Square: public Figure {
        friend bool operator==(const Square& lf, const Square& rf);
        friend bool operator!=(const Square& lf, const Square& rf);
        friend std::ostream& operator<<(std::ostream& os, const Square& r);
        friend std::istream& operator>>(std::istream& is, Square& r);
      private:
        Point* points[SQUAREANGLES];

        bool Validate(Point p1, Point p2, Point p3, Point p4) const;
        void Clear();
      public:
        Square() = default;
        Square(Point p1, Point p2, Point p3, Point p4);
        Square(const Square& other);
        Square& operator=(const Square& other);
        Point Center() const override;
        double Area() const override;
        operator double() const override;
        ~Square();
    };

    bool operator==(const Square& lf, const Square& rf);
    bool operator!=(const Square& lf, const Square& rf);

    std::ostream& operator<<(std::ostream& os, const Square& s);
    std::istream& operator>>(std::istream& is, Square& s);
}

