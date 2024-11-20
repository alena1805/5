#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Генерация случайных чисел и запись их в бинарный файл
void g(const std::string& f, int c) {
    std::ofstream o(f, std::ios::binary); // Открываем файл для записи в бинарном режиме
    if (!o) { 
        std::cerr << "Ошибка!" << std::endl; // Проверяем, удалось ли открыть файл
        return; 
    }
    for (int i = 0; i < c; ++i) { // Генерируем c случайных чисел
        int n = rand() % 10000; // Генерация случайного числа от 0 до 9999
        o.write(reinterpret_cast<const char*>(&n), sizeof(n)); // Запись числа в файл
    }
}

// Проверка совпадения первой и последней цифры числа
bool s(int n) {
    int l = std::abs(n) % 10; // Получаем последнюю цифру числа
    while (n >= 10 || n <= -10) n /= 10; // Убираем все цифры кроме первой
    return std::abs(n) == l; // Сравниваем первую и последнюю цифры
}

// Фильтрация чисел из входного файла и запись подходящих в выходной файл
void f(const std::string& in, const std::string& out) {
    std::ifstream i(in, std::ios::binary); // Открываем входной файл для чтения
    std::ofstream o(out, std::ios::binary); // Открываем выходной файл для записи
    if (!i || !o) { 
        std::cerr << "Ошибка!" << std::endl; // Проверяем, удалось ли открыть файлы
        return; 
    }
    int n;
    while (i.read(reinterpret_cast<char*>(&n), sizeof(n))) // Читаем числа из входного файла
        if (s(n)) o.write(reinterpret_cast<const char*>(&n), sizeof(n)); // Если число подходит, записываем его в выходной файл
}

// Печать содержимого бинарного файла на экран
void p(const std::string& f) {
    std::ifstream i(f, std::ios::binary); // Открываем файл для чтения
    if (!i) { 
        std::cerr << "Ошибка!" << std::endl; // Проверяем, удалось ли открыть файл
        return; 
    }
    int n;
    std::cout << "Файл " << f << ": "; // Выводим название файла
    while (i.read(reinterpret_cast<char*>(&n), sizeof(n))) // Читаем числа из файла
        std::cout << n << " "; // Печатаем каждое число
    std::cout << std::endl; // Переход на новую строку после печати всех чисел
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Инициализируем генератор случайных чисел
    const std::string in = "i.dat", out = "o.dat"; // Определяем имена входного и выходного файлов
    
    g(in, 100);  // Генерация 100 случайных чисел и запись их в файл i.dat
    f(in, out);  // Фильтрация чисел из i.dat и запись подходящих в файл o.dat
    p(in);       // Печать содержимого входного файла i.dat
    p(out);      // Печать содержимого выходного файла o.dat

    std::cout << "Готово." << std::endl; // Сообщение о завершении работы программы
    return 0; // Завершение программы
}
