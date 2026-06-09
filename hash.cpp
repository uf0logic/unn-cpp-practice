// Example program
#include <iostream>
#include <string>
#define HASH_SIZE 100
using namespace std;

class Hash {

    class Student {
        const int id;
        string name;
        int age;
        bool IsExist = true;

    public:
        Student(int _id, const string& _name, int _age) : id(_id), name(_name), age(_age) {}
        void set_age(int _age) {
            age = _age;
        }

        //Добавим get'еры для вывода
        int get_id() const {
            return id;
        }

        string get_name() const{
            return name;
        }

        int get_age() const {
            return age;
        }
        bool IsObjectExist() const {
            return IsExist;
        }
        void DeleteObject() {
            IsExist = false;
        }
    };

    class Node {
        Student* sp;
        Node* next = NULL;

    public:
        Node(Student* _sp) : sp(_sp) {}
        ~Node() {
            delete sp;
        }
        Student* get_student() const {
            return sp;
        }
        Node* get_next() const {
            return next;
        }
        void set_next(Node* p) {
            next = p;
        }
    };

    Node* head[HASH_SIZE] = { NULL };
    int counter = 0;
    int last_id = 0;

public:
    Hash() = default;
    ~Hash() {}
    //Hash(const Hash& r) : {}
    Hash& operator=(const Hash& r) {}
    void reset() {}
    bool insert_obj(const string& _name, const int _age) {
    }
    bool delete_obj(const string& _name) {
    }

    void select_name(const string& _name) {}

    void print() const {
        for (int i = 0; i < HASH_SIZE; ++i) {
            Node* curr = head[i];
            while (curr) {
                Student* student = curr->get_student();
                if (student->IsObjectExist()) {
                    cout << "  Student " << i << ": ID=" << student->get_id() << ", Name=" << student->get_name() << ", Age=" << student->get_age() << endl;
                }
                curr = curr->get_next();
            }
        }
    }
};

int main()
{
    Hash fiit2024;
    // fiit.insert("Ivan", 23);

    return 0;
}
