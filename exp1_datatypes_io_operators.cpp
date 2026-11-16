// Experiment 1: Data types, constants, variables, I/O and operators
#include <iostream>
using namespace std;

int main() {
    // Constant: value can never change
    const float totalMarks = 100;

    // Variables of different data types
    int age;            // whole number
    float marks;        // decimal number
    char grade;         // single character
    bool passed;        // true or false

    // Input using cin
    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter your marks: ";
    cin >> marks;

    // Arithmetic operators
    float percentage = (marks / totalMarks) * 100;

    // Relational operator with if/else
    if (percentage >= 40) {
        passed = true;
    } else {
        passed = false;
    }

    // Logical operator for grade
    if (percentage >= 75 && passed) {
        grade = 'A';
    } else if (percentage >= 40) {
        grade = 'B';
    } else {
        grade = 'F';
    }

    // Output using cout
    cout << "Age = " << age << endl;
    cout << "Marks = " << marks << endl;
    cout << "Percentage = " << percentage << "%" << endl;
    cout << "Grade = " << grade << endl;
    cout << "Passed = " << passed << endl;   // prints 1 or 0

    return 0;
}
