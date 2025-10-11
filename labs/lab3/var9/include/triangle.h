#pragma once

#include "figure.h"

namespace figure {
    class Triangle: public Figure {
        friend bool operator==(const Triangle& lf, const Triangle& rf);
        friend bool operator!=(const Triangle& lf, const Triangle& rf);
        friend std::ostream& operator<<(std::ostream& os, const Triangle& r);
        friend std::istream& operator>>(std::istream& is, Triangle& r);
      private:
        Point* points[3];

        bool Validate(Point p1, Point p2, Point p3) const;
        void Clear();
      public:
        Triangle() = default;
        Triangle(Point p1, Point p2, Point p3);
        Triangle(const Triangle& other);
        Triangle& operator=(const Triangle& other);
        Point Center() const override;
        double Area() const override;
        operator double() const override;
        ~Triangle();
    };
    bool operator==(const Triangle& l, const Triangle& r);
    bool operator!=(const Triangle& l, const Triangle& r);
    
    std::ostream& operator<<(std::ostream& os, const Triangle& s);
    std::istream& operator>>(std::istream& is, Triangle& s);
}