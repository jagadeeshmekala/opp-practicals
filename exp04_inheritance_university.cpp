// Experiment 4: Single and multilevel inheritance
// University management system: Person -> Student -> GraduateStudent
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    int age;
    string name;

public:
    void getPersonData() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
    }

    void displayPersonData() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

class Student : public Person {
private:
    int roll;
    string course;

public:
    void getStudentData() {
        getPersonData();
        cout << "Enter roll no.: ";
        cin >> roll;
        cout << "Enter course: ";
        cin >> course;
    }

    void displayStudentData() {
        displayPersonData();
        cout << "Roll no.: " << roll << endl;
        cout << "Course: " << course << endl;
    }
};

class GraduateStudent : public Student {
private:
    int marks;
    string specialization;

public:
    void getGraduateStudentData() {
        getStudentData();
        cout << "Enter specialization: ";
        cin >> specialization;
        cout << "Enter marks: ";
        cin >> marks;
    }

    void displayGraduateStudentData() {
        displayStudentData();
        cout << "Specialization: " << specialization << endl;
        cout << "Marks: " << marks << endl;

        if (marks >= 45) {
            cout << "Graduated!" << endl;
        } else {
            cout << "Not Graduated!" << endl;
        }
    }
};

int main() {
    GraduateStudent s1;

    cout << "ENTERING DETAILS" << endl;
    s1.getGraduateStudentData();

    cout << "\nDISPLAYING DETAILS" << endl;
    s1.displayGraduateStudentData();

    return 0;
}
