#ifndef ELEVEN_H
#define ELEVEN_H

#include <iostream>
#include <string>
#include <vector>

class Eleven {
private:
    unsigned char* digits;  // Массив цифр (0-10)
    size_t size;            // Количество цифр

    // Внутренние вспомогательные методы
    void removeLeadingZeros(); // Удалить нули в начале числа
    bool isValidDigit(unsigned char digit) const; // Проверить что цифра от 0 до 10

public:
    // Конструкторы
    Eleven();                                      // Пустое число (0)
    Eleven(const size_t& n, unsigned char t = 0); // Число из n одинаковых цифр
    Eleven(const std::initializer_list<unsigned char>& t); // Из списка {1,2,3}
    Eleven(const std::string& t);                  // Из строки "123"
    Eleven(const Eleven& other);                   // Копирование
    Eleven(Eleven&& other) noexcept;               // Перемещение
    
    // Деструктор
    virtual ~Eleven() noexcept;

    // Геттеры
    size_t getSize() const;
    unsigned char* getDigits() const;

    // Сравнения
    bool isEqual(const Eleven& other) const;  // ==
    bool isGreater(const Eleven& other) const; // >
    bool isLess(const Eleven& other) const;    // <

    // Арифметика
    Eleven add(const Eleven& other) const;     // +
    Eleven subtract(const Eleven& other) const; // -
    
    // Преобразование в строку для вывода
    std::string toString() const;

    // Операторы присваивания
    Eleven& operator=(const Eleven& other);
    Eleven& operator=(Eleven&& other) noexcept;
};

#endif