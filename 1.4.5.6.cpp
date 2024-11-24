#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

// Класс с набором статических методов для работы с файлами
class F {
public:
    // Генерация случайных чисел и запись их в бинарный файл
    static void gRN(const string& f, int c) {
        ofstream o(f, ios::binary);  // Открываем файл для записи в бинарном режиме
        if (!o) {
            cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }
        for (int i = 0; i < c; ++i) {
            int n = rand() % 10000;  // Генерация случайного числа
            o.write(reinterpret_cast<const char*>(&n), sizeof(n));  // Запись числа в файл
        }
    }

    // Проверка, является ли первое и последнее число числа одинаковыми цифрами
    static bool mD(int n) {
        int d = abs(n) % 10;  // Получаем последнюю цифру числа
        while (abs(n) >= 10) n /= 10;  // Убираем все цифры, кроме первой
        return abs(n) == d;  // Сравниваем первую и последнюю цифры
    }

    // Чтение чисел из бинарного файла и запись тех, у которых первая и последняя цифры одинаковые, в другой файл
    static void fN(const string& i, const string& o) {
        ifstream in(i, ios::binary);  // Открытие исходного файла для чтения в бинарном формате
        ofstream out(o, ios::binary);  // Открытие целевого файла для записи в бинарном формате
        if (!in || !out) {
            cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }
        int n;
        while (in.read(reinterpret_cast<char*>(&n), sizeof(n))) {  // Чтение чисел из файла
            if (mD(n)) {  // Проверка, если цифры совпадают
                out.write(reinterpret_cast<const char*>(&n), sizeof(n));  // Запись числа в новый файл
            }
        }
    }

    // Вывод содержимого бинарного файла в консоль
    static void pF(const string& f) {
        ifstream in(f, ios::binary);  // Открываем файл для чтения
        if (!in) {
            cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }
        int n;
        cout << "Файл " << f << ": ";
        while (in.read(reinterpret_cast<char*>(&n), sizeof(n))) {  // Чтение чисел из файла
            cout << n << " ";  // Вывод числа в консоль
        }
        cout << endl;
    }

    // Чтение строк из текстового файла и запись тех, которые начинаются на заданную букву, в новый файл
    static void fL(char l, const string& i, const string& o) {
        ifstream in(i);  // Открываем исходный текстовый файл для чтения
        ofstream out(o);  // Открываем целевой файл для записи
        if (!in) {
            cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }
        string s;
        while (getline(in, s)) {  // Чтение строк из файла
            if (s.size() > 1 && (tolower(s[0]) == tolower(l) || tolower(s[1]) == tolower(l))) {
                out << s << endl;  // Запись строк в новый файл, если они начинаются с буквы l
            }
        }
    }

    // Генерация случайных чисел в виде таблицы (r строк и c столбцов) и запись их в файл
    static void gRD(const string& f, int r, int c) {
        ofstream o(f);  // Открываем файл для записи
        if (!o) {
            cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }
        srand(static_cast<unsigned>(time(0)));  // Инициализация генератора случайных чисел
        for (int i = 0; i < r; ++i) {  // Проходим по строкам
            for (int j = 0; j < c; ++j) {  // Проходим по столбцам
                o << rand() % 1000 << " ";  // Записываем случайное число
            }
            o << endl;  // Переход на новую строку
        }
    }

    // Чтение чисел из файла и возвращение суммы первого и наибольшего числа
    static int sFM(const string& f) {
        ifstream in(f);  // Открываем файл для чтения
        if (!in) {
cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return -1;
        }
        int fE = -1, mE = numeric_limits<int>::min(), n;
        while (in >> n) {  // Чтение чисел из файла
            if (fE == -1) fE = n;  // Запоминаем первое число
            if (n > mE) mE = n;  // Ищем наибольшее число
        }
        if (fE == -1) {  // Если файл пустой
            cerr << "Пусто!" << endl;
            return -1;
        }
        return fE + mE;  // Возвращаем сумму первого и наибольшего числа
    }

    // Генерация случайных чисел в заданном диапазоне и запись их в файл
    static void gRR(const string& f, int c, int mn, int mx) {
        ofstream o(f);  // Открываем файл для записи
        if (!o) {
            cerr << "Ошибка!" << endl;  // Если файл не открылся, выводим ошибку
            return;
        }
        for (int i = 0; i < c; ++i) {  // Генерация и запись случайных чисел
            o << mn + rand() % (mx - mn + 1) << endl;
        }
    }

    // Чтение чисел из файла и запись их в новый файл, деленных на k
    static void rN(const string& i, const string& o, int k) {
        ifstream in(i);  // Открываем исходный файл для чтения
        ofstream out(o);  // Открываем целевой файл для записи
        if (!in || !out) {
            cerr << "Ошибка!" << endl;  // Если файлы не открылись, выводим ошибку
            return;
        }
        int n;
        while (in >> n) {  // Чтение чисел из файла
            out << n / k << endl;  // Запись чисел, деленных на k, в новый файл
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));  // Инициализация генератора случайных чисел

    const string i = "i.dat", o = "o.dat";  // Имена файлов для ввода и вывода
    F::gRN(i, 100);  // Генерация случайных чисел и запись в файл i.dat
    F::fN(i, o);  // Запись чисел с одинаковыми первой и последней цифрой в файл o.dat
    F::pF(i);  // Вывод содержимого файла i.dat
    F::pF(o);  // Вывод содержимого файла o.dat

    const string t = "data.txt";  // Имя текстового файла для генерации таблицы
    F::gRD(t, 5, 10);  // Генерация таблицы случайных чисел и запись в файл data.txt

    int r = F::sFM(t);  // Чтение чисел из data.txt и вычисление суммы первого и наибольшего
    if (r != -1) cout << r << endl;  // Вывод суммы

    char l;
    cout << "Введите букву: ";  // Запрос буквы у пользователя
    cin >> l;
    if (!isalpha(l)) {  // Проверка, что введена буква
        cerr << "Ошибка!" << endl;
        return 1;
    }

    const string inFile = "input.txt", outFile = "text_out.txt";  // Имена файлов для текста
    F::fL(l, inFile, outFile);  // Выбор строк, начинающихся с буквы l, и запись их в новый файл

    const string cFile = "c.txt", dFile = "d.txt";  // Имена файлов для чисел
    F::gRR(cFile, 100, 1, 1000);  // Генерация случайных чисел и запись в файл c.txt

    int k;
    while (true) {  // Запрос значения k
        cout << "Введите k: ";
        cin >> k;
        if (cin.fail() || k <= 0) {  // Проверка на корректность ввода
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка!" << endl;
        } else {
            break;
        }
    }

    F::rN(cFile, dFile, k);  // Запись чисел, деленных на k, в новый файл d.txt

    cout << "Готово!" << endl;  // Завершение программы
    return 0;
}
