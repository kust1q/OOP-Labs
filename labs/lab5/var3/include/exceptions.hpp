#pragma once

#include <exception>
#include <string>

class ListIsEmptyException: public std::exception {
public:
    explicit ListIsEmptyException(const std::string& text) : error_message_(text) {
    }

    const char* what() const noexcept override {
        return error_message_.data();
    }

private:
    std::string error_message_;
};

class InvalidDeallocatedBitesSisezSizeException: public std::exception {
public:
    explicit InvalidDeallocatedBitesSisezSizeException(const std::string& text) : error_message_(text) {
    }

    const char* what() const noexcept override {
        return error_message_.data();
    }

private:
    std::string error_message_;
};

class InvalidDeallocatedBlockException: public std::exception {
public:
    explicit InvalidDeallocatedBlockException(const std::string& text) : error_message_(text) {
    }

    const char* what() const noexcept override {
        return error_message_.data();
    }

private:
    std::string error_message_;
};

