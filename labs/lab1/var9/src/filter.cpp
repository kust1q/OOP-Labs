#include <iostream>
#include <string>
#include <vector>

#include <filter.h>

namespace filter {
    std::vector<std::string> filter(const std::string& input) {
        std::vector<std::string> numbers{};
        std::string buf = "";
        for (size_t i = 0; i < input.length(); ++i) {
            if (('1' <= input[i] && input[i] <= '9') || (input[i] == '0' && !buf.empty())) {
                buf += input[i];
            } else if (!buf.empty()) {
                numbers.push_back(buf);
                buf.clear();
            }
        }
        if (!buf.empty()) {
            numbers.push_back(buf);
        }
        return numbers;
    }
}