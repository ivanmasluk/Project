#include <iostream>
#include <clocale>

using namespace std;

// Функция для вывода двоичного представления с разделением на байты
void printBinary(unsigned int number, int totalBits) {
    for (int i = 0; i < totalBits; i++) {
        int shift = totalBits - 1 - i;
        unsigned int mask = 1u << shift;
        int digit = (number & mask) ? 1 : 0;

        cout << digit;

        // Разделение на байты
        if ((i + 1) % 8 == 0 && i != totalBits - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

// Задание 1: Размеры типов данных
void task1() {
    cout << "=== Размеры типов данных (в байтах) ===" << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "short int: " << sizeof(short int) << endl;
    cout << "long int: " << sizeof(long int) << endl;
    cout << "long long int: " << sizeof(long long int) << endl;
    cout << "float: " << sizeof(float) << endl;
    cout << "double: " << sizeof(double) << endl;
    cout << "long double: " << sizeof(long double) << endl;
    cout << "char: " << sizeof(char) << endl;
    cout << "bool: " << sizeof(bool) << endl;
    cout << endl;
}

// Задание 2: Двоичное представление int
void task2() {
    cout << "=== Двоичное представление целого числа (int) ===" << endl;
    cout << "Введите целое число: ";

    union {
        int int_number;
        unsigned int uint_number;
    } u;

    cin >> u.int_number;

    cout << "Двоичное представление (" << sizeof(int) * 8 << " бит):" << endl;

    printBinary(u.uint_number, sizeof(int) * 8);
    cout << endl;
}

// Задание 3: Двоичное представление float
void task3() {
    cout << "=== Двоичное представление числа float ===" << endl;
    cout << "Введите число с плавающей точкой: ";

    union {
        float float_number;
        unsigned int uint_number;
    } u;

    cin >> u.float_number;

    cout << "Двоичное представление (32 бита):" << endl;

    printBinary(u.uint_number, sizeof(float) * 8);
    cout << endl;
}

// Задание 4: Двоичное представление double
void task4() {
    cout << "=== Двоичное представление числа double ===" << endl;
    cout << "Введите число с плавающей точкой (double): ";

    union {
        double double_number;
        unsigned long long ull_number;
    } u;

    cin >> u.double_number;

    cout << "Двоичное представление (64 бита):" << endl;

    // Выводим по 8 бит с разделением
    unsigned long long mask = 1ull << 63;
    for (int i = 0; i < 64; i++) {
        cout << ((u.ull_number & mask) ? 1 : 0);
        mask >>= 1;

        if ((i + 1) % 8 == 0 && i != 63) {
            cout << " ";
        }
    }
    cout << endl << endl;
}

// Задание 5: Изменение бита
void task5() {
    cout << "=== Изменение бита в числе ===" << endl;
    cout << "Выберите тип данных:" << endl;
    cout << "1. int (32 бита)" << endl;
    cout << "2. float (32 бита)" << endl;
    cout << "3. double (64 бита)" << endl;
    cout << "4. char (8 бит)" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: { // int
        union {
            int int_number;
            unsigned int uint_number;
        } u;

        cout << "Введите целое число: ";
        cin >> u.int_number;

        cout << "Текущее двоичное представление:" << endl;
        printBinary(u.uint_number, sizeof(int) * 8);

        cout << "Введите номер бита для изменения (0-" << sizeof(int) * 8 - 1 << "): ";
        int bit_number;
        cin >> bit_number;

        if (bit_number >= 0 && bit_number < sizeof(int) * 8) {
            unsigned int mask = 1u << bit_number;
            u.uint_number ^= mask;

            cout << "Измененное число (десятичное): " << u.int_number << endl;
            cout << "Новое двоичное представление:" << endl;
            printBinary(u.uint_number, sizeof(int) * 8);
        }
        else {
            cout << "Неверный номер бита!" << endl;
        }
        break;
    }

    case 2: { // float
        union {
            float float_number;
            unsigned int uint_number;
        } u;

        cout << "Введите число с плавающей точкой: ";
        cin >> u.float_number;

        cout << "Текущее двоичное представление:" << endl;
        printBinary(u.uint_number, sizeof(float) * 8);

        cout << "Введите номер бита для изменения (0-" << sizeof(float) * 8 - 1 << "): ";
        int bit_number;
        cin >> bit_number;

        if (bit_number >= 0 && bit_number < sizeof(float) * 8) {
            unsigned int mask = 1u << bit_number;
            u.uint_number ^= mask;

            cout << "Измененное число (десятичное): " << u.float_number << endl;
            cout << "Новое двоичное представление:" << endl;
            printBinary(u.uint_number, sizeof(float) * 8);
        }
        else {
            cout << "Неверный номер бита!" << endl;
        }
        break;
    }

    case 3: { // double
        union {
            double double_number;
            unsigned long long ull_number;
        } u;

        cout << "Введите число double: ";
        cin >> u.double_number;

        cout << "Текущее двоичное представление:" << endl;
        unsigned long long mask = 1ull << 63;
        for (int i = 0; i < 64; i++) {
            cout << ((u.ull_number & mask) ? 1 : 0);
            mask >>= 1;
            if ((i + 1) % 8 == 0 && i != 63) cout << " ";
        }
        cout << endl;

        cout << "Введите номер бита для изменения (0-" << sizeof(double) * 8 - 1 << "): ";
        int bit_number;
        cin >> bit_number;

        if (bit_number >= 0 && bit_number < sizeof(double) * 8) {
            unsigned long long mask = 1ull << bit_number;
            u.ull_number ^= mask;

            cout << "Измененное число (десятичное): " << u.double_number << endl;
            cout << "Новое двоичное представление:" << endl;
            mask = 1ull << 63;
            for (int i = 0; i < 64; i++) {
                cout << ((u.ull_number & mask) ? 1 : 0);
                mask >>= 1;
                if ((i + 1) % 8 == 0 && i != 63) cout << " ";
            }
            cout << endl;
        }
        else {
            cout << "Неверный номер бита!" << endl;
        }
        break;
    }

    case 4: { // char
        union {
            char char_value;
            unsigned char uchar_value;
        } u;

        cout << "Введите символ: ";
        cin >> u.char_value;

        cout << "Текущее двоичное представление:" << endl;
        unsigned char mask = 1u << 7;
        for (int i = 0; i < 8; i++) {
            cout << ((u.uchar_value & mask) ? 1 : 0);
            mask >>= 1;
        }
        cout << endl;

        cout << "Введите номер бита для изменения (0-7): ";
        int bit_number;
        cin >> bit_number;

        if (bit_number >= 0 && bit_number < 8) {
            unsigned char mask = 1u << bit_number;
            u.uchar_value ^= mask;

            cout << "Измененный символ: ";
            cout << "'" << u.char_value << "' (код: " << (int)u.uchar_value << ")" << endl;

            cout << "Новое двоичное представление:" << endl;
            mask = 1u << 7;
            for (int i = 0; i < 8; i++) {
                cout << ((u.uchar_value & mask) ? 1 : 0);
                mask >>= 1;
            }
            cout << endl;
        }
        else {
            cout << "Неверный номер бита!" << endl;
        }
        break;
    }

    default:
        cout << "Неверный выбор!" << endl;
    }
    cout << endl;
}

int main() {
    setlocale(0, "rus");

    int choice;

    do {
        cout << "================================" << endl;
        cout << "ПРАКТИЧЕСКАЯ РАБОТА №1" << endl;
        cout << "ТИПЫ ДАННЫХ И ИХ ПРЕДСТАВЛЕНИЕ В ПАМЯТИ" << endl;
        cout << "================================" << endl;
        cout << "1. Размеры типов данных" << endl;
        cout << "2. Двоичное представление int" << endl;
        cout << "3. Двоичное представление float" << endl;
        cout << "4. Двоичное представление double" << endl;
        cout << "5. Изменение бита в числе" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите задание: ";

        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 0: cout << "Выход из программы." << endl; break;
        default: cout << "Неверный выбор! Попробуйте снова." << endl;
        }

    } while (choice != 0);

    return 0;
}