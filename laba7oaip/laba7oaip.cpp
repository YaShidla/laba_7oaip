/*Шидловский К.Д. гр. 378101 лаб.7 вар. 13
Создать хеш-таблицу из случайных целых чисел и из нее сделать еще
две. В первую поместить записи с ключами большими К, а во второй – с
меньшими К.*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int data;   // данные, хранящиеся в вершине
    Node* next; // следующая вершина
};

Node** createHashTable(int size) {
    Node** table = new Node * [size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
    return table;
}

int myhash(int data, int size) {
    return data % size;
}

Node* insertNode(Node** hashTable, int data, int size) {
    Node* p = new Node;
    if (!p) {
        cerr << "Нехватка памяти (insertNode)\n";
        exit(1);
    }
    int bucket = myhash(data, size);
    p->data = data;
    p->next = hashTable[bucket];
    hashTable[bucket] = p;
    return p;
}

// Очистка памяти
void deleteHashTable(Node** hashTable, int size) {
    for (int i = 0; i < size; i++) {
        Node* p = hashTable[i];
        while (p) {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }
    delete[] hashTable;
}

void printHashTable(Node** hashTable, int size) {
    for (int i = 0; i < size; i++) {
        cout << i << ": ";
        Node* p = hashTable[i];
        while (p) {
            cout << p->data << " -> ";
            p = p->next;
        }
        cout << "null\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int hashTableSize, numElements, K;
    cout << "Введите количество элементов: ";
    cin >> numElements;
    cout << "Введите размер хеш-таблицы: ";
    cin >> hashTableSize;
    cout << "Введите значение K: ";
    cin >> K;

    srand(static_cast<unsigned int>(time(0)));

    Node** hashTable = createHashTable(hashTableSize);
    Node** greaterHashTable = createHashTable(hashTableSize);
    Node** lesserHashTable = createHashTable(hashTableSize);

    // Заполнение исходной хеш-таблицы случайными элементами
    for (int i = 0; i < numElements; i++) {
        int data = rand() % 100;
        insertNode(hashTable, data, hashTableSize);
    }

    // Разделение исходной хеш-таблицы на две
    for (int i = 0; i < hashTableSize; i++) {
        Node* p = hashTable[i];
        while (p) {
            if (p->data > K) {
                insertNode(greaterHashTable, p->data, hashTableSize);
            }
            else {
                insertNode(lesserHashTable, p->data, hashTableSize);
            }
            p = p->next;
        }
    }

    // Вывод всех хеш-таблиц
    cout << "Исходная хеш-таблица:\n";
    printHashTable(hashTable, hashTableSize);

    cout << "\nХеш-таблица с ключами больше " << K << ":\n";
    printHashTable(greaterHashTable, hashTableSize);

    cout << "\nХеш-таблица с ключами меньше или равными " << K << ":\n";
    printHashTable(lesserHashTable, hashTableSize);

    deleteHashTable(hashTable, hashTableSize);
    deleteHashTable(greaterHashTable, hashTableSize);
    deleteHashTable(lesserHashTable, hashTableSize);

    system("pause");
    return 0;
}

