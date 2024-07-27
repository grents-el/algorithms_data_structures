#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

// Структура для представления точки на плоскости
struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {} // Конструктор для инициализации координат
};

// Структура для представления ребра графа
struct Edge {
    int u, v; // Вершины, которые соединяет ребро
    double weight; // Вес ребра (расстояние между вершинами)
    Edge(int _u, int _v, double _weight) : u(_u), v(_v), weight(_weight) {} // Конструктор для инициализации ребра
};

// Функция для вычисления расстояния между двумя точками
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)); // Возвращает евклидово расстояние
}

// Функция для сравнения двух рёбер по их весу (для сортировки)
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Класс для представления и работы с непересекающимися множествами (для алгоритма Крускала)
class DisjointSet {
private:
    vector<int> parent, rank; // Векторы для хранения родителя и ранга каждого элемента
public:
    // Конструктор, инициализирующий n множеств-этап 1 каждый элемент = множество
    DisjointSet(int n) {
        parent.resize(n); // Инициализация вектора parent размером n
        rank.resize(n, 0); // Инициализация вектора rank размером n значениями 0
        for (int i = 0; i < n; ++i) // Цикл для установки начальных значений
            parent[i] = i; // Каждый элемент является своим собственным родителем
    }

    // Функция для нахождения корня элемента u с применением сжатия путей
    int find(int u) {
        if (u != parent[u]) // Если элемент не является своим собственным родителем
            parent[u] = find(parent[u]); // Рекурсивно находит корень и выполняет сжатие пути
        return parent[u]; // Возвращает корень элемента
    }

    // Функция для объединения двух множеств
    void merge(int u, int v) {
        int pu = find(u); // Находит корень первого элемента
        int pv = find(v); // Находит корень второго элемента
        if (pu == pv) return; // Если корни одинаковы, элементы уже в одном множестве
        if (rank[pu] > rank[pv]) // Если ранг первого корня больше ранга второго
            parent[pv] = pu; // Первый корень становится родителем второго
        else if (rank[pu] < rank[pv]) // Если ранг первого корня меньше ранга второго
            parent[pu] = pv; // Второй корень становится родителем первого
        else {
            parent[pv] = pu; // Первый корень становится родителем второго
            rank[pu]++; // Увеличиваем ранг первого корня
        }
    }
};

// Функция для нахождения кластеров
void findClusters(int N, int K, const vector<Point>& points) {
    int n = points.size(); // Получаем количество точек
    vector<Edge> edges; // Вектор для хранения всех рёбер

    // Построение списка всех рёбер полного графа -2
    for (int i = 0; i < n; ++i) { // Внешний цикл по всем точкам
        for (int j = i + 1; j < n; ++j) { // Внутренний цикл по всем следующим точкам
            double dist = distance(points[i], points[j]); // Вычисляем расстояние между точками
            edges.push_back(Edge(i, j, dist)); // Добавляем ребро в вектор рёбер
        }
    }

    // Сортировка рёбер по возрастанию веса -3
    sort(edges.begin(), edges.end(), compareEdges); // Сортируем рёбра по весу

    // Инициализация структуры для работы с непересекающимися множествами
    DisjointSet ds(n); // Создаём объект класса DisjointSet для n элементов
    vector<Edge> minSpanningTree; // Вектор для хранения минимального остовного дерева
    vector<vector<bool>> adjMatrix(n, vector<bool>(n, false)); // Матрица смежности
    int components = n; // Начальное количество компонент связности

    // Построение минимального остовного дерева с использованием первых N-K рёбер
    for (const Edge& edge : edges) { // Проходим по всем рёбрам
        int u = edge.u; // Получаем первую вершину ребра
        int v = edge.v; // Получаем вторую вершину ребра
        if (ds.find(u) != ds.find(v)) { // Если вершины находятся в разных компонентах
            ds.merge(u, v); // Объединяем компоненты
            minSpanningTree.push_back(edge); // Добавляем ребро в минимальное остовное дерево
            adjMatrix[u][v] = adjMatrix[v][u] = true; // Обновляем матрицу смежности
            components--; // Уменьшаем количество компонент
            if (components == K) break; // Останавливаемся, когда найдено K компонент связности
        }
    }

    // Вывод матрицы смежности
    cout << "Матрица смежности:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Построение кластеров
    vector<vector<int>> clusters(n); // Вектор для хранения кластеров
    for (const Edge& edge : minSpanningTree) { // Проходим по рёбрам минимального остовного дерева
        clusters[edge.u].push_back(edge.v); // Добавляем вершину v в кластер u
        clusters[edge.v].push_back(edge.u); // Добавляем вершину u в кластер v
    }

    // Вывод информации о кластерах
    for (int i = 0; i < n; ++i) { // Проходим по всем точкам
        if (clusters[i].empty()) continue; // Пропускаем пустые кластеры
        cout << "Кластер " << i + 1 << ":\n"; // Выводим номер кластера
        cout << "Количество вершин: " << clusters[i].size() + 1 << "\n"; // Выводим количество вершин в кластере

        // Инициализация минимальных и максимальных значений координат
        double minX = points[i].x, maxX = points[i].x; // Минимальная и максимальная координата X
        double minY = points[i].y, maxY = points[i].y; // Минимальная и максимальная координата Y
        double sumX = points[i].x, sumY = points[i].y; // Суммы координат X и Y для вычисления центра

        // Обновление значений для всех вершин в кластере
        for (int j : clusters[i]) { // Проходим по всем вершинам в кластере
            minX = min(minX, points[j].x); // Обновляем минимальную координату X
            maxX = max(maxX, points[j].x); // Обновляем максимальную координату X
            minY = min(minY, points[j].y); // Обновляем минимальную координату Y
            maxY = max(maxY, points[j].y); // Обновляем максимальную координату Y
            sumX += points[j].x; // Добавляем координату X к сумме
            sumY += points[j].y; // Добавляем координату Y к сумме
        }

        // Вычисление координат центра кластера
        double centroidX = sumX / (clusters[i].size() + 1); // Центр кластера по X
        double centroidY = sumY / (clusters[i].size() + 1); // Центр кластера по Y
        cout << "Min X: " << minX << ", Max X: " << maxX << "\n"; // Вывод минимальной и максимальной координаты X
        cout << "Min Y: " << minY << ", Max Y: " << maxY << "\n"; // Вывод минимальной и максимальной координаты Y
        cout << "Centroid X: " << centroidX << ", Centroid Y: " << centroidY << "\n\n"; // Вывод координат центра кластера
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int N = 10; // Количество точек
    int K = 3;  // Количество кластеров
    vector<Point> points; // Вектор для хранения точек

    // Генерация N случайных точек
    for (int i = 0; i < N; ++i) { // Цикл для генерации точек
        double x = static_cast<double>(rand()) / RAND_MAX * 10; // Генерация случайной координаты X
        double y = static_cast<double>(rand()) / RAND_MAX * 10; // Генерация случайной координаты Y
        points.emplace_back(x, y); // Добавление точки в вектор points
    }

    // Вызов функции для нахождения кластеров
    findClusters(N, K, points); // Нахождение кластеров

    return 0; // Завершение программы
}

