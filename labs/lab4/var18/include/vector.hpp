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
        Vector();
        Vector(size_t count, const T& value);
        Vector(const Vector& other);
        Vector<T>& operator=(const Vector& other);
        Vector<T>& operator=(Vector&& other);
        Vector(Vector&& other) noexcept;
        Vector(const std::initializer_list<T>& init);
        
        T& operator[](size_t pos);
        const T& operator[](size_t pos) const;
        T& Front() const;
        bool IsEmpty() const noexcept;
        T& Back() const;
        T* Data() const noexcept;
        size_t Size() const noexcept;
        size_t Capacity() const noexcept;
        
        void Reserve(size_t new_cap);
        void Clear() noexcept;
        void Insert(size_t pos, T value);
        void Erase(size_t begin_pos, size_t end_pos);
        void PushBack(T value);
        
        template <class... Args>
        void EmplaceBack(Args&&... args);
        
        void PopBack();
        void Resize(size_t count, const T& value = T());
        
        template<typename U>
        U CommonArea();
        
        void SeparateCenter();
        void SeparateArea();
        
        ~Vector();

      private:
        size_t sz_;
        size_t cap_;
        std::shared_ptr<T[]> arr_;

        void Swap(Vector& v);
        inline static auto deleter = [](T* ptr) {
            delete[] ptr;
        };
    };

    template<typename T>
    void swap(Vector<T>& v1, Vector<T>& v2) noexcept;
}

#include "vector.ipp"