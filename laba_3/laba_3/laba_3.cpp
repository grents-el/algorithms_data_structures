

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
constexpr int MAX_STRING_LENGTH = 100;
constexpr int MAX_CHAR_RANGE = 128;
constexpr int MAX_HASH_TABLE_SIZE = 10007;

class SList {
public:
    struct Node {
        char* data;
        Node* next;

        Node(const char* str) {
            size_t length = strlen(str) + 1;
            data = new char[length];
            strcpy_s(data, length, str);// копируем строку
            next = nullptr;
        }


        ~Node() {
            delete[] data;
        }
    };

    Node* head;
    int comparisons;
    int uniqueStrings;


public:
    SList() : head(nullptr), comparisons(0), uniqueStrings(0) {

    }

    ~SList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool contains(const char* str) {//проверяем наличие
        Node* current = head;
        //comparisons = 0;
        while (current != nullptr) {
            comparisons++;
            if (strcmp(current->data, str) == 0)
                return true;
            current = current->next;//указываем на след
        }
        return false;
    }

    void add(const char* str) {//довляем если еще нету
        if (!contains(str)) {
            Node* newNode = new Node(str);//память
            newNode->next = head;//перекидываем указатель
            head = newNode;//
            uniqueStrings++;
        }
    }
    void add1(const char* str) {//довляем если еще нету
        //if (!contains(str)) {
        Node* newNode = new Node(str);//память
        newNode->next = head;//перекидываем указатель
        head = newNode;//
        uniqueStrings++;
        //}
    }

    int getComparisons() const {//
        return comparisons;
    }

    int getUniqueStrings() const {
        return uniqueStrings;
    }

    void merge(SList& other) {//обьедиеяем список
        Node* current = other.head;
        while (current != nullptr) {
            add1(current->data);
            current = current->next;
        }
    }
};

class HashTable {
private:
    SList* table;
    int size;

public:
    HashTable(int q) : size(q) {
        table = new SList[q];
    }

    ~HashTable() {
        delete[] table;
    }

    int hash(const char* str) const {
        int hashValue = 0;
        int length = strlen(str);
        for (int i = 0; i < length; ++i) {
            hashValue = (hashValue * 31 + str[i]) % size;
        }
        return hashValue;
    }

    void addUnique(const char* str) {
        int index = hash(str);
        table[index].add(str);
    }

    void chainLists(SList& resultList) {
        for (int i = 0; i < size; ++i) {
            resultList.merge(table[i]);
        }
    }
    void printHashTable() {
        for (int i = 0; i < size; ++i) {
            cout << "Ячейка № " << i << ": ";
            SList::Node* current = table[i].head;
            while (current != nullptr) {
                cout << current->data << " | ";
                current = current->next;
            }
            cout << endl;
        }
    }

    void printHashList(SList& resultList) {
        for (int i = 0; i < size; ++i) {
            //cout << "Ячейка № " << i << ": ";
            SList::Node* current = table[i].head;
            while (current != nullptr) {
                cout << current->data << " | ";
                current = current->next;
            }
            //cout << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int n; // Number of strings
    int minStringLength;
    int maxStringLength;
    char** arraystr;
    cout << "Введите количество строк: ";
    cin >> n;
    cout << "Введите минимальную длину строки:";
    cin >> minStringLength;
    cout << "Введите максимальную длину строки:";
    cin >> maxStringLength;

    int q; // Size of the hash table
    cout << "Введите размер хэш-таблицы: ";
    cin >> q;

    // HashTable hashTable(q);
     //for (int i = 0; i < n; ++i) {
       //  hashTable.addUnique(strings[i]);
     //}
    HashTable hashTable(q);
    arraystr = new char* [n];

    for (int i = 0; i < n; i++) {
        int length = minStringLength + rand() % (maxStringLength - minStringLength + 1);
        char* str = new char[length + 1];
        for (int j = 0; j < length; j++)
            str[j] = 'a' + rand() % 26; // случайный символ в диапазоне 'a'-'z'
        str[length] = '\0';
        arraystr[i] = str;
        hashTable.addUnique(str);
    }
    SList uniqueList;
    hashTable.chainLists(uniqueList);

    cout << "table" << endl;
    hashTable.printHashTable();
    puts("");
    cout << "List" << endl;
    hashTable.printHashList(uniqueList);
    puts("");

    cout << "Всего сравнений: " << uniqueList.getComparisons() << endl;
    cout << "Количество уникальных строк: " << uniqueList.getUniqueStrings() << endl;


    for (int i = 0; i < n; i++) {
        delete[]arraystr[i];
    }
    delete[]arraystr;

    return 0;
}
