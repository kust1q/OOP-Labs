#include "money.h"

int main() {
    std::string input;
    std::cin >> input;
    money::Money money = money::Money(input);
    std::cout << money.CheckBalance() << std::endl;
    return 0;
}