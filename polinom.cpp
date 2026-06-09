#include <iostream>
using namespace std;

template <class T>
class Polinom{

    int koef; // степень
    T * array; // массив

    public:

    ~Polinom(){
        delete [] array;
    }

    Polinom() : koef(0), array(new T[1]{static_cast<T>(0)}) {}

    // из массива
    Polinom(int _koef, const T * _array){
        koef = _koef;
        array = new T[koef + 1];
        // ищем старший ненулевой
        int real_koef = 0;
        for(int i = koef; i >= 0; i--){
            if(_array[i] != 0){
                real_koef = i;
                break;
            }
        }
        koef = real_koef;
        for(int i = 0; i <= koef; i++)
            array[i] = _array[i];
    }

    // копирующий
    Polinom(const Polinom & other){
        koef = other.koef;
        array = new T[koef + 1];
        for(int i = 0; i <= koef; i++)
            array[i] = other.array[i];
    }

    Polinom & operator=(const Polinom & other){
        if(this == &other) return *this;
        delete [] array;
        koef = other.koef;
        array = new T[koef + 1];
        for(int i = 0; i <= koef; i++)
            array[i] = other.array[i];
        return *this;
    }

    int degree() const { return koef; }

    // значение в точке
    T evaluate(T x) const {
        T result = 0;
        T power = 1;
        for(int i = 0; i <= koef; i++){
            result += array[i] * power;
            power *= x;
        }
        return result;
    }

    // схема Горнера
    T evaluateHorner(T x) const {
        T result = array[koef];
        for(int i = koef - 1; i >= 0; i--){
            result = result * x + array[i];
        }
        return result;
    }

    friend ostream & operator<<(ostream & out, const Polinom & r){
        if( r.koef == 0 && r.array[0] == 0 ){
            cout << 0 << endl;
            return out;
        }
        bool first = true;
        for( int i = r.koef; i >= 0; i-- ){
            if(r.array[i] == 0) continue;
            if( !first && r.array[i] > 0 ) cout << "+";
            if( r.array[i] == 1 && !first ){
                // без единицы
            } else if( r.array[i] == -1 && !first ){
                cout << "-";
            } else {
                cout << r.array[i];
            }
            if( i == 0 ){
                // без X
            } else if( i == 1 ){
                cout << "X";
            } else {
                cout << "X^" << i;
            }
            first = false;
        }
        cout << endl;
        return out;
    }

    // сложение
    friend Polinom<T> operator+(const Polinom<T> & a, const Polinom<T> & b){
        int new_koef = max(a.koef, b.koef);
        T * result_arr = new T[new_koef + 1]{0};
        for(int i = 0; i <= a.koef; i++)
            result_arr[i] += a.array[i];
        for(int i = 0; i <= b.koef; i++)
            result_arr[i] += b.array[i];
        return Polinom<T>(new_koef, result_arr);
    }
};


int main() {
    Polinom<int> p1;
    cout << "p1 = " << p1; // 0

    int A[] = {-20, 10, -7, 3, 2};
    Polinom<int> p2(sizeof(A)/sizeof(int) - 1, A);
    cout << "p2 = " << p2;

    double B[] = {-10.45, 1.67, 0, 0, 0, 0, 5.6, 0, 0, 0};
    Polinom<double> p3(sizeof(B)/sizeof(double) - 1, B);
    cout << "p3 = " << p3;

    Polinom<int> p4(2, new int[]{6, -5, 2});
    cout << "p4(3) = " << p4.evaluate(3) << endl; // = 9
    cout << "p4 Horner(3) = " << p4.evaluateHorner(3) << endl;

    int C[] = {1, 2};
    Polinom<int> p5(1, C);
    Polinom<int> p6(1, new int[]{3, 4});
    Polinom<int> p7 = p5 + p6;
    cout << "p5+p6 = " << p7;

    Polinom<int> p8(p2);
    cout << "p8 = " << p8;

    Polinom<int> p9;
    p9 = p2;
    cout << "p9 = " << p9;

    return 0;
}
