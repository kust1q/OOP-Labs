#include "vector.h"

namespace vector {
    Vector::Vector() : sz_(0), cap_(0), arr_(nullptr) {
    }

    Vector::Vector(size_t count, unsigned char value) : sz_(count), cap_(count) {
        arr_ = new unsigned char[sz_];
        for (size_t i = 0; i < sz_; ++i) {
            arr_[i] = value;
        }
    }

    Vector::Vector(const Vector& other) : sz_(other.sz_), cap_(other.cap_) {
        arr_ = reinterpret_cast<unsigned char*>(new int8_t[cap_ * sizeof(unsigned char)]);
        for (size_t i = 0; i < sz_; ++i) {
            new (arr_ + i) unsigned char(std::move(other.arr_[i]));
        }
    }

    Vector::Vector(Vector&& other) noexcept : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
        other.arr_ = nullptr;
        other.sz_ = 0;
        other.cap_ = 0;
    }

    Vector::Vector(std::initializer_list<unsigned char> init) : sz_(init.size()) {
        cap_ = init.size() < 10 ? 10 : init.size();  // NOLINT
        arr_ = reinterpret_cast<unsigned char*>(new int8_t[cap_]);
        size_t i = 0;
        for (unsigned char val : init) {
            new (arr_ + i) unsigned char(std::move(val));
            ++i;
        }
    }

    Vector& Vector::Copy(const Vector& other) {
        if (&other == this) {
        return *this;
        }
        Vector temp = other;
        Swap(temp);
        return *this;
    }

    Vector& Vector::Rotate(Vector&& other) {
        Vector temp(std::move(other));
        Swap(temp);
        return *this;
    }

    unsigned char& Vector::Get(size_t pos) {
        return arr_[pos];
    }

    unsigned char Vector::Get(size_t pos) const {
        return arr_[pos];
    }

    unsigned char& Vector::Front() const noexcept {
        return arr_[0];
    }

    bool Vector::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    unsigned char& Vector::Back() const noexcept {
        return arr_[sz_ - 1];
    }

    unsigned char* Vector::Data() const noexcept {
        return arr_;
    }

    size_t Vector::Size() const noexcept {
        return sz_;
    }

    size_t Vector::Capacity() const noexcept {
        return cap_;
    }

    void Vector::Reserve(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }
        unsigned char* new_arr = reinterpret_cast<unsigned char*>(new int8_t[new_cap]);
        for (size_t i = 0; i < sz_; i++) {
            new (new_arr + i) unsigned char(std::move(arr_[i]));
        }
        delete[] reinterpret_cast<int8_t*>(arr_);
        arr_ = new_arr;
        cap_ = new_cap;
    }

    void Vector::Clear() noexcept {
        delete[] reinterpret_cast<int8_t*>(arr_);
        arr_ = nullptr;
        sz_ = 0;
    }

    void Vector::Insert(size_t pos, unsigned char value) {
        if (sz_ == cap_) {
            Reserve(cap_ * 2);
        };
        if (pos >= sz_) {
            PushBack(value);
            return;
        }
        for (size_t i = sz_; i > pos; --i) {
            new (arr_ + i) unsigned char(std::move(arr_[i - 1]));
        }
        new (arr_ + pos) unsigned char(std::move(value));
        ++sz_;
    }

    void Vector::Erase(size_t begin_pos, size_t end_pos) {
        if (begin_pos >= end_pos || end_pos > sz_) {
            return;
        };
        for (size_t i = end_pos; i < sz_; ++i) {
            new (arr_ + begin_pos + i - end_pos) unsigned char(std::move(arr_[i]));
        }
        sz_ -= (end_pos - begin_pos);
    }

    void Vector::PushBack(unsigned char value) {
        if (cap_ == 0) {
            Reserve(10);  // NOLINT
        } else if (cap_ == sz_) {
            Reserve(2 * sz_);
        }
        new (arr_ + sz_) unsigned char(std::move(value));
        ++sz_;
    }

    void Vector::PopBack() {
        --sz_;
    }

    void Vector::Resize(size_t count, unsigned char value) {
        if (count > cap_) {
            Reserve(count);
        }
        for (size_t i = sz_; i < count; ++i) {
            new (arr_ + i) unsigned char(std::move(value));
        }
        sz_ = count;
    }

    Vector::~Vector() {
        delete[] reinterpret_cast<int8_t*>(arr_);
    }
}