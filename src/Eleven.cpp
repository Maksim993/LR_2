#include "Eleven.h"
#include <stdexcept>
#include <algorithm>

// Конструктор по умолчанию - создает число 0
Eleven::Eleven() : size(1) {
    digits = new unsigned char[1];
    digits[0] = 0;
}

// Конструктор с размером и значением
Eleven::Eleven(const size_t& n, unsigned char t) : size(n) {
    if (n == 0) throw std::invalid_argument("Size cannot be zero");
    if (t > 10) throw std::invalid_argument("Digit must be between 0 and 10");
    
    digits = new unsigned char[n];
    for (size_t i = 0; i < n; ++i) {
        digits[i] = t;
    }
    removeLeadingZeros();
}

// Конструктор из списка инициализации - ИСПРАВЛЕННЫЙ (правильный порядок)
Eleven::Eleven(const std::initializer_list<unsigned char>& t) {
    size = t.size();
    if (size == 0) throw std::invalid_argument("Initializer list cannot be empty");
    
    digits = new unsigned char[size];
    
    // Записываем цифры в обратном порядке (младшая цифра в начале)
    size_t i = 0;
    for (auto it = t.end() - 1; it >= t.begin(); --it) {
        unsigned char digit = *it;
        if (digit > 10) {
            delete[] digits;
            throw std::invalid_argument("Digit in list must be between 0 and 10");
        }
        digits[i++] = digit;
        if (i >= size) break; // Защита от переполнения
    }
    removeLeadingZeros();
}

// Конструктор из строки
Eleven::Eleven(const std::string& t) {
    if (t.empty()) throw std::invalid_argument("String cannot be empty");
    
    size = t.length();
    digits = new unsigned char[size];
    
    for (size_t i = 0; i < size; ++i) {
        char c = t[i];
        unsigned char digit;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c == 'A' || c == 'a') {
            digit = 10;
        } else {
            delete[] digits;
            throw std::invalid_argument("Invalid character in string. Use 0-9 and A");
        }
        
        // Сохраняем в обратном порядке: младшая цифра в начале
        digits[size - 1 - i] = digit;
    }
    removeLeadingZeros();
}

// Конструктор копирования
Eleven::Eleven(const Eleven& other) : size(other.size) {
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

// Конструктор перемещения
Eleven::Eleven(Eleven&& other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

// Деструктор
Eleven::~Eleven() noexcept {
    delete[] digits;
}

// Удаление ведущих нулей
void Eleven::removeLeadingZeros() {
    size_t newSize = size;
    while (newSize > 1 && digits[newSize - 1] == 0) {
        --newSize;
    }
    
    if (newSize != size) { //перевыделяем память без вед нулей
        unsigned char* newDigits = new unsigned char[newSize];
        for (size_t i = 0; i < newSize; ++i) {
            newDigits[i] = digits[i];
        }
        delete[] digits;
        digits = newDigits;
        size = newSize;
    }
}

bool Eleven::isValidDigit(unsigned char digit) const {
    return digit <= 10;
}

// Получение размера числа
size_t Eleven::getSize() const {
    return size;
}

// Получение массива цифр
unsigned char* Eleven::getDigits() const {
    unsigned char* copy = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) copy[i] = digits[i];
    return copy;
}

bool Eleven::isEqual(const Eleven& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Eleven::isGreater(const Eleven& other) const {
    if (size > other.size) return true; // Число с большим количеством цифр больше
    if (size < other.size) return false;
    
     // Сравниваем по цифрам с старшего разряда
    for (int i = size - 1; i >= 0; --i) {
        if (digits[i] > other.digits[i]) return true;
        if (digits[i] < other.digits[i]) return false;
    }
    return false; // Равны
}

bool Eleven::isLess(const Eleven& other) const {
    return !isEqual(other) && !isGreater(other);
}

Eleven Eleven::add(const Eleven& other) const {
    size_t maxSize = std::max(size, other.size) + 1; // +1 для возможного переноса
    std::vector<unsigned char> result(maxSize, 0);
    
    unsigned char carry = 0; // Перенос
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char sum = carry;
        if (i < size) sum += digits[i];
        if (i < other.size) sum += other.digits[i];
        result[i] = sum % 11;
        carry = sum / 11;
    }
    
    // Преобразуем результат в строку
    std::string resultStr;
    for (int i = result.size() - 1; i >= 0; --i) {
        if (result[i] < 10) {
            resultStr += '0' + result[i];
        } else {
            resultStr += 'A';
        }
    }
    
    // Удаляем ведущие нули
    size_t start = resultStr.find_first_not_of('0');
    if (start == std::string::npos) {
        return Eleven("0");
    }
    
    return Eleven(resultStr.substr(start));
}

Eleven Eleven::subtract(const Eleven& other) const {
    if (isLess(other)) throw std::invalid_argument("Cannot subtract larger number from smaller");
    std::vector<unsigned char> result(size, 0);
    int borrow = 0;
    for (size_t i = 0; i < size; ++i) {
        int diff = digits[i] - borrow;
        if (i < other.size) diff -= other.digits[i];
        if (diff < 0) {
            diff += 11; // Занимаем из старшего разряда
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = diff;
    }
    // Преобразуем результат в строку
    std::string resultStr;
    for (int i = result.size() - 1; i >= 0; --i) {
        if (result[i] < 10) {
            resultStr += '0' + result[i];
        } else {
            resultStr += 'A';
        }
    }
    // Удаляем ведущие нули
    size_t start = resultStr.find_first_not_of('0');
    if (start == std::string::npos) {
        return Eleven("0");
    }
    
    return Eleven(resultStr.substr(start));
}

// Преобразование в строку
std::string Eleven::toString() const {
    std::string result;
    for (int i = size - 1; i >= 0; --i) {
        if (digits[i] < 10) {
            result += '0' + digits[i];
        } else {
            result += 'A';
        }
    }
    return result;
}

// Оператор присваивания копированием
Eleven& Eleven::operator=(const Eleven& other) {
    if (this != &other) {
        delete[] digits; // Освобождаем старую память
        size = other.size;
        digits = new unsigned char[size]; // Выделяем новую
        for (size_t i = 0; i < size; ++i) {
            digits[i] = other.digits[i];  // Копируем цифры
        }
    }
    return *this;
}
// Оператор присваивания 
Eleven& Eleven::operator=(Eleven&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;// Перехватываем указатель
        size = other.size;
        other.digits = nullptr;// Обнуляем указатель исходного объекта
        other.size = 0;
    }
    return *this;
}