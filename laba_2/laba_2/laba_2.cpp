

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
template<typename T>
class Sort {
public:
    // Static method for shell sort
    static int shellSort(vector<T*>& arr, int n) {
        int comparisons = 0;
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                T* temp = arr[i];
                int j;
                for (j = i; j >= gap && *arr[j - gap] > *temp; j -= gap) {
                    arr[j] = arr[j - gap];
                    ++comparisons;
                }
                arr[j] = temp;
            }

        }
        return comparisons;
    }

    // Static method for heap sort
    static int pyramidSort(vector<T*>& arr, int n) {
        int comparisons = 0;
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(arr, n, i, comparisons);
        }
        for (int i = n - 1; i >= 0; --i) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0, comparisons);
        }
        return comparisons;
    }

    // Static method to check if indirectly sorted
    static bool isIndirectlySorted(const vector<T*>& arr, int n) {
        for (int i = 0; i < n - 1; ++i) {
            if (*arr[i] > *arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

private:
    // Helper function for heapify
    static void heapify(vector<T*>& arr, int n, int i, int& comparisons) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && *arr[l] > *arr[largest]) {
            largest = l;
            ++comparisons;
        }

        if (r < n && *arr[r] > *arr[largest]) {
            largest = r;
            ++comparisons;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest, comparisons);
        }
    }
};

class Participant {
private: // Закрытая секция класса
    int id; // Уникальный идентификатор участника
    int solvedProblems; // Количество решенных задач
    int timeSpent; // Время, затраченное на решение задач
    int pointsScored; // Набранные баллы
    int unsuccessfulAttempts; // Количество неудачных попыток

public:
    Participant(int id, int solved, int time, int points, int attempts) // Конструктор класса
        : id(id), solvedProblems(solved), timeSpent(time), pointsScored(points), unsuccessfulAttempts(attempts) {} // Инициализация членов класса

    // Операторы сравнения для сортировки
    bool operator>(const Participant& other) const {
        if (pointsScored != other.pointsScored)
            return pointsScored > other.pointsScored;
        if (solvedProblems != other.solvedProblems)
            return solvedProblems > other.solvedProblems;
        if (timeSpent != other.timeSpent)
            return timeSpent < other.timeSpent;
        if (unsuccessfulAttempts != other.unsuccessfulAttempts)
            return unsuccessfulAttempts < other.unsuccessfulAttempts;
        return id < other.id;
    }

    bool operator<(const Participant& other) const {
        return other > *this;
    }

    friend ostream& operator<<(ostream& os, const Participant& participant) {
        os << participant.id << "\t" << participant.pointsScored << "\t\t" << participant.solvedProblems << "\t" << participant.timeSpent << "\t\t" << participant.unsuccessfulAttempts; // Выводим данные участника в поток
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    const int n = 10; // Количество участников
    vector<Participant*> participants; // Создаем вектор указателей на участников

    // Генерируем участников
    for (int i = 0; i < n; ++i) {
        participants.push_back(new Participant(i + 1, rand() % 6, rand() % 241 + 60, rand() % 26, rand() % 21)); // Добавляем нового участника в вектор
    }

    // Сортируем участников с использованием сортировки Шелла
    Sort<Participant>::shellSort(participants, n);


    ofstream outputFile("participant_results.txt");
    if (outputFile.is_open()) {
        outputFile << "Место  ID Баллы Решено Время Попыток \n";
        for (int i = n - 1; i >= 0; --i) {
            outputFile << n - i << "\t\t" << *participants[i] << "\n"; // 
        }
        outputFile.close();
        cout << "Результаты были сохранены в participant_results.txt\n";
    }
    else {
        cerr << "Невозможно открыть файл для записи.\n";
    }

    // Освобождаем выделенную память
    for (int i = 0; i < n; ++i) {
        delete participants[i];
    }

    return 0;
}
