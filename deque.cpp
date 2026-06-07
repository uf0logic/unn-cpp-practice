#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t count;

public:

    Deque() : head(nullptr), tail(nullptr), count(0) {}

    // Конструктор копирования
    Deque(const Deque& other) : head(nullptr), tail(nullptr), count(0) {
        Node* cur = other.head;
        while (cur != nullptr) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }

    // Деструктор
    ~Deque() {
        clear();
    }

    // Оператор присваивания
    Deque& operator=(const Deque& other) {
        if (this != &other) {
            clear();
            Node* cur = other.head;
            while (cur != nullptr) {
                pushBack(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    // Добавление элемента в конец
    void pushBack(const T& value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    // Добавление элемента в начало
    void pushFront(const T& value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    // Получение последнего элемента (без удаления)
    T& back() {
        if (isEmpty()) {
            throw out_of_range("Deque is empty");
        }
        return tail->data;
    }

    const T& back() const {
        if (isEmpty()) {
            throw out_of_range("Deque is empty");
        }
        return tail->data;
    }

    // Получение первого элемента (без удаления)
    T& front() {
        if (isEmpty()) {
            throw out_of_range("Deque is empty");
        }
        return head->data;
    }

    const T& front() const {
        if (isEmpty()) {
            throw out_of_range("Deque is empty");
        }
        return head->data;
    }

    // Получение размера
    size_t size() const {
        return count;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return count == 0;
    }

    // Удаление элемента из конца
    void popBack() {
        if (isEmpty()) {
            throw out_of_range("Deque is empty");
        }

        Node* tmp = tail;

        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete tmp;
        count--;
    }

    // Удаление элемента из начала
    void popFront() {
        if (isEmpty()) {
            throw out_of_range("Deque is empty");
        }

        Node* tmp = head;

        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }

        delete tmp;
        count--;
    }

    // Вывод всех элементов (для демонстрации)
    void print() const {
        Node* cur = head;
        cout << "Deque: ";
        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << "(size: " << count << ")" << endl;
    }

    // Очистка очереди
    void clear() {
        while (!isEmpty()) {
            popFront();
        }
    }

};

// Основная функция
int main() {
    try {
        Deque<int> dq;
        dq.pushFront(1);
        dq.pushFront(5);
        dq.pushBack(10);
        dq.pushBack(20);

        cout << "Исходная очередь:" << endl;
        dq.print();
        cout << "Верхний элемент: " << dq.front() << endl;
        cout << "Нижний элемент: " << dq.back() << endl;

        cout << "\nУдаляем из начала:" << endl;
        dq.popFront();
        dq.print();

        cout << "Удаляем из конца:" << endl;
        dq.popBack();
        dq.print();

        cout << "\nСоздаём копию:" << endl;
        Deque<int> dq2(dq);
        dq2.print();

        dq2.pushBack(30);
        cout << "Оригинал после модификации копии: ";
        dq.print();
        cout << "Копия после модификации: ";
        dq2.print();

        cout << "\nОчищаем основную очередь:" << endl;
        dq.clear();
        dq.print();

        cout << "Копия осталась без изменений: ";
        dq2.print();

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
