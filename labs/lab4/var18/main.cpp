#include "exceptions.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "trapezoid.hpp"

int main() {
    figure::Square<double> s;
    std::cout << "Enter the square points:" << std::endl;
    std::cin >> s;

    figure::Rectangle<double> r;
    std::cout << "Enter the rectangle points:" << std::endl;
    std::cin >> r;

    figure::Trapezoid<double> t;
    std::cout << "Enter the trapezoid points:" << std::endl;
    std::cin >> t;

    std::cout << "Square: " << s << std::endl;
    std::cout << "Rectangle: " << r << std::endl;
    std::cout << "Trapezoid: " << t << std::endl;
    return 0;
}