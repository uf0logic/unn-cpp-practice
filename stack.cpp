#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    T* data;
    size_t top;
    size_t capacity;

    // Вспомогательные стеки для O(1) поиска min/max
    T* minStack;
    T* maxStack;

    // Выделение памяти
    void allocate(size_t newCap) {
        capacity = newCap;
        data = new T[capacity];
        minStack = new T[capacity];
        maxStack = new T[capacity];
    }

    // Освобождение памяти
    void deallocate() {
        delete[] data;
        delete[] minStack;
        delete[] maxStack;
    }

public:

    Stack() : top(0), capacity(16) {
        allocate(capacity);
    }

    // Конструктор копирования
    Stack(const Stack& other)
        : top(other.top), capacity(other.capacity) {
        data = new T[capacity];
        minStack = new T[capacity];
        maxStack = new T[capacity];
        for (size_t i = 0; i < top; i++) {
            data[i] = other.data[i];
            minStack[i] = other.minStack[i];
            maxStack[i] = other.maxStack[i];
        }
    }

    // Копирующий оператор присваивания
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            // Оптимизация: если текущей памяти достаточно — не перевыделяем
            if (capacity < other.top) {
                deallocate();
                allocate(other.capacity);
            } else {
                top = other.top;
                for (size_t i = 0; i < top; i++) {
                    data[i] = other.data[i];
                    minStack[i] = other.minStack[i];
                    maxStack[i] = other.maxStack[i];
                }
            }
        }
        return *this;
    }

    // Конструктор с указанием начальной ёмкости
    explicit Stack(size_t cap)
        : top(0), capacity(cap) {
        allocate(capacity);
    }

    // Деструктор
    ~Stack() {
        deallocate();
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return top == 0;
    }

    // Размер стека
    size_t size() const {
        return top;
    }

    // Ёмкость стека
    size_t getCapacity() const {
        return capacity;
    }

    // Добавление элемента
    void push(const T& value) {
        if (top == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[top] = value;
        size_t idx = top++; // текущий индекс (0-based)

        // Обновление стека минимумов
        if (idx == 0 || value <= minStack[idx - 1]) {
            minStack[idx] = value;
        } else {
            minStack[idx] = minStack[idx - 1];
        }

        // Обновление стека максимумов
        if (idx == 0 || value >= maxStack[idx - 1]) {
            maxStack[idx] = value;
        } else {
            maxStack[idx] = maxStack[idx - 1];
        }
    }

    // Удаление верхнего элемента
    void pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        top--;
    }

    // Верхний элемент
    T& topElement() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return data[top - 1];
    }

    const T& topElement() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return data[top - 1];
    }

    // Минимальный элемент за O(1)
    T getMin() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return minStack[top - 1];
    }

    // Максимальный элемент за O(1)
    T getMax() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return maxStack[top - 1];
    }

    // Вывод стека
    void print() const {
        cout << "Stack: [";
        for (size_t i = 0; i < top; i++) {
            if (i > 0) cout << ", ";
            cout << data[i];
        }
        cout << "] (size: " << top << ", capacity: " << capacity << ")" << endl;
    }

    // Очистка стека
    void clear() {
        top = 0;
    }

private:
    // Изменение размера
    void resize(size_t newCap) {
        T* newData = new T[newCap];
        T* newMinStack = new T[newCap];
        T* newMaxStack = new T[newCap];

        for (size_t i = 0; i < top; i++) {
            newData[i] = data[i];
            newMinStack[i] = minStack[i];
            newMaxStack[i] = maxStack[i];
        }

        deallocate();
        data = newData;
        minStack = newMinStack;
        maxStack = newMaxStack;
        capacity = newCap;
    }
};

// Основная функция
int main() {
    try {
        Stack<int> st;

        cout << "--- Базовые операции ---" << endl;
        st.push(10);
        st.push(5);
        st.push(20);
        st.push(3);
        st.push(15);

        cout << "Стек после push: ";
        st.print();
        cout << "Верхний элемент: " << st.topElement() << endl;
        cout << "Минимум: " << st.getMin() << endl;
        cout << "Максимум: " << st.getMax() << endl;

        cout << "\n--- После pop ---" << endl;
        st.pop();
        st.pop();
        cout << "Стек после 2 pop: ";
        st.print();
        cout << "Верхний элемент: " << st.topElement() << endl;
        cout << "Минимум: " << st.getMin() << endl;
        cout << "Максимум: " << st.getMax() << endl;

        cout << "\n--- Копирование (с перераспределением) ---" << endl;
        Stack<int> st2(st);
        st2.print();
        cout << "Копия: min = " << st2.getMin() << ", max = " << st2.getMax() << endl;

        st2.push(1);
        st2.push(100);
        cout << "Копия после push: ";
        st2.print();
        cout << "Оригинал без изменений: ";
        st.print();

        cout << "\n--- Оптимизация копирования (хватает capacity) ---" << endl;
        Stack<int> st3(32); // создаём стек с большим capacity
        st3 = st; // копируем — память не должна перевыделяться
        cout << "st3 capacity: " << st3.getCapacity() << endl;

        cout << "\n--- Пустой стек ---" << endl;
        Stack<int> st4;
        cout << "st4 isEmpty: " << (st4.isEmpty() ? "true" : "false") << endl;
        st4.print();

        cout << "\n--- Проверка с дублирующими min/max ---" << endl;
        Stack<int> st5;
        st5.push(50);
        st5.push(50);
        st5.push(10);
        st5.push(10);
        st5.push(90);
        cout << "Стек с повторами: ";
        st5.print();
        cout << "Минимум: " << st5.getMin() << endl;
        cout << "Максимум: " << st5.getMax() << endl;
        st5.pop();
        cout << "После pop, минимум: " << st5.getMin() << ", максимум: " << st5.getMax() << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
