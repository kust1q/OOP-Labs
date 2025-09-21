#pragma once

#include <initializer_list>
#include <utility>
#include <cstdlib>
#include <cstddef>
#include <new>

namespace vector {
    const int8_t BASECAP = 10;

    class Vector {
    public:
        Vector();

        Vector(size_t count, unsigned char value);

        Vector(const Vector& other);

        Vector(Vector&& other) noexcept;

        Vector(std::initializer_list<unsigned char> init);

        Vector& Copy(const Vector& other);

        Vector& Rotate(Vector&& other);

        unsigned char& Get(size_t pos);

        unsigned char Get(size_t pos) const;

        size_t Size() const noexcept;

        size_t Capacity() const noexcept;

        unsigned char& Front() const noexcept;

        unsigned char& Back() const noexcept;

        unsigned char* Data() const noexcept;

        bool IsEmpty() const noexcept;

        void Reserve(size_t new_cap);

        void Clear() noexcept;

        void Insert(size_t pos, unsigned char value);

        void Erase(size_t begin_pos, size_t end_pos);

        void PushBack(unsigned char value);

        void PopBack();

        void Resize(size_t count, unsigned char value);

        ~Vector();

    private:
        size_t sz_;
        size_t cap_;
        unsigned char* arr_;

        void Swap(Vector& v) {
            std::swap(v.arr_, arr_);
            std::swap(v.sz_, sz_);
            std::swap(v.cap_, cap_);
        }
    };
}

