#pragma once 

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>

#include "exceptions.h"

namespace money {
    class Money {
      private:
        size_t sz_;
        unsigned char* arr_;

      public:
        Money();

        Money(const size_t& n, unsigned char c = 0);

        Money(const std::initializer_list<unsigned char>& init);

        Money(const std::string& s);

        Money(const Money& other) noexcept;

        Money(Money&& other);
        
        ~Money() noexcept;

        Money Add(const Money& other) const;

        Money Sub(const Money& other) const;

        void Copy(Money other);

        bool GT(const Money& other) const;

        bool LT(const Money& other) const;

        bool EQ(const Money& other) const;

        std::string CheckBalance() const;
    };
}