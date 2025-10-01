#ifndef ELEVEN_H
#define ELEVEN_H

#include <iostream>
#include <string>
#include <vector>

class Eleven {
private:
    unsigned char* digits;  // Динамический массив цифр
    size_t size;            // Размер числа (количество цифр)

    // Вспомогательные методы
    void removeLeadingZeros(); // Удаление ведущих нулей
    bool isValidDigit(unsigned char digit) const; // Проверка корректности цифры

public:
    // Конструкторы
    Eleven();                                      // По умолчанию
    Eleven(const size_t& n, unsigned char t = 0); // Создание числа из n цифр
    Eleven(const std::initializer_list<unsigned char>& t); // Из списка инициализации
    Eleven(const std::string& t);                  // Из строки
    Eleven(const Eleven& other);                   // Копирования
    Eleven(Eleven&& other) noexcept;               // Перемещения
    
    // Деструктор
    virtual ~Eleven() noexcept;

    // Методы доступа
    size_t getSize() const;
    unsigned char* getDigits() const;

    // Операции сравнения
    bool isEqual(const Eleven& other) const;  // Равно
    bool isGreater(const Eleven& other) const; // Больше
    bool isLess(const Eleven& other) const;    // Меньше

    // Арифметические операции
    Eleven add(const Eleven& other) const;     // Сложение
    Eleven subtract(const Eleven& other) const; // Вычитание
    
    // Вывод числа
    std::string toString() const;

    // Оператор присваивания
    Eleven& operator=(const Eleven& other);
    Eleven& operator=(Eleven&& other) noexcept;
};

#endif