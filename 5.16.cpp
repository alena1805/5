#include <iostream>    // Для ввода-вывода
#include <fstream>     // Для работы с файлами
#include <cstdlib>     // Для функций rand() и srand()
#include <ctime>       // Для функции time()
#include <limits>      // Для std::numeric_limits

using namespace std; // Используем стандартное пространство имен

// Функция для записи случайных данных в файл
void gD(const string& f, int r, int n) {
    ofstream out(f); // Открываем файл для записи
    if (!out) { // Проверка успешности открытия файла
        cerr << "Ошибка открытия файла." << endl; // Вывод сообщения об ошибке
        return; // Завершаем функцию, если файл не открылся
    }

    srand(time(0)); // Инициализация генератора случайных чисел с использованием текущего времени

    // Генерация r строк по n случайных чисел
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < n; ++j) {
            out << rand() % 1000 << " "; // Записываем случайное число от 0 до 999 в файл
        }
        out << endl; // Переход на новую строку после записи n чисел
    }
}

// Функция для нахождения суммы первого и максимального элемента в файле
int sFM(const string& f) {
    ifstream in(f); // Открываем файл для чтения
    if (!in) { // Проверка успешности открытия файла
        cerr << "Ошибка открытия файла." << endl; // Вывод сообщения об ошибке
        return -1; // Возвращаем -1 в случае ошибки
    }

    int fElem = -1; // Переменная для хранения первого элемента (инициализируем как -1)
    int mElem = numeric_limits<int>::min(); // Переменная для хранения максимального элемента (инициализируем минимально возможным значением)
    int n;

    // Читаем числа из файла и находим первый и максимальный элементы
    while (in >> n) {
        if (fElem == -1) fElem = n; // Сохраняем первый элемент
        if (n > mElem) mElem = n; // Обновляем максимальный элемент, если текущее число больше
    }

    if (fElem == -1) { // Проверка, был ли прочитан хотя бы один элемент
        cerr << "Файл пуст." << endl; // Сообщение об ошибке, если файл пуст
        return -1; // Возвращаем -1 в случае пустого файла
    }

    return fElem + mElem; // Возвращаем сумму первого и максимального элемента
}

int main() {
    const string f = "data.txt"; // Имя файла для записи и чтения данных

    // Заполняем файл случайными данными: 5 строк по 10 чисел
    gD(f, 5, 10); 

    // Вычисляем и выводим результат суммы первого и максимального элемента
    int res = sFM(f);
    if (res != -1) cout << res << endl; // Если результат не равен -1, выводим его

    return 0; // Завершение программы
}
