// laba_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 
template<typename T>
class Sort {
public:
    // Статический метод для сортировки методом Шелла
    static int shellSort(std::vector<T*>& arr, int n) {
        int comparisons = 0;
        for (int gap = n / 2; gap > 0; gap /= 2) { // Цикл для определения шага сортировки
            for (int i = gap; i < n; ++i) { // Цикл для прохода по элементам внутри каждого шага
                T* temp = arr[i]; // Временная переменная для хранения значения текущего элемента
                int j;
                for (j = i; j >= gap && *arr[j - gap] > *temp; j -= gap) { // Цикл для сравнения и перемещения элементов на правильные позиции
                    arr[j] = arr[j - gap]; // Перемещение элемента влево
                    ++comparisons;
                }
                arr[j] = temp; // Помещение временного значения на правильную позицию
                //++comparisons;
            }

        }
        return comparisons;
    }

    // Статический метод для сортировки пирамидой
    static int pyramidSort(std::vector<T*>& arr, int n) {
        int comparisons = 0; // Переменная для подсчета сравнений элементов
        for (int i = n / 2 - 1; i >= 0; --i) { // Построение начальной кучи
            heapify(arr, n, i, comparisons); // Вызов функции для превращения массива в кучу
        }
        for (int i = n - 1; i >= 0; --i) { // Один за другим извлекаем элементы из кучи
            std::swap(arr[0], arr[i]); // Перемещаем текущий корень в конец
            heapify(arr, i, 0, comparisons); // Вызов функции для восстановления свойства кучи
        }
        return comparisons;
    }

    // Статический метод для проверки косвенной упорядоченности
    static bool isIndirectlySorted(const std::vector<T*>& arr, int n) {
        for (int i = 0; i < n - 1; ++i) { // Проход по элементам массива
            if (*arr[i] > *arr[i + 1]) { // Проверка на косвенную упорядоченность
                return false;
            }
        }
        return true;
    }

private:
    // Вспомогательная функция для превращения массива в кучу
    static void heapify(std::vector<T*>& arr, int n, int i, int& comparisons) {
        int largest = i; // Инициализация корня поддерева
        int l = 2 * i + 1; // Левый потомок
        int r = 2 * i + 2; // Правый потомок

        if (l < n && *arr[l] > *arr[largest]) { // Если левый потомок больше корня
            largest = l;
            ++comparisons; // Увеличиваем счетчик сравнений
        }

        if (r < n && *arr[r] > *arr[largest]) { // Если правый потомок больше, чем наибольший элемент
            largest = r;
            ++comparisons;
        }

        if (largest != i) { // Если наибольший элемент не корень
            std::swap(arr[i], arr[largest]); // Меняем местами корень и наибольший элемент
            heapify(arr, n, largest, comparisons); // Рекурсивно приводим поддерево к виду кучи
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 100; // Размер массива
    int* arr1, *arr2, *arr3;
    std::vector<int*> ascending(n); // Вектор для упорядоченного по возрастанию массива
    std::vector<int*> descending(n); // Вектор для упорядоченного по убыванию массива
    std::vector<int*> random(n); // Вектор для случайного массива
    arr1 = new int[n];
    arr2 = new int[n];
    arr3 = new int[n];
    // Генерация массивов/измен
    for (int i = 0; i < n; ++i) {
        arr1[i] = i;
        arr2[i] = n - 1;
        arr3[i] = rand() % n;
        ascending[i] = &arr1[i]; // Упорядоченный по возрастанию
        descending[i] = &arr2[i]; // Упорядоченный по убыванию
        random[i] = &arr3[i]; // Случайные значения
    }

    // Выполнение сортировки и вывод количества сравнений
    std::cout << "Упорядоченный по возрастанию:\n";
    int asc_comparisons_shell = Sort<int>::shellSort(ascending, n);
    std::cout << "Shell Sort кол-во сравнений: " << asc_comparisons_shell << std::endl;
    std::cout << "Проверка: " << Sort<int>::isIndirectlySorted(ascending, n) << std::endl;



    int asc_comparisons_pyramid = Sort<int>::pyramidSort(ascending, n);
    std::cout << "Pyramid Sort кол-во сравнений: " << asc_comparisons_pyramid << std::endl;
    std::cout << "Проверка: " << Sort<int>::isIndirectlySorted(ascending, n) << std::endl;

    // Повторяем для убывающего и случайного массивов
    std::cout << "Упорядоченный по убыванию:\n";
    int dsc_comparisons_shell = Sort<int>::shellSort(descending, n);
    std::cout << "Shell Sort кол-во сравнений: " << dsc_comparisons_shell << std::endl;
    std::cout << "Проверка: " << Sort<int>::isIndirectlySorted(descending, n) << std::endl;
    //убывание
    int dsc_comparisons_pyramid = Sort<int>::pyramidSort(descending, n);
    std::cout << "Pyramid Sort кол-во сравнений: " << dsc_comparisons_pyramid << std::endl;
    std::cout << "Проверка: " << Sort<int>::isIndirectlySorted(descending, n) << std::endl;
    //random
    std::cout << "random:\n";
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr3[i]);
    }
    int rnd_comparisons_shell = Sort<int>::shellSort(random, n);
    std::cout << "Shell Sort кол-во сравнений: " << rnd_comparisons_shell << std::endl;
    std::cout << "Проверка: " << Sort<int>::isIndirectlySorted(random, n) << std::endl;
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr3[i]);
    }

    int rnd_comparisons_pyramid = Sort<int>::pyramidSort(random, n);
    std::cout << "Pyramid Sort кол-во сравнений: " << rnd_comparisons_pyramid << std::endl;
    std::cout << "Проверка: " << Sort<int>::isIndirectlySorted(random, n) << std::endl;

    // Освобождение памяти
    //for (int i = 0; i < n; ++i) {
      //  delete[] ascending[n];
        //delete[] descending[n];
        //delete[] random[n];
    //}

    return 0;
}
