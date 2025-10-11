#include "vector.h"
#include "figure.h"

namespace vector {
    size_t BASECAP = 3;

    Vector::Vector() : sz_(0), cap_(0), arr_(nullptr) {}

    Vector::Vector(std::initializer_list<figure::Figure*> init): sz_(init.size()), cap_(init.size()) {
        arr_ = new figure::Figure*[init.size()];
        size_t i = 0;
        for (figure::Figure* f: init) {
            arr_[i] = f;
            ++i;
        }
    }

    figure::Figure& Vector::operator[](size_t pos) {
        return *arr_[pos];
    }

    const figure::Figure& Vector::operator[](size_t pos) const {
        return *arr_[pos];
    }

    figure::Figure& Vector::Front() const noexcept {
        return *arr_[0];
    }

    bool Vector::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    figure::Figure& Vector::Back() const noexcept {
        return *arr_[sz_ - 1];
    }

    figure::Figure** Vector::Data() const noexcept {
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
        figure::Figure** new_arr = reinterpret_cast<figure::Figure**>(new int8_t[new_cap * sizeof(figure::Figure*)]);
        for (size_t i = 0; i < sz_; i++) {
            new_arr[i] = arr_[i];
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

    void Vector::Insert(size_t pos, figure::Figure* value) {
        if (sz_ == cap_) {
            Reserve(cap_ * 2);
        };
        if (pos >= sz_) {
            PushBack(value);
            return;
        }
        for (size_t i = sz_; i > pos; --i) {
            arr_[i] = arr_[i - 1];
        }
        arr_[pos] = value;
        ++sz_;
    }

    void Vector::Erase(size_t begin_pos, size_t end_pos) {
        if (begin_pos >= end_pos || end_pos > sz_) {
            return;
        };
        for (size_t i = end_pos; i < sz_; ++i) {
            arr_[begin_pos + i - end_pos] = arr_[i];
        }
        sz_ -= (end_pos - begin_pos);
    }

    void Vector::PushBack(figure::Figure* value) {
        if (cap_ == 0) {
            Reserve(BASECAP);
        } else if (cap_ == sz_) {
            Reserve(2 * sz_);
        }
        arr_[sz_] = value;
        ++sz_;
    }

    void Vector::PopBack() {
        --sz_;
    }

    double Vector::CommonArea() {
        double res = 0.0;
        for (size_t i = 0; i < sz_; ++i) {
            res += arr_[i]->Area();
        }
        return res;
    }

    void Vector::SeparateCenter() {
        for (size_t i = 0; i < sz_; ++i) {
            std::cout << "Центр фигуры " << i + 1 << ": " << arr_[i]->Center() << std::endl;
        }
    }

    void Vector::SeparateArea() {
        for (size_t i = 0; i < sz_; ++i) {
            std::cout << "Площадь фигуры " << i + 1 << ": " << arr_[i]->Area() << std::endl;
        }
    }

    Vector::~Vector() {
        delete[] reinterpret_cast<int8_t*>(arr_);
    }
}