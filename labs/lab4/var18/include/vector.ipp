#pragma once

#include "vector.hpp"

namespace figure {
    template <typename T>
    Vector<T>::Vector() : sz_(0), cap_(0), arr_(std::shared_ptr<T[]>(nullptr)) {}

    template <typename T>
    Vector<T>::Vector(size_t count, const T& value) : sz_(count), cap_(count) {
        arr_ = std::shared_ptr<T[]>(new T[cap_], deleter);
        for (size_t i = 0; i < sz_; ++i) {
            new (Data() + i) T(value);
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector& other) : sz_(other.sz_), cap_(other.cap_) {
        arr_ = std::shared_ptr<T[]>(new T[cap_], deleter);
        for (size_t i = 0; i < sz_; ++i) {
            new (Data() + i) T(other[i]);
        }
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector& other) {
        if (&other == this) {
            return *this;
        }
        Vector<T> temp = other;
        Swap(temp);
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector&& other) {
        Vector<T> new_v(std::move(other));
        Swap(new_v);
        return *this;
    }

    template <typename T>
    Vector<T>::Vector(Vector&& other) noexcept : sz_(other.sz_), cap_(other.cap_), arr_(std::move(other.arr_)) {
        other.sz_ = 0;
        other.cap_ = 0;
        other.arr_.reset();
    }

    template <typename T>
    Vector<T>::Vector(const std::initializer_list<T>& init) : sz_(init.size()), cap_(init.size()) {
        arr_ = std::shared_ptr<T[]>(new T[cap_], deleter);
        size_t i = 0;
        for (const T& val : init) {
            new (Data() + i) T(std::move(val));
            ++i;
        }
    }

    template <typename T>
    T& Vector<T>::operator[](size_t pos) {
        return Data()[pos];
    }

    template <typename T>
    const T& Vector<T>::operator[](size_t pos) const {
        return Data()[pos];
    }

    template <typename T>
    T& Vector<T>::Front() const {
        return Data()[0];
    }

    template <typename T>
    bool Vector<T>::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    template <typename T>
    T& Vector<T>::Back() const {
        return Data()[sz_ - 1];
    }

    template <typename T>
    T* Vector<T>::Data() const noexcept {
        return arr_.get();
    }

    template <typename T>
    size_t Vector<T>::Size() const noexcept {
        return sz_;
    }

    template <typename T>
    size_t Vector<T>::Capacity() const noexcept {
        return cap_;
    }

    template <typename T>
    void Vector<T>::Reserve(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }
        std::shared_ptr<T[]> newArr = std::shared_ptr<T[]>(new T[new_cap], deleter);
        T* newData = newArr.get();
        for (size_t i = 0; i < sz_; i++) {
            new (newData + i) T(std::move(Data()[i]));
            Data()[i].~T(); 
        }
        arr_ = newArr;
        cap_ = new_cap;
    }

    template <typename T>
    void Vector<T>::Clear() noexcept {
        for (size_t i = 0; i < sz_; ++i) {
            Data()[i].~T();
        }
        arr_.reset();
        sz_ = 0;
        cap_ = 0;
    }

    template <typename T>
    void Vector<T>::Insert(size_t pos, T value) {
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

    template <typename T>
    void Vector<T>::Erase(size_t begin_pos, size_t end_pos) {
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

    template <typename T>
    void Vector<T>::PushBack(T value) {
        if (cap_ == sz_) {
            Reserve(cap_ != 0 ? cap_ * 2 : 1);
        }
        new (Data() + sz_) T(std::move(value));
        ++sz_;
    }

    template <typename T>
    template <class... Args>
    void Vector<T>::EmplaceBack(Args&&... args) {
        if (cap_ == sz_) {
            Reserve(cap_ != 0 ? cap_ * 2 : 1);
        }
        new (Data() + sz_) T(std::forward<Args>(args)...);
        ++sz_;
    }

    template <typename T>
    void Vector<T>::PopBack() {
        if (sz_ > 0) {
            Data()[sz_ - 1].~T();
            --sz_;
        }
    }

    template <typename T>
    void Vector<T>::Resize(size_t count, const T& value) {
        if (count > cap_) {
            Reserve(count);
        }
        for (size_t i = sz_; i < count; ++i) {
            new (Data() + i) T(std::move(value));
        }
        sz_ = count;
    }

    template <typename T>
    template <typename U>
    U Vector<T>::CommonArea() {
        U res = 0.0;
        for (size_t i = 0; i < sz_; ++i) {
            res += Data()[i]->Area();
        }
        return res;
    }

    template <typename T>
    void Vector<T>::SeparateCenter() {
        for (size_t i = 0; i < sz_; ++i) {
            std::cout << "Figure's center " << i + 1 << ": " << Data()[i]->Center() << std::endl;
        }
    }

    template <typename T>
    void Vector<T>::SeparateArea() {
        for (size_t i = 0; i < sz_; ++i) {
            std::cout << "Figure's area " << i + 1 << ": " << Data()[i]->Area() << std::endl;
        }
    }

    template <typename T>
    Vector<T>::~Vector() {
        for (size_t i = 0; i < sz_; ++i) {
            Data()[i].~T();
        }
    }

    template <typename T>
    void Vector<T>::Swap(Vector& v) {
        std::swap(v.arr_, arr_);
        std::swap(v.sz_, sz_);
        std::swap(v.cap_, cap_);
    }

    template<typename T>
    void swap(Vector<T>& v1, Vector<T>& v2) noexcept {
        v1.Swap(v2);
    }
}