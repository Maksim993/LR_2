#include <gtest/gtest.h>
#include "Eleven.h"

// Тест конструктора по умолчанию
TEST(ElevenTest, DefaultConstructor) {
    Eleven num;
    EXPECT_EQ(num.toString(), "0");
}

// Тест конструктора из строки
TEST(ElevenTest, StringConstructor) {
    Eleven num("1A3"); // 1A3 в 11-ричной
    EXPECT_EQ(num.toString(), "1A3");
}

// Тест конструктора из списка
TEST(ElevenTest, InitializerListConstructor) {
    // Используем числа вместо символов
    Eleven num({1, 10, 3}); // 1A3 в 11-ричной (1, 10, 3 вместо '1', 'A', '3')
    EXPECT_EQ(num.toString(), "1A3");
}

// Тест конструктора с размером
TEST(ElevenTest, SizeConstructor) {
    Eleven num(3, 5); // 555
    EXPECT_EQ(num.toString(), "555");
}

// Тест копирования
TEST(ElevenTest, CopyConstructor) {
    Eleven num1("123");
    Eleven num2(num1);
    EXPECT_EQ(num2.toString(), "123");
}

// Тест сравнения на равенство
TEST(ElevenTest, Equality) {
    Eleven num1("123");
    Eleven num2("123");
    Eleven num3("124");
    
    EXPECT_TRUE(num1.isEqual(num2));
    EXPECT_FALSE(num1.isEqual(num3));
}

// Тест сравнения (больше/меньше)
TEST(ElevenTest, Comparison) {
    Eleven num1("123");
    Eleven num2("124");
    Eleven num3("122");
    
    EXPECT_TRUE(num2.isGreater(num1)); // 124 > 123
    EXPECT_TRUE(num3.isLess(num1));    // 122 < 123
}

// Тест сложения
TEST(ElevenTest, Addition) {
    Eleven num1("12");  // 1*11 + 2 = 13 в десятичной
    Eleven num2("1");   // 1
    Eleven result = num1.add(num2); // 13 + 1 = 14 = "13" в 11-ричной
    EXPECT_EQ(result.toString(), "13");
}

// Тест вычитания
TEST(ElevenTest, Subtraction) {
    Eleven num1("13");  // 1*11 + 3 = 14
    Eleven num2("1");   // 1
    Eleven result = num1.subtract(num2); // 14 - 1 = 13 = "12" в 11-ричной
    EXPECT_EQ(result.toString(), "12");
}

// Тест ошибки вычитания (вычитание большего из меньшего)
TEST(ElevenTest, SubtractionError) {
    Eleven num1("1");
    Eleven num2("2");
    
    EXPECT_THROW(num1.subtract(num2), std::invalid_argument);
}

// Тест удаления ведущих нулей
TEST(ElevenTest, LeadingZeros) {
    Eleven num("000123");
    EXPECT_EQ(num.toString(), "123");
}

// Тест сложения с цифрой A (10)
TEST(ElevenTest, AdditionWithA) {
    Eleven num1("A");   // 10 в десятичной
    Eleven num2("1");   // 1 в десятичной
    Eleven result = num1.add(num2); // 10 + 1 = 11 = "10" в 11-ричной
    EXPECT_EQ(result.toString(), "10");
}

// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}