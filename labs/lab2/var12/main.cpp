#include "money.h"

int main() {
    std::string input;
    std::cin >> input;
    money::Money money(input);
    std::cout << money.CheckBalance() << std::endl;
    return 0;
}