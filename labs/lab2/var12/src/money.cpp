#include "money.h"
#include <cstddef>

namespace money {
    Money::Money(): sz_(0), arr_(nullptr) {};

    Money::Money(const size_t& n, unsigned char c): sz_(n), arr_(new unsigned char[sz_]) {
        for (size_t i = 0; i < sz_; ++i) {
            arr_[i] = c;
        }
    };

    Money::Money(const std::initializer_list<unsigned char>& init){
        size_t i = 0;
        for (unsigned char c: init) {
            if (c != 0) {
                break;
            }
            ++i;
        }
        sz_ = init.size() - i;
        arr_ = new unsigned char[sz_];
        size_t j = 0;
        for (unsigned char c: init) {
            if (j < i) {
                ++j;
                continue;
            }
            arr_[sz_ - (j - i) - 1] = c;
            ++j;
        }
    };

    Money::Money(const std::string& s) {
        size_t l = 0;
        size_t r = s.length() - 1;

        for (char c: s) {
            if (c == '0') {
                ++l;
            } else {
                break;
            }
        }

        sz_ = r - l + 1;
        arr_ = new unsigned char[sz_];
        size_t i = sz_ - 1;
        while (l <= r) {
            if (s[l] < '0' || s[l]> '9') {
                delete[] arr_; 
                throw exceptions::NotNumberExceptions("Not a number!");
            }
            arr_[i] = s[l] - '0';
            --i;
            ++l;
        }
    };

    Money::Money(const Money& other) noexcept: sz_(other.sz_), arr_(new unsigned char [sz_]) {
        for (size_t i = 0; i < sz_; ++i) {
            arr_[i] = other.arr_[i];
        }
    };

    Money::Money(Money&& other): sz_(other.sz_), arr_(other.arr_) {
        other.arr_ = nullptr;
        other.sz_ = 0;
    };
        
    Money::~Money() noexcept {
        delete [] arr_;
    };

    Money Money::Add(const Money& other) const {
        unsigned char sum = 0;
        std::string res;
        for (size_t g = 0; g < std::max(sz_, other.sz_); ++g) {
            if (g >= sz_) {
                sum += other.arr_[g];
            } else if (g >= other.sz_) {
                sum += arr_[g];
            } else {
                sum += (arr_[g] + other.arr_[g]);
            }
            res += (sum % 10) + '0';
            sum /= 10;
        }
        if (sum == 1) {
            res += '1';
        }
        std::reverse(res.begin(), res.end());
        return Money(res);
    };

    Money Money::Sub(const Money& other) const {
        if (LT(other)) {
            throw exceptions::NegativeBalanceExceptions("Negative balance!");
        }
        std::string res;
        size_t i = 0;
        for (size_t g = 0; g < other.sz_; ++g) {
            i = g + 1;
            if (arr_[g] < other.arr_[g]) {
                res += (10 + arr_[g] - other.arr_[g]) + '0';
                --arr_[g + 1];  
                continue;
            }
            res += (arr_[g] - other.arr_[g]) + '0';
        }
        while (i < sz_) {
            res += arr_[i] + '0';
            ++i;
        }
        std::reverse(res.begin(), res.end());
        return Money(res);
    };

    void Money::Copy(Money other) {
        std::swap(arr_, other.arr_);
        std::swap(sz_, other.sz_);
    };

    bool Money::GT(const Money& other) const {
        if (sz_ > other.sz_) {
            return true;
        } else if (other.sz_ > sz_) {
            return false;
        }
        for (int64_t i = sz_ - 1; i >= 0; --i) {
            if (arr_[i] > other.arr_[i]) {
                return true;
            }
        }
        return false;
    };

    bool Money::LT(const Money& other) const {
        if (sz_ < other.sz_) {
            return true;
        } else if (other.sz_ < sz_) {
            return false;
        }
        for (int64_t i = sz_ - 1; i >= 0; --i) {
            if (arr_[i] < other.arr_[i]) {
                return true;
            }
        }
        return false;
    };

    bool Money::EQ(const Money& other) const {
        return !GT(other) && !LT(other);
    };

    std::string Money::CheckBalance() const {
        if (sz_ == 0) {
            return "0k.";
        }
        std::string kopecks;
        if (sz_ <= 2) {
            for (int64_t i = sz_ - 1; i >= 0; --i) {
                kopecks += (arr_[i] + '0');
            }
            return (kopecks + "k.");
        }
        std::string rubles;
        for (size_t i = sz_ - 1; i > 1; --i) {
            rubles += (arr_[i] + '0');
        }
        kopecks += (arr_[1] + '0');
        kopecks += (arr_[0] + '0');
        return (rubles + "P. " + kopecks + "k.");
    };
}