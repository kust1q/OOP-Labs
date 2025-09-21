#include <gtest/gtest.h>
#include "money.h"

TEST(test_01, DefaultConstructor) {
    money::Money m;
    EXPECT_EQ(m.CheckBalance(), "0k.");
}

TEST(test_02, SizeConstructor) {
    money::Money m1(3, 5);
    EXPECT_EQ(m1.CheckBalance(), "5P. 55k.");
    
    money::Money m2(1, 9);
    EXPECT_EQ(m2.CheckBalance(), "9k.");
}

TEST(test_03, InitializerListConstructor) {
    money::Money m1({1, 2, 3});
    EXPECT_EQ(m1.CheckBalance(), "1P. 23k."); 
    
    money::Money m2({0, 0, 5});
    EXPECT_EQ(m2.CheckBalance(), "5k."); 

    money::Money m3({0, 0, 1, 2, 3, 4});
    EXPECT_EQ(m3.CheckBalance(), "12P. 34k."); 
}

TEST(test_04, StringConstructor) {
    money::Money m1("123");
    EXPECT_EQ(m1.CheckBalance(), "1P. 23k.");
    
    money::Money m2("001250");
    EXPECT_EQ(m2.CheckBalance(), "12P. 50k.");
    
    EXPECT_THROW(money::Money m3("12a3"), exceptions::NotNumberExceptions);
}

TEST(test_05, CopyConstructor) {
    money::Money m1("12345");
    money::Money m2(m1);
    EXPECT_TRUE(m1.EQ(m2));
}

TEST(test_06, MoveConstructor) {
    money::Money m1("12345");
    money::Money m2(std::move(m1));
    EXPECT_EQ(m2.CheckBalance(), "123P. 45k.");
    EXPECT_EQ(m1.CheckBalance(), "0k."); 
}

TEST(test_07, AddMethod) {
    money::Money m1("123");
    money::Money m2("456");
    money::Money result = Add(m1, m2);
    EXPECT_EQ(result.CheckBalance(), "5P. 79k.");
    
    money::Money m3("999");
    money::Money m4("1");
    money::Money result2 = Add(m3,m4);
    EXPECT_EQ(result2.CheckBalance(), "10P. 00k.");
    
    money::Money m5("50");
    money::Money m6("50"); 
    money::Money result3 = Add(m5,m6);
    EXPECT_EQ(result3.CheckBalance(), "1P. 00k."); 
}

TEST(test_08, SubMethod) {
    money::Money m1("1000");
    money::Money m2("500");
    money::Money result = Sub(m1, m2);
    EXPECT_EQ(result.CheckBalance(), "5P. 00k.");
    
    money::Money m3("150");
    money::Money m4("75");
    money::Money result2 = Sub(m3,m4);
    EXPECT_EQ(result2.CheckBalance(), "75k.");

    money::Money m7("50");
    money::Money m8("100");
    EXPECT_THROW(Sub(m7, m8), exceptions::NegativeBalanceExceptions);
}

TEST(test_09, ComparisonMethods) {
    money::Money m1("10000");
    money::Money m2("9999");
    money::Money m3("10000");
    
    EXPECT_TRUE(m1.GT(m2));
    EXPECT_FALSE(m2.GT(m1));
    
    EXPECT_TRUE(m2.LT(m1));
    EXPECT_FALSE(m1.LT(m2));
    
    EXPECT_TRUE(m1.EQ(m3));
    EXPECT_FALSE(m1.EQ(m2));
}

TEST(test_10, CheckBalanceMethod) {
    money::Money m1(0, 0);
    EXPECT_EQ(m1.CheckBalance(), "0k.");
    
    money::Money m2("5");
    EXPECT_EQ(m2.CheckBalance(), "5k.");
    
    money::Money m3("50");
    EXPECT_EQ(m3.CheckBalance(), "50k.");
    
    money::Money m4("100");
    EXPECT_EQ(m4.CheckBalance(), "1P. 00k.");

    money::Money m5("1234567");
    EXPECT_EQ(m5.CheckBalance(), "12345P. 67k.");
}

TEST(MoneyTest, CopyMethod) {
    money::Money m1("12345");
    money::Money m2;
    m2.Copy(m1);
    EXPECT_TRUE(m1.EQ(m2));
    EXPECT_TRUE(&m1 != &m2);
    
    money::Money m5("100");
    money::Money m6("200");
    m5.Copy(m6);
    EXPECT_TRUE(m5.EQ(m6));
    EXPECT_FALSE(m5.EQ(money::Money("100")));
    EXPECT_TRUE(&m5 != &m6);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}