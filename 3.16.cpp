#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

// Структура для хранения информации об игрушке
struct Toy {
    char n[50];  // Название игрушки
    double p;    // Стоимость игрушки
    int a_min;   // Минимальный возраст для игрушки
    int a_max;   // Максимальный возраст для игрушки
};

// Функция для записи игрушек в бинарный файл
void wtf(const char* f, const vector<Toy>& t) {
    ofstream out(f, ios::binary); // Открываем файл для записи в бинарном режиме
    if (!out) {
        cerr << "Ошибка при открытии файла." << endl; // Проверка на успешное открытие файла
        return;
    }
    
    // Записываем каждую игрушку в файл
    for (const auto& toy : t) {
        out.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
    }
    out.close(); // Закрываем файл после записи
}

// Функция для чтения игрушек из бинарного файла
vector<Toy> rtf(const char* f) {
    vector<Toy> t; // Вектор для хранения прочитанных игрушек
    ifstream in(f, ios::binary); // Открываем файл для чтения в бинарном режиме
    if (!in) {
        cerr << "Ошибка при открытии файла." << endl; // Проверка на успешное открытие файла
        return t;
    }

    Toy toy; // Переменная для хранения временной игрушки
    // Читаем данные из файла, пока это возможно
    while (in.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        t.push_back(toy); // Добавляем прочитанную игрушку в вектор
    }
    in.close(); // Закрываем файл после чтения
    return t; // Возвращаем вектор с игрушками
}

// Функция для поиска информации об игрушке по названию
void fnd(const vector<Toy>& t, const char* n) {
    double s = 0; // Сумма стоимости найденных игрушек
    int c = 0; // Счетчик найденных игрушек
    int min_a = -1, max_a = -1; // Минимальный и максимальный возраст

    // Перебираем все игрушки в векторе
    for (const auto& toy : t) {
        if (strcmp(toy.n, n) == 0) { // Сравниваем название игрушки с искомым
            s += toy.p; // Добавляем стоимость к общей сумме
            c++; // Увеличиваем счетчик найденных игрушек
            // Обновляем минимальный и максимальный возраст
            if (min_a == -1 || toy.a_min < min_a) min_a = toy.a_min;
            if (max_a == -1 || toy.a_max > max_a) max_a = toy.a_max;
        }
    }

    // Если найдены игрушки, выводим информацию о них
    if (c > 0) {
        cout << "Игрушка "" << n << "" для детей от " 
             << min_a << " до " << max_a << " лет." << endl;
        cout << "Средняя стоимость: " << s / c << " рублей." << endl;
    } else {
        cout << "Игрушка "" << n << "" не найдена." << endl; // Если не найдены, выводим сообщение
    }
}

int main() {
    // Инициализация вектора игрушек
    vector<Toy> toys = {
        {"Кубики", 150.0, 2, 5},
        {"Машинка", 200.0, 3, 7},
        {"Кубики", 120.0, 2, 5},
        {"Кукла", 250.0, 4, 8},
        {"Конструктор", 300.0, 5, 10}
    };

    const char* f = "toys.dat"; // Имя файла для записи и чтения

    // Запись данных о игрушках в файл
    wtf(f, toys);

    // Чтение данных о игрушках из файла
    vector<Toy> t = rtf(f);

    // Поиск информации о "Кубиках"
    fnd(t, "Кубики");

    return 0; // Завершение программы
}
