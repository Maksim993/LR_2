#include <iostream>
#include "Eleven.h"

void demonstrateOperations() {
    std::cout << "=== Демонстрация работы с одиннадцатеричными числами ===" << std::endl;
    
    try {
        // Создание чисел только через строки - это самый надежный способ
        Eleven num1("146");     // 146 в 11-ричной = 1*121 + 4*11 + 6 = 171 в десятичной
        Eleven num2("123");     // 123 в 11-ричной = 1*121 + 2*11 + 3 = 146 в десятичной
        Eleven num3("555");     // 555 в 11-ричной
        
        std::cout << "num1: " << num1.toString() << " (в 11-ричной системе)" << std::endl;
        std::cout << "num2: " << num2.toString() << " (в 11-ричной системе)" << std::endl;
        std::cout << "num3: " << num3.toString() << " (в 11-ричной системе)" << std::endl;
        
        // Сравнения
        std::cout << "\n=== Сравнения ===" << std::endl;
        std::cout << "num1 == num2: " << (num1.isEqual(num2) ? "true" : "false") << std::endl;
        std::cout << "num1 > num2: " << (num1.isGreater(num2) ? "true" : "false") << std::endl;
        std::cout << "num1 < num2: " << (num1.isLess(num2) ? "true" : "false") << std::endl;
        
        // Арифметика
        std::cout << "\n=== Арифметика ===" << std::endl;
        Eleven sum = num1.add(num2);
        std::cout << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << std::endl;
        
        // Успешное вычитание (num1 > num2)
        Eleven diff1 = num1.subtract(num2);
        std::cout << num1.toString() << " - " << num2.toString() << " = " << diff1.toString() << std::endl;
        
        // Пытаемся вычесть большее из меньшего (должна быть ошибка)
        try {
            Eleven diff2 = num2.subtract(num1);
            std::cout << num2.toString() << " - " << num1.toString() << " = " << diff2.toString() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка вычитания (" << num2.toString() << " - " << num1.toString() << "): " << e.what() << std::endl;
            std::cout << "  Это ожидаемо, так как " << num2.toString() << " < " << num1.toString() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка при создании чисел: " << e.what() << std::endl;
        return;
    }
}

void simpleExamples() {
    std::cout << "\n=== Простые примеры ===" << std::endl;
    
    try {
        // Простые примеры сложения
        Eleven a("12");    // 1*11 + 2 = 13 в десятичной
        Eleven b("3");     // 3 в десятичной
        Eleven c = a.add(b); // 13 + 3 = 16 = "15" в 11-ричной (1*11 + 5 = 16)
        
        std::cout << a.toString() << " + " << b.toString() << " = " << c.toString() << std::endl;
        
        // Пример с цифрой A (10)
        Eleven x("A");     // 10 в десятичной
        Eleven y("1");     // 1 в десятичной
        Eleven z = x.add(y); // 10 + 1 = 11 = "10" в 11-ричной (1*11 + 0 = 11)
        std::cout << "A + 1 = " << z.toString() << std::endl;
        std::cout << "  (10 + 1 = 11 в десятичной системе)" << std::endl;
        
        // Пример вычитания
        Eleven p("15");    // 1*11 + 5 = 16 в десятичной
        Eleven q("3");     // 3 в десятичной
        Eleven r = p.subtract(q); // 16 - 3 = 13 = "12" в 11-ричной (1*11 + 2 = 13)
        std::cout << p.toString() << " - " << q.toString() << " = " << r.toString() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void comparisonExamples() {
    std::cout << "\n=== Примеры сравнения ===" << std::endl;
    
    try {
        Eleven num1("A");   // 10 в десятичной
        Eleven num2("10");  // 11 в десятичной (1*11 + 0 = 11)
        
        std::cout << "A = " << num1.toString() << " (10 в десятичной)" << std::endl;
        std::cout << "10 = " << num2.toString() << " (11 в десятичной)" << std::endl;
        std::cout << "A < 10: " << (num1.isLess(num2) ? "true" : "false") << std::endl;
        std::cout << "A > 10: " << (num1.isGreater(num2) ? "true" : "false") << std::endl;
        std::cout << "A == 10: " << (num1.isEqual(num2) ? "true" : "false") << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Лабораторная работа №2: Класс для работы с 11-ричными числами" << std::endl;
    std::cout << "=============================================================" << std::endl;
    
    demonstrateOperations();
    simpleExamples();
    comparisonExamples();
    
    std::cout << "\n=============================================================" << std::endl;
    std::cout << "Демонстрация завершена успешно!" << std::endl;
    
    return 0;
}