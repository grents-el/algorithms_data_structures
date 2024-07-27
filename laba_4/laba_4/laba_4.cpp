
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
// Структура для представления груза
struct Cargo { // Описание структуры Cargo
    int weight; // Вес груза
    int value; // Стоимость груза
};

// Гребный алгоритм
int greedyMaxCost(vector<Cargo> cargoes, int W) { // Функция для вычисления максимальной стоимости грузов при использовании жадного алгоритма
    int n = cargoes.size(); // Получение количества грузов
    sort(cargoes.begin(), cargoes.end(), [](const Cargo& a, const Cargo& b) { // Сортировка грузов по убыванию стоимости
        return a.value > b.value; // Сравнение грузов по стоимости в порядке убывания
        });

    int maxCost = 0; // Инициализация максимальной стоимости
    int currentWeight = 0; // Инициализация текущего веса
    for (int i = 0; i < n; ++i) { // Перебор всех грузов
        if (currentWeight + cargoes[i].weight <= W) { // Если груз помещается в рюкзак
            maxCost += cargoes[i].value; // Увеличение максимальной стоимости
            currentWeight += cargoes[i].weight; // Увеличение текущего веса
        }
    }
    return maxCost; // Возврат максимальной стоимости
}

// Алгоритм на основе обратного отслеживания
void backtrackingMaxCostUtil(const vector<Cargo>& cargoes, int W, int index, int currentWeight, int currentValue, int& maxCost) { // Вспомогательная функция для алгоритма на основе обратного отслеживания
    if (index == cargoes.size()) { // Если достигнут конец списка грузов
        maxCost = max(maxCost, currentValue); // Обновление максимальной стоимости
        return; // Выход из функции
    }

    // Если добавление текущего груза возможно
    if (currentWeight + cargoes[index].weight <= W) {
        backtrackingMaxCostUtil(cargoes, W, index + 1, currentWeight + cargoes[index].weight,
            currentValue + cargoes[index].value, maxCost); // Вызов функции для следующего груза
    }

    // Пропуск текущего груза
    backtrackingMaxCostUtil(cargoes, W, index + 1, currentWeight, currentValue, maxCost); // Вызов функции для следующего груза
}

int backtrackingMaxCost(const vector<Cargo>& cargoes, int W) { // Функция для вычисления максимальной стоимости грузов при использовании алгоритма на основе обратного отслеживания
    int maxCost = 0; // Инициализация максимальной стоимости
    backtrackingMaxCostUtil(cargoes, W, 0, 0, 0, maxCost); // Вызов вспомогательной функции
    return maxCost; // Возврат максимальной стоимости
}

// Алгоритм динамического программирования
int dpMaxCost(const vector<Cargo>& cargoes, int W) { // Функция для вычисления максимальной стоимости грузов при использовании алгоритма динамического программирования
    int n = cargoes.size(); // Получение количества грузов
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0)); // Создание двумерного массива для динамического программирования

    for (int i = 1; i <= n; ++i) { // Перебор всех грузов
        for (int j = 0; j <= W; ++j) { // Перебор всех возможных весов
            if (cargoes[i - 1].weight > j) { // Если текущий груз не помещается в рюкзак
                dp[i][j] = dp[i - 1][j]; // Просто копируем предыдущее значение
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cargoes[i - 1].weight] + cargoes[i - 1].value); // Выбираем максимум между текущим и значением, полученным с учетом добавления текущего груза
            }
        }
    }

    return dp[n][W]; // Возвращаем максимальную стоимость
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите количество грузов: "; // Выводим приглашение для ввода количества грузов
    cin >> n; // Считываем количество грузов

    vector<Cargo> cargoes(n); // Создаем вектор для хранения грузов
    int totalWeight = 0; // Инициализация общего веса
    for (int i = 0; i < n; ++i) { // Перебор всех грузов
        cout << "Введите вес и стоимость груза " << i + 1 << ": "; // Выводим приглашение для ввода веса и стоимости текущего груза
        cin >> cargoes[i].weight >> cargoes[i].value; // Считываем вес и стоимость текущего груза
        totalWeight += cargoes[i].weight; // Обновляем общий вес
    }

    int W = totalWeight / 2; // Вычисляем половину общего веса

    // Гребной алгоритм
    int greedyResult = greedyMaxCost(cargoes, W); // Вызываем функцию для гребного алгоритма
    cout << "Результат работы жадного алгоритма: " << greedyResult << endl; // Выводим результат работы гребного алгоритма

    // Алгоритм на основе обратного отслеживания
    if (n <= 30) { // Проверка, что количество грузов меньше или равно 30
        int backtrackingResult = backtrackingMaxCost(cargoes, W); // Вызываем функцию для алгоритма на основе обратного отслеживания
        cout << "Результат работы алгоритма обратного обхода: " << backtrackingResult << endl; // Выводим результат работы алгоритма на основе обратного отслеживания
    }
    else {
        cout << "Алгоритм обратного пути пропущен из-за большого количества грузов." << endl; // Выводим сообщение о пропуске алгоритма на основе обратного отслеживания
    }

    // Алгоритм динамического программирования
    int dpResult = dpMaxCost(cargoes, W); // Вызываем функцию для алгоритма динамического программирования
    cout << "Результат работы алгоритма динамического программирования: " << dpResult << endl; // Выводим результат работы алгоритма динамического программирования

    return 0; // Возврат нуля, обозначающий успешное завершение программы
}
