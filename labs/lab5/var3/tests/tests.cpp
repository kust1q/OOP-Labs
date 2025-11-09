#include <gtest/gtest.h>
#include <memory_resource>
#include <thread>
#include <future>
#include <algorithm> 

#include "forward_list.hpp"
#include "memory_resource.hpp"

struct Person {
    std::string name;
    int age;

    Person() = default;
    Person(const std::string& n, int a) : name(n), age(a) {}

    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "{name: \"" << p.name << "\", age: " << p.age << "}";
        return os;
    }
};

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

    MemoryResource resource;
    ForwardList<int> list{&resource};
    const size_t sz = 7;
};

// === Тесты с MemoryResource ===

TEST(MemoryResourceTest, DefaultConstructor) {
    MemoryResource resource;
    ForwardList<int> list(&resource);
    ASSERT_TRUE(list.IsEmpty()) << "Default list isn't empty!";
}

TEST(MemoryResourceTest, PushFrontSimple) {
    MemoryResource resource;
    ForwardList<int> list(&resource);
    list.PushFront(2);
    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Front(), 2);
}

TEST(MemoryResourceTest, PopFrontSimple) {
    MemoryResource resource;
    ForwardList<int> list(&resource);
    list.PushFront(1);
    list.PushFront(2);
    list.PopFront();

    ASSERT_EQ(list.Size(), 1);
    ASSERT_EQ(list.Front(), 1);
}

TEST(MemoryResourceTest, PopFrontEmptyList) {
    MemoryResource resource;
    ForwardList<int> list(&resource);
    EXPECT_THROW({
        list.PopFront();
    }, ListIsEmptyException);
}

TEST(MemoryResourceTest, ConstructorSizeDefaultValues) {
    MemoryResource resource;
    ForwardList<std::string> list(5, &resource);
    ASSERT_EQ(list.Size(), 5);
    while (list.Size()) {
        ASSERT_TRUE(list.Front().empty());
        list.PopFront();
    }
}

TEST(MemoryResourceTest, ConstructorWithInitList) {
    MemoryResource resource;
    ForwardList<int> list({1, 2, 3, 4, 5, 6, 7, 8}, &resource);
    ASSERT_EQ(list.Size(), 8);
    int iter = 1;
    while (!list.IsEmpty()) {
        ASSERT_EQ(list.Front(), iter++);
        list.PopFront();
    }
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
    MemoryResource resource;
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

TEST(MemoryResourceTest, WithComplexType) {
    MemoryResource resource;
    ForwardList<Person> list(&resource);

    list.PushFront(Person("Alice", 30));
    list.PushFront(Person("Bob", 25));

    ASSERT_EQ(list.Size(), 2);

    auto it = list.Begin();
    EXPECT_EQ(it->name, "Bob");
    EXPECT_EQ(it->age, 25);
    ++it;
    EXPECT_EQ(it->name, "Alice");
    EXPECT_EQ(it->age, 30);
    ++it;
    EXPECT_EQ(it, list.End());
}

TEST(MemoryResourceTest, CopyWithComplexType) {
    MemoryResource resource;
    ForwardList<Person> original(&resource);
    original.PushFront(Person("item1", 10));
    original.PushFront(Person("item2", 20));

    ForwardList<Person> copy(original);

    ASSERT_EQ(copy.Size(), 2);

    auto it = copy.Begin();
    EXPECT_EQ(it->name, "item2");
    EXPECT_EQ(it->age, 20);
    ++it;
    EXPECT_EQ(it->name, "item1");
    EXPECT_EQ(it->age, 10);
    ++it;
    EXPECT_EQ(it, copy.End());
}

TEST(MemoryResourceTest, FindWithPerson) {
    MemoryResource resource;
    ForwardList<Person> list(&resource);
    list.PushFront(Person("Alice", 30));
    list.PushFront(Person("Bob", 25));

    auto it = list.Find(Person("Bob", 25));
    EXPECT_NE(it, list.End());
    EXPECT_EQ(it->name, "Bob");
    EXPECT_EQ(it->age, 25);

    auto not_found = list.Find(Person("Charlie", 40));
    EXPECT_EQ(not_found, list.End());
}

// === Тесты на move семантику ===

TEST(MemoryResourceTest, MoveConstructor) {
    MemoryResource resource;
    ForwardList<int> original(&resource);
    original.PushFront(1);
    original.PushFront(2);
    original.PushFront(3);
    
    size_t original_size = original.Size();
    int original_front = original.Front();
    
    ForwardList<int> moved = std::move(original);
    
    // Проверяем, что перемещенный список имеет правильные значения
    ASSERT_EQ(moved.Size(), original_size);
    ASSERT_EQ(moved.Front(), original_front);
    
    // Проверяем, что исходный список пуст
    ASSERT_TRUE(original.IsEmpty());
    ASSERT_EQ(original.Size(), 0);
}

TEST(MemoryResourceTest, MoveAssignment) {
    MemoryResource resource;
    ForwardList<int> original(&resource);
    original.PushFront(1);
    original.PushFront(2);
    original.PushFront(3);
    
    ForwardList<int> target(&resource);
    target.PushFront(10);
    target.PushFront(20);
    
    size_t original_size = original.Size();
    int original_front = original.Front();
    
    target = std::move(original);
    
    // Проверяем, что целевой список получил значения из исходного
    ASSERT_EQ(target.Size(), original_size);
    ASSERT_EQ(target.Front(), original_front);
    
    // Проверяем, что исходный список пуст
    ASSERT_TRUE(original.IsEmpty());
    ASSERT_EQ(original.Size(), 0);
}

TEST(MemoryResourceTest, MoveSelfAssignment) {
    MemoryResource resource;
    ForwardList<int> list(&resource);
    list.PushFront(1);
    list.PushFront(2);
    
    size_t original_size = list.Size();
    int original_front = list.Front();
    
    // Попытка перемещения самого в себя
    list = std::move(list);
    
    // Список должен остаться в том же состоянии
    ASSERT_EQ(list.Size(), original_size);
    ASSERT_EQ(list.Front(), original_front);
}

TEST_F(ListTest, MoveConstructorPreservesContent) {
    size_t original_size = list.Size();
    int original_front = list.Front();
    
    ForwardList<int> moved = std::move(list);
    
    ASSERT_EQ(moved.Size(), original_size);
    ASSERT_EQ(moved.Front(), original_front);
    
    // Проверяем, что все элементы остались на месте
    int expected_values[] = {7, 6, 5, 4, 3, 2, 1};
    int i = 0;
    for (auto it = moved.Begin(); it != moved.End(); ++it) {
        ASSERT_EQ(*it, expected_values[i++]);
    }
    
    ASSERT_TRUE(list.IsEmpty());
}

TEST_F(ListTest, MoveAssignmentPreservesContent) {
    MemoryResource other_resource;
    ForwardList<int> other(&other_resource);
    other.PushFront(100);
    other.PushFront(200);
    
    size_t original_size = list.Size();
    int original_front = list.Front();
    
    other = std::move(list);
    
    ASSERT_EQ(other.Size(), original_size);
    ASSERT_EQ(other.Front(), original_front);
    
    // Проверяем, что все элементы остались на месте
    int expected_values[] = {7, 6, 5, 4, 3, 2, 1};
    int i = 0;
    for (auto it = other.Begin(); it != other.End(); ++it) {
        ASSERT_EQ(*it, expected_values[i++]);
    }
    
    ASSERT_TRUE(list.IsEmpty());
}

TEST(MemoryResourceTest, MoveWithComplexType) {
    MemoryResource resource;
    ForwardList<Person> original(&resource);
    original.PushFront(Person("Alice", 30));
    original.PushFront(Person("Bob", 25));
    
    ForwardList<Person> moved = std::move(original);
    
    ASSERT_EQ(moved.Size(), 2);
    
    auto it = moved.Begin();
    EXPECT_EQ(it->name, "Bob");
    EXPECT_EQ(it->age, 25);
    ++it;
    EXPECT_EQ(it->name, "Alice");
    EXPECT_EQ(it->age, 30);
    ++it;
    EXPECT_EQ(it, moved.End());
    
    ASSERT_TRUE(original.IsEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}