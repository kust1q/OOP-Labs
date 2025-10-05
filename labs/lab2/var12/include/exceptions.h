#pragma once

#include <exception>
#include <string>

namespace exceptions {
    class NotNumberExceptions: std::exception {
    public:
        explicit NotNumberExceptions(const std::string& text): error_message_(text) {}
        const char* what() const noexcept override {
            return error_message_.data();
        }
    private:
        std::string_view error_message_;
    };

    class NegativeBalanceExceptions: std::exception {
    public:
        explicit NegativeBalanceExceptions(const std::string& text): error_message_(text) {}
        const char* what() const noexcept override {
            return error_message_.data();
        }
    private:
        std::string error_message_;
    };
}