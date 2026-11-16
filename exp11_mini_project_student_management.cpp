// Experiment 11: MINI PROJECT - Student Management System
//
// OOP concepts used:
//   Classes and objects      : Person, Student, StudentManager
//   Encapsulation            : private data with public getters/setters
//   Inheritance              : Student inherits from Person
//   Constructors/Destructors : initialise objects, virtual destructor
//   STL                      : vector, sort, find_if, accumulate
//   File handling            : records saved to / loaded from students_db.csv
//   Input validation         : menu and marks/age/roll checks
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;

// ---------- Base class ----------
class Person {
protected:
    string name;
    int age;

public:
    Person(string n = "", int a = 0) : name(n), age(a) {}
    virtual ~Person() {}
    string getName() const { return name; }
    int getAge() const { return age; }
};

// ---------- Derived class ----------
class Student : public Person {
private:
    int roll;
    string course;
    int marks;

public:
    Student(int r = 0, string n = "", int a = 0, string c = "", int m = 0)
        : Person(n, a), roll(r), course(c), marks(m) {}

    int getRoll() const { return roll; }
    string getCourse() const { return course; }
    int getMarks() const { return marks; }
    void setMarks(int m) { marks = m; }

    string getGrade() const {
        if (marks >= 85) return "A";
        if (marks >= 70) return "B";
        if (marks >= 50) return "C";
        if (marks >= 40) return "D";
        return "F";
    }

    void display() const {
        cout << left << setw(7) << roll << setw(16) << name << setw(6) << age
             << setw(12) << course << setw(8) << marks << getGrade() << endl;
    }

    string toCSV() const {
        return to_string(roll) + "," + name + "," + to_string(age) + "," +
               course + "," + to_string(marks);
    }
};

// ---------- Helper input functions ----------
int readInt(const string& prompt, int low, int high) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (x >= low && x <= high) return x;
            cout << "Please enter a value between " << low << " and " << high << ".\n";
        } else {
            if (cin.eof()) exit(0);                       // input ended
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string readLine(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    if (cin.eof()) exit(0);
    replace(s.begin(), s.end(), ',', ' ');                // commas would break the CSV
    return s;
}

// ---------- Manager class ----------
class StudentManager {
private:
    vector<Student> students;
    string fileName = "students_db.csv";

    int findIndex(int roll) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getRoll() == roll) return (int)i;
        }
        return -1;
    }

    void save() const {
        ofstream out(fileName);
        for (const Student& s : students) out << s.toCSV() << "\n";
    }

    void load() {
        ifstream in(fileName);
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string r, n, a, c, m;
            getline(ss, r, ',');
            getline(ss, n, ',');
            getline(ss, a, ',');
            getline(ss, c, ',');
            getline(ss, m, ',');
            try {
                students.push_back(Student(stoi(r), n, stoi(a), c, stoi(m)));
            } catch (...) {
                // skip a damaged line
            }
        }
    }

    void printHeader() const {
        cout << left << setw(7) << "Roll" << setw(16) << "Name" << setw(6) << "Age"
             << setw(12) << "Course" << setw(8) << "Marks" << "Grade" << endl;
        cout << string(55, '-') << endl;
    }

public:
    StudentManager() { load(); }

    void addStudent() {
        int roll = readInt("Enter roll number: ", 1, 99999);
        if (findIndex(roll) != -1) {
            cout << "A student with this roll number already exists.\n";
            return;
        }
        string name = readLine("Enter name: ");
        int age = readInt("Enter age (1-120): ", 1, 120);
        string course = readLine("Enter course: ");
        int marks = readInt("Enter marks (0-100): ", 0, 100);

        students.push_back(Student(roll, name, age, course, marks));
        save();
        cout << "Student added successfully.\n";
    }

    void displayAll() const {
        if (students.empty()) {
            cout << "No records found.\n";
            return;
        }
        printHeader();
        for (const Student& s : students) s.display();
    }

    void searchStudent() const {
        int roll = readInt("Enter roll number to search: ", 1, 99999);
        int i = findIndex(roll);
        if (i == -1) {
            cout << "Student not found.\n";
            return;
        }
        printHeader();
        students[i].display();
    }

    void updateMarks() {
        int roll = readInt("Enter roll number to update: ", 1, 99999);
        int i = findIndex(roll);
        if (i == -1) {
            cout << "Student not found.\n";
            return;
        }
        int marks = readInt("Enter new marks (0-100): ", 0, 100);
        students[i].setMarks(marks);
        save();
        cout << "Marks updated successfully.\n";
    }

    void deleteStudent() {
        int roll = readInt("Enter roll number to delete: ", 1, 99999);
        int i = findIndex(roll);
        if (i == -1) {
            cout << "Student not found.\n";
            return;
        }
        students.erase(students.begin() + i);
        save();
        cout << "Student deleted successfully.\n";
    }

    void showRanking() const {
        if (students.empty()) {
            cout << "No records found.\n";
            return;
        }
        vector<Student> sorted = students;               // copy, keep original order
        sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) {
            return a.getMarks() > b.getMarks();
        });
        printHeader();
        for (const Student& s : sorted) s.display();
    }

    void showStatistics() const {
        if (students.empty()) {
            cout << "No records found.\n";
            return;
        }
        int total = accumulate(students.begin(), students.end(), 0,
                               [](int sum, const Student& s) { return sum + s.getMarks(); });
        auto top = max_element(students.begin(), students.end(),
                               [](const Student& a, const Student& b) {
                                   return a.getMarks() < b.getMarks();
                               });
        int passed = count_if(students.begin(), students.end(),
                              [](const Student& s) { return s.getMarks() >= 40; });

        cout << "Total students : " << students.size() << endl;
        cout << "Average marks  : " << fixed << setprecision(2)
             << (double)total / students.size() << endl;
        cout << "Topper         : " << top->getName() << " (" << top->getMarks() << ")" << endl;
        cout << "Passed         : " << passed << " / " << students.size() << endl;
    }
};

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add student\n";
        cout << "2. Display all students\n";
        cout << "3. Search student by roll number\n";
        cout << "4. Update marks\n";
        cout << "5. Delete student\n";
        cout << "6. Show ranking (by marks)\n";
        cout << "7. Show statistics\n";
        cout << "0. Exit\n";
        choice = readInt("Enter your choice: ", 0, 7);

        switch (choice) {
            case 1: manager.addStudent();    break;
            case 2: manager.displayAll();    break;
            case 3: manager.searchStudent(); break;
            case 4: manager.updateMarks();   break;
            case 5: manager.deleteStudent(); break;
            case 6: manager.showRanking();   break;
            case 7: manager.showStatistics();break;
            case 0: cout << "Goodbye! Records are saved in students_db.csv\n"; break;
        }
    } while (choice != 0);

    return 0;
}
