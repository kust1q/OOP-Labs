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

#include "vector.h"
#include "exceptions.h"

namespace money {
    class Money {  
      private:
        vector::Vector arr_;

      public:
        Money();

        Money(const size_t& n, unsigned char c = 0);

        Money(const std::initializer_list<unsigned char>& init);

        Money(const std::string& s);

        Money(const Money& other) noexcept;

        Money(Money&& other);
        
        ~Money() noexcept;

        void Copy(const Money& other);

        bool GT(const Money& other) const;

        bool LT(const Money& other) const;

        bool EQ(const Money& other) const;

        std::string CheckBalance() const;

        static Money Add(const Money& m1, const Money& m2);

        static Money Sub(const Money& m1, const Money& m2);
    };
}