#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// функция для вычисления у в зависимости от х
double calc_y(double x) {
    if (x < -6.0 || x > 8.0) return NAN;
    if (x <= -2.0) return -sqrt(-2.0 - x);           // Корень влево вниз
    if (x <= -1.0) return sqrt(1.0 - pow(x + 1.0, 2)); // Окружность R=1
    if (x <= 0.0)  return pow(x, 2);                 // Парабола стандартная
    if (x <= 2.0)  return 0.5 * pow(x, 2);           // Парабола растянутая
    if (x <= 4.0)  return sqrt(4.0 - pow(x - 2.0, 2)); // Окружность R=2
    return -sqrt(x - 4.0);                           // Корень вправо вниз
}

int main() {
    setlocale(LC_ALL, "Russian");

    // в формате дал число х, вывело у по функции
    cout << "ввод одного значения" << endl;
    double x_s;
    cout << "введите значение x: ";
    cin >> x_s;
    
    double y_s = calc_y(x_s);
    if (isnan(y_s)) {
        cout << "функция не определена (диапазон [-6; 8]).\n";
    } else {
        cout << "y = " << y_s << "\n\n";
    }

    // вывод в виде таблицы
    double start, end, dx;
    cout << "введите нач, кон и шаг (например: -6 8 1): ";
    cin >> start >> end >> dx;

    // шапка таблицы
    cout << string(23, '-') << endl;
    cout << "|" << setw(9) << "x" << " |" << setw(9) << "y" << " |" << endl;
    cout << string(23, '-') << endl;

    // цикл вычисл процесс
    for (double x = start; x <= end + dx / 10.0; x += dx) {
        double y = calc_y(x);
        
        cout << "|" << setw(9) << fixed << setprecision(3) << x << " |";
        if (isnan(y)) {
             cout << setw(9) << "NaN" << " |" << endl;
        } else {
             cout << setw(9) << fixed << setprecision(3) << y << " |" << endl;
        }
    }
    cout << string(23, '-') << endl;

    return 0;
}
