#include "exceptions.h"
#include "money.h"

int main() {
    std::string input;
    std::cin >> input;
    try {
        money::Money money(input);
        std::cout << money.CheckBalance() << std::endl;
    } catch (exceptions::NotNumberExceptions) {
        std::cout << "Not a number!" << std::endl;
    }
    return 0;
}