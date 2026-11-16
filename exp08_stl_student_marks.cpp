// Experiment 8: STL containers (vector, map, unordered_map) and
// algorithms (sort, find_if, transform) on a student marks dataset
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    int marks;
};

string getGrade(int marks) {
    if (marks >= 85) return "A";
    if (marks >= 70) return "B";
    if (marks >= 50) return "C";
    if (marks >= 40) return "D";
    return "F";
}

void printStudents(const vector<Student>& v) {
    for (const Student& s : v) {
        cout << "  Roll " << s.roll << "  " << s.name << "  " << s.marks << endl;
    }
}

int main() {
    // ---- vector: stores the dataset ----
    vector<Student> students = {
        {1, "Aarav", 78}, {2, "Diya", 92}, {3, "Kabir", 35},
        {4, "Meera", 64}, {5, "Rohan", 85}, {6, "Sana", 47}
    };

    cout << "Original data:" << endl;
    printStudents(students);

    // ---- sort: highest marks first (lambda decides the order) ----
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) { return a.marks > b.marks; });
    cout << "\nAfter sort (highest marks first):" << endl;
    printStudents(students);

    // ---- find_if: first student who failed (marks < 40) ----
    auto it = find_if(students.begin(), students.end(),
                      [](const Student& s) { return s.marks < 40; });
    cout << "\nFirst failing student: ";
    if (it != students.end()) {
        cout << it->name << " (" << it->marks << ")" << endl;
    } else {
        cout << "none" << endl;
    }

    // ---- count_if: how many passed ----
    int passed = count_if(students.begin(), students.end(),
                          [](const Student& s) { return s.marks >= 40; });
    cout << "Students passed: " << passed << " out of " << students.size() << endl;

    // ---- transform: add 5 grace marks (max 100) into a new vector ----
    vector<int> graceMarks(students.size());
    transform(students.begin(), students.end(), graceMarks.begin(),
              [](const Student& s) { return min(s.marks + 5, 100); });
    cout << "\nMarks after +5 grace: ";
    for (int m : graceMarks) cout << m << " ";
    cout << endl;

    // ---- accumulate: average marks ----
    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, const Student& s) { return sum + s.marks; });
    cout << "Average marks: " << (double)total / students.size() << endl;

    // ---- map: grade -> how many students (kept sorted by grade) ----
    map<string, int> gradeCount;
    for (const Student& s : students) {
        gradeCount[getGrade(s.marks)]++;
    }
    cout << "\nGrade distribution (map):" << endl;
    for (const auto& p : gradeCount) {
        cout << "  Grade " << p.first << ": " << p.second << endl;
    }

    // ---- unordered_map: roll number -> student (fast lookup) ----
    unordered_map<int, Student> byRoll;
    for (const Student& s : students) {
        byRoll[s.roll] = s;
    }
    int searchRoll = 4;
    cout << "\nLookup roll " << searchRoll << " (unordered_map): ";
    if (byRoll.find(searchRoll) != byRoll.end()) {
        cout << byRoll[searchRoll].name << ", marks " << byRoll[searchRoll].marks << endl;
    } else {
        cout << "not found" << endl;
    }

    return 0;
}
