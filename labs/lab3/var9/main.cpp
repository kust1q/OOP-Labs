#include "exceptions.h"
#include "rectangle.h"

int main() {
    figure::Rectangle r;
    try {
        std::cin >> r;
        std::cout << r << std::endl;
    } catch (exceptions::InvalidPointsException) {
        std::cout << "Wrong points!" << std::endl;
    }
    return 0;
}