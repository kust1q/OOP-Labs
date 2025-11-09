#pragma once

#include <cstdlib>
#include <functional>
#include <iterator>
#include <memory_resource>
#include <utility>

#include "exceptions.hpp"

template <typename T>
class ForwardList { 
  private:
    class Node {
        friend class ForwardListIterator;
        friend class ForwardList;
        T val_;
        Node* next_;
      public:
        Node();
        explicit Node(T val);
    };

  public:
    class ForwardListIterator {
        friend class ForwardList;

      private:
        Node* current_;
        explicit ForwardListIterator(Node* node);

      public:
        using value_type = T;
        using reference_type = value_type&;
        using pointer_type = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        bool operator==(const ForwardListIterator& other) const;
        bool operator!=(const ForwardListIterator& other) const;
        reference_type operator*() const;
        ForwardListIterator& operator++();
        ForwardListIterator operator++(int);
        pointer_type operator->() const;
    };

  private:
    std::pmr::polymorphic_allocator<Node> alloc_;
    Node* head_;
    size_t sz_;

  public:
    ForwardList(std::pmr::memory_resource* res = std::pmr::get_default_resource());
    explicit ForwardList(size_t sz, std::pmr::memory_resource* res = std::pmr::get_default_resource());
    ForwardList(const std::initializer_list<T>& values, std::pmr::memory_resource* res = std::pmr::get_default_resource());
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other) noexcept;
    ForwardList& operator=(const ForwardList& other);
    ForwardList& operator=(ForwardList&& other) noexcept;
    
    ForwardListIterator Begin() const noexcept;
    ForwardListIterator End() const noexcept;
    T& Front() const;
    bool IsEmpty() const noexcept;
    size_t Size() const noexcept;
    
    void EraseAfter(ForwardListIterator pos);
    void InsertAfter(ForwardListIterator pos, const T& value);
    ForwardListIterator Find(const T& value) const;
    void Clear() noexcept;
    void PushFront(const T& value);
    void PopFront();
    
    ~ForwardList();
};

#include "forward_list.ipp"