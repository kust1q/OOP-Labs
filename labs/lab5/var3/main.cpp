#include <iostream>

#include "forward_list.hpp"

int main() {
    ForwardList<int> list;
    list.PushFront(1);
    list.PushFront(2);
    list.PushFront(3);
    list.PushFront(4);
    for (auto it = list.Begin(); it != list.End(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}