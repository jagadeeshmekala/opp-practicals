// Experiment 3: All constructor types and the Rule of 5
#include <iostream>
using namespace std;

class Number {
private:
    int* value;                        // pointer to heap memory

public:
    // Default constructor
    Number() {
        value = new int(0);
        cout << "Default Constructor" << endl;
    }

    // Parameterized constructor
    Number(int x) {
        value = new int(x);
        cout << "Parameterized Constructor" << endl;
    }

    // Copy constructor (deep copy)
    Number(const Number& n) {
        value = new int(*n.value);
        cout << "Copy Constructor" << endl;
    }

    // Move constructor (steal the pointer)
    Number(Number&& n) noexcept {
        value = n.value;
        n.value = nullptr;
        cout << "Move Constructor" << endl;
    }

    // Copy assignment
    Number& operator=(const Number& n) {
        if (this != &n) {
            delete value;
            value = new int(*n.value);
        }
        cout << "Copy Assignment" << endl;
        return *this;
    }

    // Move assignment
    Number& operator=(Number&& n) noexcept {
        if (this != &n) {
            delete value;
            value = n.value;
            n.value = nullptr;
        }
        cout << "Move Assignment" << endl;
        return *this;
    }

    // Destructor
    ~Number() {
        delete value;
        cout << "Destructor" << endl;
    }

    void display() {
        if (value != nullptr)
            cout << "Value: " << *value << endl;
        else
            cout << "Value: moved-from" << endl;
    }
};

int main() {
    Number n1;                 // default
    Number n2(10);             // parameterized
    Number n3 = n2;            // copy constructor
    Number n4 = Number(20);    // parameterized

    n3 = n2;                   // copy assignment
    n4 = Number(30);           // move assignment

    n1.display();
    n2.display();
    n3.display();
    n4.display();

    return 0;
}
