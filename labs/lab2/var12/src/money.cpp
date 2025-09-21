#include "money.h"
#include "exceptions.h"
#include "vector.h"


namespace money {
    Money::Money(): arr_(vector::Vector())  {};

    Money::Money(const size_t& n, unsigned char c): arr_(vector::Vector(n, c)) {};

    Money::Money(const std::initializer_list<unsigned char>& init): arr_(vector::Vector(init.size(), 0)) {
        size_t i = init.size() - 1;
        for (unsigned char c: init) {
            arr_.Get(i) = c;
            --i;
        }
        unsigned char back = arr_.Back();
        while (back == 0) {
            arr_.PopBack();
            back = arr_.Back();
        }
    };

    Money::Money(const std::string& s): arr_(vector::Vector(s.length(), 0)) {
        size_t i = s.length() - 1;
        for (char c: s) {
            if (c < '0' || c > '9') {
                throw exceptions::NotNumberExceptions("Not a number!");
            }
            arr_.Get(i) = c - '0';
            --i;
        }
        unsigned char back = arr_.Back();
        while (back == 0) {
            arr_.PopBack();
            back = arr_.Back();
        }
    };

    Money::Money(const Money& other) noexcept: arr_(other.arr_) {};

    Money::Money(Money&& other): arr_(std::move(other.arr_)) {};
        
    Money::~Money() noexcept {
        arr_.Clear();
    };

    void Money::Copy(const Money& other) {
        arr_.Copy(other.arr_);
    };

    bool Money::GT(const Money& other) const {
        if (arr_.Size() > other.arr_.Size()) {
            return true;
        } else if (other.arr_.Size() > arr_.Size()) {
            return false;
        }
        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) > other.arr_.Get(i)) {
                return true;
            }
        }
        return false;
    };

    bool Money::LT(const Money& other) const {
        if (arr_.Size() < other.arr_.Size()) {
            return true;
        } else if (other.arr_.Size() < arr_.Size()) {
            return false;
        }
        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) < other.arr_.Get(i)) {
                return true;
            }
        }
        return false;
    };

    bool Money::EQ(const Money& other) const {
        if (other.arr_.Size() != arr_.Size()) {
            return false;
        }
        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) != other.arr_.Get(i)) {
                return false;
            }
        }
        return true;
    };

    std::string Money::CheckBalance() const {
        if (arr_.Size() == 0) {
            return "0k.";
        }
        std::string kopecks;
        if (arr_.Size() <= 2) {
            for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
                kopecks += (arr_.Get(i) + '0');
            }
            return (kopecks + "k.");
        }
        std::string rubles;
        for (size_t i = arr_.Size() - 1; i > 1; --i) {
            rubles += (arr_.Get(i) + '0');
        }
        kopecks += (arr_.Get(1) + '0');
        kopecks += (arr_.Get(0) + '0');
        return (rubles + "P. " + kopecks + "k.");
    };

    Money Add(const Money& m1, const Money& m2) {
        Money m3;
        unsigned char sum = 0;
        for (size_t i = 0; i < std::max(m2.arr_.Size(), m1.arr_.Size()); ++i) {
            if (i >= m1.arr_.Size()) {
                sum += m2.arr_.Get(i);
            } else if (i >= m2.arr_.Size()) {
                sum += m1.arr_.Get(i);
            } else {
                sum += (m1.arr_.Get(i) + m2.arr_.Get(i));
            }
            m3.arr_.PushBack(sum % 10);
            sum /= 10;
        }
        if (sum == 1) {
            m3.arr_.PushBack(sum);
        }
        return m3;
    }

    Money Sub(const Money& m1, const Money& m2) {
        if (m1.LT(m2)) {
            throw exceptions::NegativeBalanceExceptions("Negative balance!");
        } else if (m1.EQ(m2)) {
            return Money();
        }

        Money m3 = m1;
        for (size_t i = 0; i < m2.arr_.Size(); ++i) {
            if (m3.arr_.Get(i) < m2.arr_.Get(i)) {
                m3.arr_.Get(i) += (10 - m2.arr_.Get(i));
                --m3.arr_.Get(i + 1);
                continue;
            }
            m3.arr_.Get(i) -= m2.arr_.Get(i);
        }
        unsigned char back = m3.arr_.Back();
        while (back == 0) {
            m3.arr_.PopBack();
            back = m3.arr_.Back();
        }
        return m3;
    }
}