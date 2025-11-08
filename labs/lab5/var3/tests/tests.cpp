#include <gtest/gtest.h>
#include <memory_resource>
#include <thread>
#include <future>
#include <algorithm> 

#include "forward_list.hpp"
#include "memory_resource.hpp"

class ListTest : public testing::Test {
protected:
    void SetUp() override {
        list.PushFront(1);
        list.PushFront(2);
        list.PushFront(3);
        list.PushFront(4);
        list.PushFront(5);
        list.PushFront(6);
        list.PushFront(7);
        ASSERT_EQ(list.Size(), sz);
    }

    MemoryResource resource{4096, ForwardList<int>::node_size()};
    ForwardList<int> list{&resource};
    const size_t sz = 7;
};

// === Тесты с MemoryResource ===

TEST(MemoryResourceTest, DefaultConstructor) {
    MemoryResource resource(4096, ForwardList<int>::node_size());
    ForwardList<int> list(&resource);
    ASSERT_TRUE(list.IsEmpty()) << "Default list isn't empty!";
}

TEST(MemoryResourceTest, PushFrontSimple) {
    MemoryResource resource(4096, ForwardList<int>::node_size());
    ForwardList<int> list(&resource);
    list.PushFront(2);
    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Front(), 2);
}

TEST(MemoryResourceTest, PopFrontSimple) {
    MemoryResource resource(4096, ForwardList<int>::node_size());
    ForwardList<int> list(&resource);
    list.PushFront(1);
    list.PushFront(2);
    list.PopFront();

    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Front(), 1);
}

TEST(MemoryResourceTest, PopFrontEmptyList) {
    MemoryResource resource(4096, ForwardList<int>::node_size());
    ForwardList<int> list(&resource);
    EXPECT_THROW({
        list.PopFront();
    }, ListIsEmptyException);
}

TEST(MemoryResourceTest, ConstructorSizeDefaultValues) {
    MemoryResource resource(4096, ForwardList<std::string>::node_size());
    ForwardList<std::string> list(5, &resource);
    ASSERT_EQ(list.Size(), 5);
    while (list.Size()) {
        ASSERT_TRUE(list.Front().empty());
        list.PopFront();
    }
}

TEST(MemoryResourceTest, ConstructorWithInitList) {
    MemoryResource resource(4096, ForwardList<int>::node_size());
    ForwardList<int> list({1, 2, 3, 4, 5, 6, 7, 8}, &resource);
    ASSERT_EQ(list.Size(), 8);
    int iter = 1;
    while (!list.IsEmpty()) {
        ASSERT_EQ(list.Front(), iter++);
        list.PopFront();
    }
}

TEST(MemoryResourceTest, Swap) {
    MemoryResource resource1(4096, ForwardList<int>::node_size());
    MemoryResource resource2(4096, ForwardList<int>::node_size());

    ForwardList<int> list(&resource1);
    list.PushFront(5);

    ForwardList<int> lst(&resource2);
    lst.PushFront(15);
    lst.PushFront(14);

    size_t old_list_size = list.Size();
    size_t old_lst_size = lst.Size();

    std::swap(list, lst);

    ASSERT_EQ(lst.Size(), old_list_size);
    ASSERT_EQ(list.Size(), old_lst_size);

    ASSERT_EQ(lst.Front(), 5);
    ASSERT_EQ(list.Front(), 14);
    list.PopFront();
    ASSERT_EQ(list.Front(), 15);
}

TEST_F(ListTest, CopyConstructor) {
    ForwardList<int> lst = list;
    ASSERT_NE(&list, &lst) << "Copy constructor must do copy!\n";
    ASSERT_EQ(list.Size(), lst.Size());
    auto it1 = list.Begin();
    auto it2 = lst.Begin();
    while (it2 != lst.End()) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST_F(ListTest, CopyAssigment) {
    MemoryResource resource(4096, ForwardList<int>::node_size());
    ForwardList<int> lst(&resource);
    lst.PushFront(4);
    list = lst;
    ASSERT_NE(&list, &lst) << "Copy assignment must do copy!\n";
    ASSERT_EQ(list.Size(), lst.Size());
    auto it1 = list.Begin();
    auto it2 = lst.Begin();
    while (it2 != lst.End()) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST_F(ListTest, SelfAssignment) {
    std::thread thread([&](){
        list = list;
    });
    auto future = std::async(std::launch::async, &std::thread::join, &thread);
    ASSERT_LT(
        future.wait_for(std::chrono::seconds(1)),
        std::future_status::timeout
    ) << "There is infinity loop!\n";
}

TEST_F(ListTest, RangeWithIteratorPreFix) {
    ASSERT_EQ(std::distance(list.Begin(), list.End()), sz) << 
                  "Distance between begin and end iterators isn't equal size";
    int iter = 7;
    for (auto it = list.Begin(); it != list.End(); ++it) {
        ASSERT_EQ(*it, iter--);
    }
}

TEST_F(ListTest, RangeWithIteratorPostFix) {
    ASSERT_EQ(std::distance(list.Begin(), list.End()), sz) << 
                  "Distance between begin and end iterators isn't equal size";
    int iter = 7;
    for (auto it = list.Begin(); it != list.End(); it++) {
        ASSERT_EQ(*it, iter--);
    }
}

TEST_F(ListTest, FindFirst) {
    auto it = list.Begin();
    ASSERT_EQ(it, list.Find(7));
}

TEST_F(ListTest, FindLast) {
    auto it = list.Begin();
    std::advance(it, 6);
    ASSERT_EQ(it, list.Find(1));
}

TEST_F(ListTest, FindFail) {
    auto it = list.End();
    ASSERT_EQ(it, list.Find(999));
}

TEST_F(ListTest, FindAll) {
    auto it = list.Begin();
    for (int i = 7; i >= 1; --i) {
        ASSERT_EQ(it++, list.Find(i));
    }
}

TEST_F(ListTest, EraseAfterBegin) {
    int next_value = *(++list.Begin());
    list.EraseAfter(list.Begin());
    ASSERT_EQ(list.Size(), sz - 1);
    auto it = list.Begin();
    ++it;
    ASSERT_NE(*it, next_value);
}

TEST_F(ListTest, EraseMedium) {
    auto it = list.Begin();
    std::advance(it, sz / 2);
    list.EraseAfter(it);
    ASSERT_EQ(list.Size(), sz - 1);
    for (auto check_it = list.Begin(); check_it != list.End(); ++check_it) {
        ASSERT_NE(*check_it, 3);
    }
}

TEST_F(ListTest, InsertAfterMedium) {
    auto it = list.Begin();
    std::advance(it, sz / 2);
    list.InsertAfter(it, 4);
    ASSERT_EQ(list.Size(), sz + 1);
    std::advance(it, 1);
    ASSERT_EQ(*it, 4);
}

TEST_F(ListTest, Clear) {
    list.Clear();
    ASSERT_TRUE(list.IsEmpty());
    ASSERT_EQ(list.Size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}