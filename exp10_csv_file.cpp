// Experiment 10: CSV reader/writer using fstream and file pointers
// Uses seekg, seekp, tellg and tellp to read and update records in place
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Student {
    int id;
    string name;
    int marks;
};

const string FILE_NAME = "students.csv";

// ---------- WRITE: store records in CSV ----------
// Marks are written with 3 digits (e.g. 078) so every record's marks field
// has a fixed width and can be overwritten in place with seekp.
void writeCSV(const vector<Student>& students) {
    ofstream out(FILE_NAME);
    if (!out) {
        cout << "Could not open file for writing" << endl;
        return;
    }
    out << "id,name,marks\n";
    for (const Student& s : students) {
        out << s.id << "," << s.name << ","
            << setfill('0') << setw(3) << s.marks << setfill(' ') << "\n";
    }
    cout << "[tellp] Write position after writing all records: " << out.tellp()
         << " bytes" << endl;
    out.close();
}

// ---------- READ: retrieve all records ----------
// Also remembers the byte position of each record using tellg
vector<streampos> readCSV() {
    vector<streampos> offsets;             // start position of each record
    ifstream in(FILE_NAME);
    if (!in) {
        cout << "Could not open file for reading" << endl;
        return offsets;
    }

    string line;
    getline(in, line);                     // skip header line
    cout << "\nID   Name      Marks" << endl;

    while (true) {
        streampos pos = in.tellg();        // where this record starts
        if (!getline(in, line)) break;

        stringstream ss(line);
        string id, name, marks;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, marks, ',');

        cout << left << setw(5) << id << setw(10) << name << stoi(marks)
             << "   (starts at byte " << pos << ")" << endl;
        offsets.push_back(pos);
    }
    return offsets;
}

// ---------- seekg: jump straight to one record and read it ----------
void readRecordAt(streampos pos) {
    ifstream in(FILE_NAME);
    in.seekg(pos);                         // move the GET pointer
    string line;
    getline(in, line);
    cout << "[seekg] Record at byte " << pos << ": " << line << endl;
}

// ---------- seekp: overwrite the marks of one record in place ----------
void updateMarks(streampos recordPos, int newMarks) {
    fstream file(FILE_NAME, ios::in | ios::out);

    file.seekg(recordPos);
    string line;
    getline(file, line);                   // to know the record length

    file.clear();
    streampos marksPos = recordPos + (streamoff)(line.size() - 3);
    file.seekp(marksPos);                  // move the PUT pointer to marks field
    file << setfill('0') << setw(3) << newMarks;
    cout << "[seekp/tellp] Updated marks; put pointer is now at byte "
         << file.tellp() << endl;
    file.close();
}

int main() {
    vector<Student> students = {
        {1, "Aarav", 78}, {2, "Diya", 92}, {3, "Kabir", 35}, {4, "Meera", 64}
    };

    // 1. Write the CSV file
    writeCSV(students);

    // 2. Read it back
    vector<streampos> offsets = readCSV();

    // 3. Jump directly to the 3rd record using seekg
    cout << endl;
    readRecordAt(offsets[2]);

    // 4. Change Kabir's marks from 35 to 58 in place using seekp
    updateMarks(offsets[2], 58);

    // 5. Read again to confirm the update
    cout << "\nAfter update:";
    readCSV();

    return 0;
}
