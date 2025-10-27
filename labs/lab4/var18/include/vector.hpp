#pragma once

#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>

namespace figure {
    template <typename T>
    class Vector {
        template<typename U>
        friend void swap(Vector<U>& v1, Vector<U>& g2) noexcept;
      public:
        Vector() : sz_(0), cap_(0), arr_(std::shared_ptr<int8_t[]>(nullptr)) {}

        Vector(size_t count, const T& value) : sz_(count), cap_(count) {
            arr_ = std::shared_ptr<int8_t[]>(new int8_t[sizeof(T) * cap_], deleter);
            for (size_t i = 0; i < sz_; ++i) {
                new (Data() + i) T(value);
            }
        }

        Vector(const Vector& other) : sz_(other.sz_), cap_(other.cap_) {
            arr_ = std::shared_ptr<int8_t[]>(new int8_t[sizeof(T) * cap_], deleter);
            for (size_t i = 0; i < sz_; ++i) {
                new (Data() + i) T(other[i]);
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

        Vector(Vector&& other) noexcept : sz_(other.sz_), cap_(other.cap_), arr_(std::move(other.arr_)) {
            other.sz_ = 0;
            other.cap_ = 0;
        }

        Vector(const std::initializer_list<T>& init) : sz_(init.size()), cap_(init.size()) {
            arr_ = std::shared_ptr<int8_t[]>(new int8_t[sizeof(T) * cap_], deleter);
            size_t i = 0;
            for (const T& val : init) {
                new (Data() + i) T(std::move(val));
                ++i;
            }
        }

        T& operator[](size_t pos) {
            return Data()[pos];
        }

        const T& operator[](size_t pos) const {
            return Data()[pos];
        }

        T& Front() const {
            return Data()[0];
        }

        bool IsEmpty() const noexcept {
            return sz_ == 0;
        }

        T& Back() const {
            return Data()[sz_ - 1];
        }

        T* Data() const noexcept {
            return reinterpret_cast<T*>(arr_.get());
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
            std::shared_ptr<int8_t[]> newArr = std::shared_ptr<int8_t[]>(new int8_t[sizeof(T) * new_cap], deleter);
            T* newData = reinterpret_cast<T*>(newArr.get());
            for (size_t i = 0; i < sz_; i++) {
                new (newData + i) T(std::move(Data()[i]));
                Data()[i].~T(); 
            }
            arr_ = newArr;
            cap_ = new_cap;
        }

        void Clear() noexcept {
            for (size_t i = 0; i < sz_; ++i) {
                Data()[i].~T();
            }
            arr_.reset();
            sz_ = 0;
            cap_ = 0;
        }

        void Insert(size_t pos, T value) {
            if (sz_ == cap_) {
                Reserve(cap_ != 0 ? cap_ * 2 : 1);
            };
            if (pos >= sz_) {
                PushBack(std::move(value));
                return;
            }
            for (size_t i = sz_; i > pos; --i) {
                new (Data() + i) T(std::move(Data()[i - 1]));
                Data()[i - 1].~T();
            }
            new (Data() + pos) T(std::move(value));
            ++sz_;
        }

        void Erase(size_t begin_pos, size_t end_pos) {
            if (begin_pos >= end_pos || end_pos > sz_) {
                return;
            };
            for (size_t i = begin_pos; i < end_pos; ++i) {
                Data()[i].~T();
            }
            for (size_t i = end_pos; i < sz_; ++i) {
                new (Data() + begin_pos + i - end_pos) T(std::move(Data()[i]));
            }
            sz_ -= (end_pos - begin_pos);
        }

        void PushBack(T value) {
            if (cap_ == sz_) {
                Reserve(cap_ != 0 ? cap_ * 2 : 1);
            }
            new (Data() + sz_) T(std::move(value));
            ++sz_;
        }

        template <class... Args>
        void EmplaceBack(Args&&... args) {
            if (cap_ == sz_) {
                Reserve(cap_ != 0 ? cap_ * 2 : 1);
            }
            new (Data() + sz_) T(std::forward<Args>(args)...);
            ++sz_;
        }

        void PopBack() {
            if (sz_ > 0) {
                Data()[sz_ - 1].~T();
                --sz_;
            }
        }

        void Resize(size_t count, const T& value = T()) {
            if (count > cap_) {
                Reserve(count);
            }
            for (size_t i = sz_; i < count; ++i) {
                new (Data() + i) T(std::move(value));
            }
            sz_ = count;
        }

        template<typename U>
        U CommonArea() {
            U res = 0.0;
            for (size_t i = 0; i < sz_; ++i) {
                res += Data()[i]->Area();
            }
            return res;
        }

        void SeparateCenter() {
            for (size_t i = 0; i < sz_; ++i) {
                std::cout << "Figure's center " << i + 1 << ": " << Data()[i]->Center() << std::endl;
            }
        }

        void SeparateArea() {
            for (size_t i = 0; i < sz_; ++i) {
                std::cout << "Figure's area " << i + 1 << ": " << Data()[i]->Area() << std::endl;
            }
        }

        ~Vector() {
            for (size_t i = 0; i < sz_; ++i) {
                Data()[i].~T();
            }
        }

      private:
        size_t sz_;
        size_t cap_;
        std::shared_ptr<int8_t[]> arr_;

        void Swap(Vector& v) {
            std::swap(v.arr_, arr_);
            std::swap(v.sz_, sz_);
            std::swap(v.cap_, cap_);
        }

        inline static auto deleter = [](int8_t* ptr) {
            delete[] ptr;
        };
    };

    template<typename T>
    void swap(Vector<T>& v1, Vector<T>& v2) noexcept {
        v1.Swap(v2);
    }
}
