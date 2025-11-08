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

class InvalidBlockSizeException: public std::exception {
public:
    explicit InvalidBlockSizeException(const std::string& text) : error_message_(text) {
    }

    const char* what() const noexcept override {
        return error_message_.data();
    }

private:
    std::string error_message_;
};

class InvalidPoolSizeException: public std::exception {
public:
    explicit InvalidPoolSizeException(const std::string& text) : error_message_(text) {
    }

    const char* what() const noexcept override {
        return error_message_.data();
    }

private:
    std::string error_message_;
};

