// Experiment 6: Compile time polymorphism
// Function overloading and operator overloading (Complex number class)
#include <iostream>
#include <string>
using namespace std;

class Complex {
    int real, img;

public:
    Complex(int r = 0, int i = 0) {
        real = r;
        img = i;
    }

    // Function overloading: same name, different parameters
    void display() {
        cout << real << " + " << img << "i" << endl;
    }

    void display(string msg) {
        cout << msg << real << " + " << img << "i" << endl;
    }

    // Operator overloading: gives + a meaning for Complex objects
    Complex operator+(Complex c) {
        Complex temp;
        temp.real = real + c.real;
        temp.img = img + c.img;
        return temp;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(2, 5);

    c1.display();
    c1.display("First Complex Number: ");
    c2.display("Second Complex Number: ");

    Complex c3 = c1 + c2;
    c3.display("Addition: ");

    return 0;
}
