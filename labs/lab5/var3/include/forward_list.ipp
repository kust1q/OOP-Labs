#pragma once

#include "forward_list.hpp"

template <typename T>
ForwardList<T>::Node::Node() : val_(), next_(nullptr) {}

template <typename T>
ForwardList<T>::Node::Node(T val) : val_(val), next_(nullptr) {}

template <typename T>
ForwardList<T>::ForwardListIterator::ForwardListIterator(Node* node) : current_(node) {}

template <typename T>
bool ForwardList<T>::ForwardListIterator::operator==(const ForwardListIterator& other) const {
    return current_ == other.current_;
}

template <typename T>
bool ForwardList<T>::ForwardListIterator::operator!=(const ForwardListIterator& other) const {
    return current_ != other.current_;
}

template <typename T>
typename ForwardList<T>::ForwardListIterator::reference_type ForwardList<T>::ForwardListIterator::operator*() const {
    return current_->val_;
}

template <typename T>
typename ForwardList<T>::ForwardListIterator& ForwardList<T>::ForwardListIterator::operator++() {
    current_ = current_->next_;
    return *this;
}

template <typename T>
typename ForwardList<T>::ForwardListIterator ForwardList<T>::ForwardListIterator::operator++(int) {
    ForwardListIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename ForwardList<T>::ForwardListIterator::pointer_type ForwardList<T>::ForwardListIterator::operator->() const {
    return std::addressof(current_->val_);
}

template <typename T>
ForwardList<T>::ForwardList(std::pmr::memory_resource* res): alloc_(res), head_(alloc_.allocate(1)), sz_(0) {
    try {
        alloc_.construct(head_);
    } catch (...) {
        alloc_.deallocate(head_, 1);
        throw;
    }
}

template <typename T>
ForwardList<T>::ForwardList(size_t sz, std::pmr::memory_resource* res): alloc_(res), head_(alloc_.allocate(1)), sz_(sz) {
    try {
        alloc_.construct(head_);
    } catch (...) {
        alloc_.deallocate(head_, 1);
        throw;
    }

    Node* cur = head_;
    for (size_t i = 0; i < sz; ++i) {
        Node* new_node = alloc_.allocate(1);
        try {
            alloc_.construct(new_node);
        } catch (...) {
            alloc_.deallocate(new_node, 1);
            throw;
        }
        cur->next_ = new_node;
        cur = cur->next_;
    }
}

template <typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& values, std::pmr::memory_resource* res): alloc_(res), head_(alloc_.allocate(1)), sz_(values.size()) {
    try {
        alloc_.construct(head_);
    } catch (...) {
        alloc_.deallocate(head_, 1);
        throw;
    }

    Node* cur = head_;
    for (auto& val : values) {
        Node* new_node = alloc_.allocate(1);
        try {
            alloc_.construct(new_node, val);
        } catch (...) {
            alloc_.deallocate(new_node, 1);
            throw;
        }
        cur->next_ = new_node;
        cur = cur->next_;
    }
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other): alloc_(other.alloc_), head_(alloc_.allocate(1)), sz_(other.Size()) {
    try {
        alloc_.construct(head_);
    } catch (...) {
        alloc_.deallocate(head_, 1);
        throw;
    }

    Node* cur = head_;
    for (auto it = other.Begin(); it != other.End(); ++it) {
        Node* new_node = alloc_.allocate(1);
        try {
            alloc_.construct(new_node, *it);
        } catch (...) {
            alloc_.deallocate(new_node, 1);
            throw;
        }
        cur->next_ = new_node;
        cur = cur->next_;
    }
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& other) {
    if (this == &other) {
        return *this;
    }
    
    Clear();
    Node* cur = head_;
    for (auto it = other.Begin(); it != other.End(); ++it) {
        Node* new_node = alloc_.allocate(1);
        try {
            alloc_.construct(new_node, *it);
        } catch (...) {
            alloc_.deallocate(new_node, 1);
            throw;
        }
        cur->next_ = new_node;
        cur = cur->next_;
        ++sz_;
    }
    
    return *this;
}

template <typename T>
typename ForwardList<T>::ForwardListIterator ForwardList<T>::Begin() const noexcept {
    return ForwardListIterator(head_->next_);
}

template <typename T>
typename ForwardList<T>::ForwardListIterator ForwardList<T>::End() const noexcept {
    return ForwardListIterator(nullptr);
}

template <typename T>
T& ForwardList<T>::Front() const {
    if (IsEmpty()) {
        throw ListIsEmptyException("List is empty!");
    }
    return head_->next_->val_;
}

template <typename T>
bool ForwardList<T>::IsEmpty() const noexcept {
    return sz_ == 0;
}

template <typename T>
size_t ForwardList<T>::Size() const noexcept {
    return sz_;
}

template <typename T>
void ForwardList<T>::EraseAfter(ForwardListIterator pos) {
    if (IsEmpty()) {
        throw ListIsEmptyException("List is empty!");
    }
    if (pos.current_ == nullptr || pos.current_->next_ == nullptr) {
        return;
    }
    Node* del = pos.current_->next_;
    pos.current_->next_ = del->next_;

    std::destroy_at(del);
    alloc_.deallocate(del, 1);
    --sz_;
}

template <typename T>
void ForwardList<T>::InsertAfter(ForwardListIterator pos, const T& value) {
    if (pos.current_ == nullptr) {
        return;
    }
    Node* new_node = alloc_.allocate(1);
    try {
        alloc_.construct(new_node, value);
    } catch (...) {
        alloc_.deallocate(new_node, 1);
        throw;
    }
    Node* temp = pos.current_->next_;
    pos.current_->next_ = new_node;
    new_node->next_ = temp;
    ++sz_;
}

template <typename T>
typename ForwardList<T>::ForwardListIterator ForwardList<T>::Find(const T& value) const {
    for (auto it = Begin(); it != End(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return End();
}

template <typename T>
void ForwardList<T>::Clear() noexcept {
    Node* cur = head_->next_;
    while (cur != nullptr) {
        Node* next = cur->next_;
        std::destroy_at(cur);
        alloc_.deallocate(cur, 1);
        cur = next;
    }
    head_->next_ = nullptr;
    sz_ = 0;
}

template <typename T>
void ForwardList<T>::PushFront(const T& value) {
    Node* new_node = alloc_.allocate(1);
    try {
        alloc_.construct(new_node, value);
    } catch (...) {
        alloc_.deallocate(new_node, 1);
        throw;
    }

    Node* temp = head_->next_;
    head_->next_ = new_node;
    new_node->next_ = temp;
    ++sz_;
}

template <typename T>
void ForwardList<T>::PopFront() {
    if (IsEmpty()) {
        throw ListIsEmptyException("List is empty!");
    }
    Node* del = head_->next_;
    head_->next_ = del->next_;

    std::destroy_at(del);
    alloc_.deallocate(del, 1);
    --sz_;
}

template <typename T>
ForwardList<T>::~ForwardList() {
    Clear();
    std::destroy_at(head_);
    alloc_.deallocate(head_, 1);
}