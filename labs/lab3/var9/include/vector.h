#pragma once

#include <cstdlib>
#include <initializer_list>
#include <utility>

#include "figure.h"

namespace vector {
    class Vector {
      public:
        Vector();

        Vector(std::initializer_list<figure::Figure*> init);

        figure::Figure& operator[](size_t pos);

        const figure::Figure& operator[](size_t pos) const;

        figure::Figure& Front() const noexcept;

        figure::Figure& Back() const noexcept;

        figure::Figure** Data() const noexcept;

        bool IsEmpty() const noexcept;

        size_t Size() const noexcept;

        size_t Capacity() const noexcept;

        void Reserve(size_t new_cap);

        void Clear() noexcept;

        void Insert(size_t pos, figure::Figure* value);

        void Erase(size_t begin_pos, size_t end_pos);

        void PushBack(figure::Figure* value);

        void PopBack();

        double CommonArea();

        void SeparateCenter();

        void SeparateArea();

        ~Vector();

    private:
        size_t sz_;
        size_t cap_;
        figure::Figure** arr_;

        void Swap(Vector& v) {
            std::swap(v.arr_, arr_);
            std::swap(v.sz_, sz_);
            std::swap(v.cap_, cap_);
        }
    };
}