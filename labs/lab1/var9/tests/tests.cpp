#include <gtest/gtest.h>
#include "filter.h"

TEST(test_01, EmptyString) {
    EXPECT_EQ(filter::Filter(""), (std::vector<std::string>{}));
}

TEST(test_02, ZeroString) {
    EXPECT_EQ(filter::Filter("0000"), (std::vector<std::string>{}));
}

TEST(test_03, SimpleString) {
    EXPECT_EQ(filter::Filter("a111a"), (std::vector<std::string>{"111"}));
}

TEST(test_04, StringWithMoreNums) {
    EXPECT_EQ(filter::Filter("a111a222a"), (std::vector<std::string>{"111", "222"}));
}

TEST(test_05, StringWithAllNumbers) {
    EXPECT_EQ(filter::Filter("123456789"), (std::vector<std::string>{"123456789"}));
}

TEST(test_06, StringWithZerosBegin) {
    EXPECT_EQ(filter::Filter("aaa0014aaa23456789"), (std::vector<std::string>{"14", "23456789"}));
}

TEST(test_07, StringWithOnlyLetters) {
    EXPECT_EQ(filter::Filter("AAAAAAAAAAaaaaaaaaAAAAA"), (std::vector<std::string>{}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}