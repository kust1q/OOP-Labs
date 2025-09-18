#include "filter.h"

int main() {
    std ::string input;
    std::cin >> input;
    std::vector<std::string> numbers = filter::Filter(input);
    for (const std::string& num: numbers) {
        std::cout << num << std::endl;
    }
    return 0;
}