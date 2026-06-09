// Example program
#include <iostream>
using namespace std;

class Stack{

    class Node{

        int element;
        Node * next = NULL;

        public:
            Node() = default;
            Node(int element) : element(element) {};
            int get_element() const{
                return element;
            }
            Node * get_next() const{
                return next;
            }
            void set_element(int _n){
                element = _n;
            }
            void set_next(Node * p){
                next = p;
            }
    };

    Node * top = NULL;
    int size = 0;

    public:
        Stack()= default;

        Stack (const Stack & r) : size(r.size) {
            if(r.size){
                Node * p = r.top;
                Node * temp = new Node(p->get_element());
                top = temp;
                while(p = p->get_next()){
                   temp->set_next(new Node(p->get_element()));
                   temp = temp->get_next();
                }
            }
        }

        ~Stack(){
            reset();
        }
        bool IsEmpty() const{
            return size == 0;
        }
        int get_top() const {
            if(IsEmpty()) exit(1);
            return top->get_element();
        }
        int get_size() const {
            return size;
        }
        bool push(int n){
            Node * new_node = new Node(n);
            if(!new_node) return false;
            if(size == 0) top = new_node;
            else{
                new_node->set_next(top);
                top = new_node;
            }
            size++;
            return true;
        }
        bool pop(){
            if(size == 0) return false;
            Node * temp = top->get_next();
            delete top;
            top = temp;
            size--;
            return true;
        }
        void print() const{
            if(size == 0) return;
            Node * temp = top;
            while(temp){
                cout<<temp->get_element()<<endl;
                temp = temp->get_next();
            }
            cout<<endl;
        }
        void reset(){
            while(pop());
        }

        Stack & operator=(const Stack & r){
            if(this != &r){
                /*
                    if (this->size < r.size )  => Создать недостающие узлы.
                    else if( this->size > r.size) => Удалить лишние узлы

                    Копировать.
                */
                Node * temp;
                Node * prev;
                int counter;
                if(this->size < r.size){
                    temp = top;
                    while(temp->get_next()) temp = temp->get_next();
                    counter = r.size - this->size;
                    while(counter--){
                        temp->set_next(new Node);
                        temp = temp->get_next();
                    }
                }
                else if(this->size > r.size){
                    counter = r.size;
                    temp = top;
                    while(counter--){
                        prev = temp;
                        temp = temp->get_next();
                       // if(counter == (r.size - 1)) temp->set_next(nullptr);
                    }
                    prev->set_next(nullptr);
                }

            }
            return *this;
        }
};
int main()
{
    Stack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.pop();
    s1.pop();
    s1.push(5);
    s1.print();
   // s1.reset();
 //   cout<<s1.get_size()<<endl;
    Stack s2 = s1;
    s2.print();
    s1.pop();

    s2.push(100);
    s2.push(200);
    s1.print();
    s2.print();


    return 0;
}
