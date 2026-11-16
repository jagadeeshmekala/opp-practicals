// Experiment 7: Generic Stack class using templates
// Tested with int, float and std::string
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// T is a placeholder for any data type
template <typename T>
class Stack {
private:
    vector<T> data;                       // stores the elements

public:
    void push(const T& value) {           // add on top
        data.push_back(value);
    }

    T pop() {                             // remove from top and return it
        if (isEmpty()) {
            throw runtime_error("Stack Underflow: cannot pop from an empty stack");
        }
        T top = data.back();
        data.pop_back();
        return top;
    }

    T peek() const {                      // look at top without removing
        if (isEmpty()) {
            throw runtime_error("Stack is empty: nothing to peek");
        }
        return data.back();
    }

    bool isEmpty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }

    void display() const {
        cout << "Stack (top -> bottom): ";
        for (int i = (int)data.size() - 1; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // ---- Stack of int ----
    cout << "=== Stack of int ===" << endl;
    Stack<int> si;
    si.push(10);
    si.push(20);
    si.push(30);
    si.display();
    cout << "Top element: " << si.peek() << endl;
    cout << "Popped: " << si.pop() << endl;
    si.display();
    cout << "Size: " << si.size() << endl;

    // ---- Stack of float ----
    cout << "\n=== Stack of float ===" << endl;
    Stack<float> sf;
    sf.push(1.5f);
    sf.push(2.75f);
    sf.push(3.14f);
    sf.display();
    cout << "Popped: " << sf.pop() << endl;
    sf.display();

    // ---- Stack of std::string ----
    cout << "\n=== Stack of string ===" << endl;
    Stack<string> ss;
    ss.push("C++");
    ss.push("is");
    ss.push("fun");
    ss.display();
    cout << "Popped: " << ss.pop() << endl;
    ss.display();

    // ---- Underflow check ----
    cout << "\n=== Underflow test ===" << endl;
    Stack<int> empty;
    try {
        empty.pop();
    } catch (const runtime_error& e) {
        cout << "Error caught: " << e.what() << endl;
    }

    return 0;
}
