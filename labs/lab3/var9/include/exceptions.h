#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {
    class InvalidPointsException: std::runtime_error {
    public:
        explicit InvalidPointsException(const std::string& text): std::runtime_error(text) {}
    };
}