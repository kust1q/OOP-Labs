#pragma once

#include <cstdlib>
#include <iostream>
#include <initializer_list>
#include <memory>
#include <utility>

namespace figure {
    constexpr const size_t BASECAP = 3;

    template <typename T>
    class Vector {
        template<typename U>
        friend void swap(Vector<U>& v1, Vector<U>& g2) noexcept;
      public:
        Vector() : sz_(0), cap_(BASECAP), arr_(std::make_shared<T[]>(BASECAP)) {
        }

        Vector(size_t count, const T& value) : sz_(count), cap_(count) {
            arr_ = std::make_shared<T[]>(cap_);
            for (size_t i = 0; i < sz_; ++i) {
                arr_[i] = value;
            }
        }

        Vector(const Vector& other) : sz_(other.sz_), cap_(other.cap_) {
            arr_ = std::make_shared<T[]>(cap_);
            for (size_t i = 0; i < sz_; ++i) {
                arr_[i] = other.arr_[i];
            }
        }

        Vector<T>& operator=(const Vector& other) {
            if (&other == this) {
                return *this;
            }
            Vector<T> temp = other;
            Swap(temp);
            return *this;
        }

        Vector<T>& operator=(Vector&& other) {
            Vector<T> new_v(std::move(other));
            Swap(new_v);
            return *this;
        }

        Vector(Vector&& other) noexcept : sz_(other.sz_), cap_(other.cap_), arr_(other.arr_) {
            other.arr_ = nullptr;
            other.sz_ = 0;
            other.cap_ = 0;
        }

        Vector(std::initializer_list<T> init) : sz_(init.size()), cap_(init.size()) {
            arr_ = std::make_shared<T[]>(cap_);
            size_t i = 0;
            for (const T& val : init) {
                arr_[i] = std::move(val);
                ++i;
            }
        }

        T& operator[](size_t pos) {
            return arr_[pos];
        }

        const T& operator[](size_t pos) const {
            return arr_[pos];
        }

        T& Front() const noexcept {
            return arr_[0];
        }

        bool IsEmpty() const noexcept {
            return sz_ == 0;
        }

        T& Back() const noexcept {
            return arr_[sz_ - 1];
        }

        T* Data() const noexcept {
            return arr_.get();
        }

        size_t Size() const noexcept {
            return sz_;
        }

        size_t Capacity() const noexcept {
            return cap_;
        }

        void Reserve(size_t new_cap) {
            if (new_cap <= cap_) {
                return;
            }
            std::shared_ptr<T[]> newArr = std::make_shared<T[]>(new_cap);
            for (size_t i = 0; i < sz_; i++) {
                newArr[i] = (std::move(arr_[i]));
            }
            arr_ = newArr;
            cap_ = new_cap;
        }

        void Clear() noexcept {
            sz_ = 0;
        }

        void Insert(size_t pos, T value) {
            if (sz_ == cap_) {
                Reserve(cap_ * 2);
            };
            if (pos >= sz_) {
                PushBack(std::move(value));
                return;
            }
            for (size_t i = sz_; i > pos; --i) {
                arr_[i] = std::move(arr_[i - 1]);
            }
            arr_[pos] = std::move(value);
            ++sz_;
        }

        void Erase(size_t begin_pos, size_t end_pos) {
            if (begin_pos >= end_pos || end_pos > sz_) {
                return;
            };
            for (size_t i = end_pos; i < sz_; ++i) {
                arr_[begin_pos + i - end_pos] = std::move(arr_[i]);
            }
            sz_ -= (end_pos - begin_pos);
        }

        void PushBack(T value) {
            if (cap_ == sz_) {
                Reserve(2 * sz_);
            }
            arr_[sz_] = std::move(value);
            ++sz_;
        }

        template <class... Args>
        void EmplaceBack(Args&&... args) {
            if (cap_ == sz_) {
                Reserve(2 * cap_);
            }
            arr_[sz_] = T(std::forward<Args>(args)...);
            ++sz_;
        }

        void PopBack() {
            if (sz_ > 0) {
                --sz_;
            }
        }

        void Resize(size_t count, const T& value = T()) {
            if (count > cap_) {
                Reserve(count);
            }
            for (size_t i = sz_; i < count; ++i) {
                arr_[i] = std::move(value);
            }
            sz_ = count;
        }

        template<typename U>
        U CommonArea() {
            U res = 0.0;
            for (size_t i = 0; i < sz_; ++i) {
                res += arr_[i]->Area();
            }
            return res;
        }

        void SeparateCenter() {
            for (size_t i = 0; i < sz_; ++i) {
                std::cout << "Figure's center " << i + 1 << ": " << arr_[i]->Center() << std::endl;
            }
        }

        void SeparateArea() {
            for (size_t i = 0; i < sz_; ++i) {
                std::cout << "Figure's area " << i + 1 << ": " << arr_[i]->Area() << std::endl;
            }
        }

        ~Vector() = default;

      private:
        size_t sz_;
        size_t cap_;
        std::shared_ptr<T[]> arr_;

        void Swap(Vector& v) {
            std::swap(v.arr_, arr_);
            std::swap(v.sz_, sz_);
            std::swap(v.cap_, cap_);
        }
    };

    template<typename T>
    void swap(Vector<T>& v1, Vector<T>& v2) noexcept {
        v1.Swap(v2);
    }
}
