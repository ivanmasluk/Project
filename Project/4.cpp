#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <locale.h>
#include <windows.h>

#define MAX_TEXT   1024
#define MAX_WORDS  50
#define MAX_WORD   16
#define MAX_SUBSTR 16

// Функции для работы с русскими буквами в CP1251
bool isRussianLetter(unsigned char ch) {
    return (ch >= 192 && ch <= 255);
}

bool isLowerRussian(unsigned char ch) {
    return (ch >= 224 && ch <= 255);
}

unsigned char toLowerRussian(unsigned char ch) {
    if (ch >= 192 && ch <= 223) return ch + 32; // А-Я -> а-я
    return ch;
}

unsigned char toUpperRussian(unsigned char ch) {
    if (ch >= 224 && ch <= 255) return ch - 32; // а-я -> А-Я
    return ch;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void readInput(char text[]) {
    int choice;
    std::cout << "Выберите ввод (1 - клавиатура, 2 - файл): ";
    std::cin >> choice;
    clearBuffer();

    if (choice == 1) {
        std::cout << "Введите текст (заканчивается точкой):\n";
        std::cin.getline(text, MAX_TEXT);
    }
    else {
        char filename[256];
        std::cout << "Введите имя файла: ";
        std::cin.getline(filename, 256);

        FILE* file = NULL;
        fopen_s(&file, filename, "r");
        if (file) {
            fgets(text, MAX_TEXT, file);
            fclose(file);
        }
        else {
            text[0] = '.';
            text[1] = '\0';
        }
    }
}

void normalizeText(char text[]) {
    int i = 0, j = 0;
    int inWord = 0;
    char result[MAX_TEXT];
    bool lastWasPunct = false;

    while (text[i]) {
        unsigned char ch = (unsigned char)text[i];

        if (ch == '.') {
            if (inWord) result[j++] = text[i];
            break;
        }

        // Проверка на знаки препинания
        if (ch == ',' || ch == ';' || ch == ':' || ch == '!' || ch == '?' ||
            ch == '(' || ch == ')' || ch == '-' || ch == '"') {
            if (inWord && !lastWasPunct) {
                result[j++] = text[i];
                lastWasPunct = true;
            }
            i++;
            continue;
        }

        lastWasPunct = false;

        if (ch == ' ' || ch == '\t') {
            if (inWord) {
                result[j++] = ' ';
                inWord = 0;
            }
        }
        else if (isRussianLetter(ch) || (ch >= '0' && ch <= '9')) {
            if (!inWord) {
                // Первая буква слова - прописная
                result[j++] = (char)toUpperRussian(ch);
                inWord = 1;
            }
            else {
                // Остальные буквы - строчные
                result[j++] = (char)toLowerRussian(ch);
            }
        }
        else {
            // Пропускаем другие символы
        }
        i++;
    }
    result[j] = '\0';
    strcpy_s(text, MAX_TEXT, result);
}

int splitWords(char text[], char words[][MAX_WORD]) {
    int count = 0;
    char* context = NULL;
    char* token = strtok_s(text, " ", &context);

    while (token && count < MAX_WORDS) {
        strcpy_s(words[count], MAX_WORD, token);

        // Убираем точку в конце последнего слова
        char* dot = strchr(words[count], '.');
        if (dot != NULL) {
            *dot = '\0';
            count++;
            break;
        }

        count++;
        token = strtok_s(NULL, " ", &context);
    }
    return count;
}

void task1ReverseWords(char words[][MAX_WORD], int count) {
    std::cout << "\nЗадание 1 - Слова в обратном порядке:\n";
    for (int i = count - 1; i >= 0; i--) {
        std::cout << words[i];
        if (i > 0) std::cout << " ";
    }
    std::cout << ".\n";
}

void task2WordLengths(char words[][MAX_WORD], int count) {
    std::cout << "\nЗадание 2 - Количество символов в словах:\n";
    for (int i = 0; i < count; i++) {
        int len = (int)strlen(words[i]);
        std::cout << "Слово '" << words[i] << "': " << len << " символов\n";
    }
}

int linearSearch(const char text[], const char pattern[]) {
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    int count = 0;

    if (m == 0 || n < m) return 0;

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        for (; j < m; j++) {
            if (text[i + j] != pattern[j]) break;
        }
        if (j == m) count++;
    }
    return count;
}

int boyerMooreSearch(const char text[], const char pattern[]) {
    int n = (int)strlen(text);
    int m = (int)strlen(pattern);
    if (m == 0 || n < m) return 0;

    int skip[256];
    for (int i = 0; i < 256; ++i) skip[i] = m;
    for (int i = 0; i < m - 1; i++) {
        skip[(unsigned char)pattern[i]] = m - 1 - i;
    }

    int count = 0;
    int i = 0;

    while (i <= n - m) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            count++;
            i += m;
        }
        else {
            int s = skip[(unsigned char)text[i + j]];
            int shift = j + 1;
            i += (s > shift) ? s : shift;
        }
    }
    return count;
}

int main() {
    // Настройка кодировки для Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    char text[MAX_TEXT];
    char words[MAX_WORDS][MAX_WORD];

    std::cout << "=== ПРОГРАММА ОБРАБОТКИ ТЕКСТА ===\n";

    readInput(text);

    std::cout << "\nИсходный текст: " << text << "\n";

    normalizeText(text);
    std::cout << "Обработанный текст: " << text << "\n";

    int wordCount = splitWords(text, words);
    std::cout << "Найдено слов: " << wordCount << "\n";

    task1ReverseWords(words, wordCount);
    task2WordLengths(words, wordCount);

    std::cout << "\n=== ПОИСК ПОДСТРОК ===\n";
    std::cout << "Введите подстроку для поиска: ";
    char pattern[MAX_SUBSTR];
    std::cin.getline(pattern, MAX_SUBSTR);

    char fullText[MAX_TEXT] = { 0 };
    for (int i = 0; i < wordCount; i++) {
        strcat_s(fullText, MAX_TEXT, words[i]);
        if (i < wordCount - 1) strcat_s(fullText, MAX_TEXT, " ");
    }

    int linearCount = linearSearch(fullText, pattern);
    int boyerCount = boyerMooreSearch(fullText, pattern);

    std::cout << "Линейный поиск: найдено вхождений: " << linearCount << "\n";
    std::cout << "Алгоритм Бойера-Мура: найдено вхождений: " << boyerCount << "\n";

    std::cout << "\nПрограмма завершена.\n";
    return 0;
}